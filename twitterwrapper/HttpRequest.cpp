#include <iostream>
#include "HttpRequest.h"

void HttpRequest::sendPost(char *url, curl_slist *headers, char *fields)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << res << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}

void HttpRequest::sendPost(const char *url, curl_slist *headers, const char *fields)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << res << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}
