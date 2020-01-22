#include <iostream>
#include <pistache/endpoint.h>
#include "httpserver/handlers/WebhookHandler.h"
#include "Config.h"
#include "httpserver/headers/XTBAChecksum.h"
#include "Logger.h"

using namespace Pistache;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <configFilePath>" << std::endl;
        return -1;
    }

    if (access(argv[1], F_OK) == -1) {
        std::cerr << "Config file not found!" << std::endl;
        return -1;
    }

    Config::loadConfig(std::string(argv[1]));

    Logger::log("Configuration file loaded successfully!");

    Http::Header::Registry::instance().registerHeader<XTBAChecksum>();

    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(Config::get("port")));
    auto opts = Pistache::Http::Endpoint::options()
            .threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<WebhookHandler>());
    server.serve();

    Logger::log("Connected to port! Listening for requests...");
}