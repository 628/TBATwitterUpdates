#include <curl/curl.h>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "Twitter.h"
#include "../HttpRequest.h"

#define urlEncode(str) std::string(oauth_url_escape(str.c_str()))

bool Twitter::sendTweet(const std::string& messageContent)
{
    OAuthHeaders oAuthHeaders;

    oAuthHeaders.token = authToken;
    oAuthHeaders.consumerKey = consumerKey;

    std::time_t epochSeconds = std::time(nullptr);
    oAuthHeaders.timestamp = std::to_string(epochSeconds);

    std::string paramStr = "oauth_consumer_key=" + urlEncode(oAuthHeaders.consumerKey) +
            "&oauth_nonce=" + urlEncode(oAuthHeaders.nonce) +
            "&oauth_signature_method=" + urlEncode(oAuthHeaders.signature_method) +
            "&oauth_timestamp=" + urlEncode(oAuthHeaders.timestamp) +
            "&oauth_token=" + urlEncode(oAuthHeaders.token) +
            "&oauth_version=" + urlEncode(oAuthHeaders.version) +
            "&status=" + urlEncode(messageContent);

    std::string url = "https://api.twitter.com/1.1/statuses/update.json";
    std::string signatureStr = "POST&" + urlEncode(url) + "&" + urlEncode(paramStr);

    std::string signingKey = urlEncode(consumerKeySecret) + "&" + urlEncode(authTokenSecret);

    oAuthHeaders.signature = urlEncode(std::string(oauth_sign_hmac_sha1(signatureStr.c_str(), signingKey.c_str())));

    struct curl_slist *headers = nullptr;
    std::string headersString = "Authorization: "
                                "OAuth "
                                "oauth_consumer_key=\"" + oAuthHeaders.consumerKey + "\", "
                                "oauth_nonce=\"" + oAuthHeaders.nonce + "\", "
                                "oauth_signature=\"" + oAuthHeaders.signature + "\", "
                                "oauth_signature_method=\"" + oAuthHeaders.signature_method + "\", "
                                "oauth_timestamp=\"" + oAuthHeaders.timestamp + "\", "
                                "oauth_token=\"" + oAuthHeaders.token + "\", "
                                "oauth_version=\"" + oAuthHeaders.version + "\"";

    headers = curl_slist_append(headers, headersString.c_str());

    std::string contentField = "status=" + urlEncode(messageContent);

    HttpRequest::sendPost(url.c_str(), headers, contentField.c_str());
}