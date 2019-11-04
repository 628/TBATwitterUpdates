#ifndef TBATWITTERUPDATES_HTTPREQUEST_H
#define TBATWITTERUPDATES_HTTPREQUEST_H

#include <curl/curl.h>

class HttpRequest
{
public:
    static void sendPost(char *url, curl_slist *headers, char *fields);
    static void sendPost(const char *url, curl_slist *headers, const char *fields);

    static void sendGet(char *url, curl_slist *headers);
    static void sendGet(const char *url, curl_slist *headers);
};


#endif //TBATWITTERUPDATES_HTTPREQUEST_H
