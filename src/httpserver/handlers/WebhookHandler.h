#ifndef TBATWITTERUPDATES_WEBHOOKHANDLER_H
#define TBATWITTERUPDATES_WEBHOOKHANDLER_H

#include <pistache/endpoint.h>

using namespace Pistache;

class WebhookHandler : public Http::Handler
{
public:
HTTP_PROTOTYPE(WebhookHandler)
    void onRequest(const Http::Request &request, Http::ResponseWriter response) override;
};


#endif //TBATWITTERUPDATES_WEBHOOKHANDLER_H
