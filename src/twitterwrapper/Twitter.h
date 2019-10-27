#include <utility>

#include <utility>

#ifndef TBATWITTERUPDATES_TWITTER_H
#define TBATWITTERUPDATES_TWITTER_H

#include <string>
#include <utility>
#include <oauth.h>

class Twitter
{
public:
    std::string authToken;
    std::string consumerKey;
    std::string authTokenSecret;
    std::string consumerKeySecret;

    Twitter(std::string token, std::string key, std::string tokenSecret, std::string keySecret)
    {
        authToken = std::move(token);
        consumerKey = std::move(key);
        consumerKeySecret = std::move(keySecret);
        authTokenSecret = std::move(tokenSecret);
    }

    bool sendTweet(const std::string& messageContent);
private:
    typedef struct
    {
        std::string consumerKey;
        std::string nonce = oauth_gen_nonce();
        std::string signature;
        std::string signature_method = "HMAC-SHA1";
        std::string timestamp;
        std::string token;
        std::string version = "1.0";
    } OAuthHeaders;
};


#endif //TBATWITTERUPDATES_TWITTER_H
