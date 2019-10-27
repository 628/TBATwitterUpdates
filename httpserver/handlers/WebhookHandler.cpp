#include "WebhookHandler.h"
#include "../../Config.h"
#include "../../twitterwrapper/Twitter.h"
#include <nlohmann/json.hpp>
#include <openssl/sha.h>
#include <crypto++/sha.h>
#include <crypto++/hex.h>
#include <algorithm>

using json = nlohmann::json;

std::string getFullCompLevelString(const std::string &level)
{
    if (level == "qm")
    {
        return "Quals";
    }
    else if (level == "ef")
    {
        return "Eighths";
    }
    else if (level == "qf")
    {
        return "Quarters";
    }
    else if (level == "sf")
    {
        return "Semis";
    }
    else if (level == "f")
    {
        return "Finals";
    }
    else
    {
        return "";
    }
}

typedef struct
{
    std::string eventName;
    std::string compLevel;
    std::string matchNum;
    std::string alliance;
    std::string score;
    bool won;
} Match;

std::string genSHA1Hash(const std::string &source)
{
    CryptoPP::SHA1 hash;
    byte digest[CryptoPP::SHA1::DIGESTSIZE];

    hash.CalculateDigest(digest, (const byte *) source.c_str(), source.size());

    std::string output;
    CryptoPP::HexEncoder encoder;
    CryptoPP::StringSink test = CryptoPP::StringSink(output);

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}

bool verifyMatchFields(Match match)
{
    return !(match.eventName.empty() ||
             match.compLevel.empty() ||
             match.matchNum.empty() ||
             match.alliance.empty() ||
             match.score.empty());

}

void WebhookHandler::onRequest(const Http::Request &request, Http::ResponseWriter response)
{
    std::string checkSumHeader = request.headers().getRaw("X-TBA-Checksum").value();
    std::string checkSum = genSHA1Hash(Config::get("secret") + request.body());

    // Make lowercase
    std::transform(checkSum.begin(), checkSum.end(), checkSum.begin(), [](unsigned char c)
    { return std::tolower(c); });

    if (checkSumHeader != checkSum)
    {
        response.send(Http::Code::Forbidden);
        return;
    }

    auto jsonBody = json::parse(request.body());

    std::string messageType = jsonBody.value("message_type", "NULL");

    if (messageType == "NULL")
    {
        response.send(Http::Code::Bad_Request);
        return;
    }

    if (messageType == "verification")
    {
        json data = jsonBody.at("/message_data"_json_pointer);
        std::string verificationKey = data.value("verification_key", "NULL");

        if (verificationKey != "NULL")
        {
            std::cout << "Your verification key is " << verificationKey
                      << "! Please enter it on your TBA account." << std::endl;

            response.send(Http::Code::Ok);
            return;
        }
        else
        {
            response.send(Http::Code::Bad_Request);
            return;
        }
    }
    else if (messageType == "match_score")
    {
        Match frcMatch{};

        json data = jsonBody.at("/message_data"_json_pointer);
        json match = data.at("/match"_json_pointer);
        json alliances = match.at("/alliances"_json_pointer);
        json blueAlliance = alliances.at("/blue"_json_pointer);
        json redAlliance = alliances.at("/red"_json_pointer);

        std::vector<std::string> blueTeams = blueAlliance.value("teams", std::vector<std::string>());
        std::vector<std::string> redTeams = redAlliance.value("teams", std::vector<std::string>());

        bool won = false;
        int redScore = redAlliance.value("score", 0);
        int blueScore = blueAlliance.value("score", 0);

        for (const std::string &s : blueTeams)
        {
            if (s == Config::get("team"))
            {
                frcMatch.alliance = "Blue Alliance";
                frcMatch.score = std::to_string(blueScore);
                won = blueScore > redScore;
            }
        }

        for (const std::string &s : redTeams)
        {
            if (s == Config::get("team"))
            {
                frcMatch.alliance = "Red Alliance";
                frcMatch.score = std::to_string(redScore);
                won = redScore > blueScore;
            }
        }

        frcMatch.eventName = data.value("event_name", "NULL");
        frcMatch.matchNum = std::to_string(match.value("match_number", 0));
        frcMatch.won = won;
        frcMatch.compLevel = getFullCompLevelString(match.value("comp_level", ""));

        if (!verifyMatchFields(frcMatch))
        {
            response.send(Http::Code::Bad_Request);
            return;
        }

        Twitter twitter(Config::get("accessToken"),
                Config::get("consumerApiKey"),
                Config::get("accessTokenSecret"),
                Config::get("consumerApiKeySecret"));

        std::string status;

        if (frcMatch.won)
        {
            status = "Win";
        }
        else
        {
            status = "Loss";
        }

        std::string tweet = frcMatch.eventName + " - " + frcMatch.compLevel + " " + frcMatch.matchNum + "\n" +
                "Result: " + status + "\n" +
                "Score: " + frcMatch.score + " (" + frcMatch.alliance + ")\n";

        twitter.sendTweet(tweet);

        response.send(Http::Code::Ok);
        return;
    }
    else
    {
        response.send(Http::Code::Ok);
        return;
    }
}
