#ifndef TBATWITTERUPDATES_TWITTER_H
#define TBATWITTERUPDATES_TWITTER_H

#include <string>
#include <utility>

class Twitter
{
public:
    std::string authToken;
    std::string consumerKey;

    Twitter(std::string authToken, std::string consumerKey)
    {
        this->authToken = std::move(authToken);
        this->consumerKey = std::move(consumerKey);
    }

    bool sendTweet(std::string messageContent);
private:
    typedef struct
    {
        std::string consumerKey = consumerKey;
        std::string nonce = oauth_gen_nonce();
        std::string signature;
        std::string signature_method = "HMAC-SHA1";
        std::string timestamp;
        std::string token = authToken;
        std::string version = "1.0";
    } OAuthHeaders;
};


#endif //TBATWITTERUPDATES_TWITTER_H
