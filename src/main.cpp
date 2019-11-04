#include <iostream>
#include "pistache/endpoint.h"
#include "httpserver/handlers/WebhookHandler.h"
#include "Config.h"
#include "httpserver/headers/XTBAChecksum.h"
#include "Logger.h"

using namespace Pistache;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <configFilePath>" << std::endl;
        return -1;
    }

    if (access(argv[1], F_OK) == -1)
    {
        std::cerr << "Config file not found!" << std::endl;
        return -1;
    }

    Config::loadConfig(std::string(argv[1]));

    Logger::log("Configuration file loaded successfully!");

    Http::Header::Registry::instance().registerHeader<XTBAChecksum>();
    Http::listenAndServe<WebhookHandler>("*:" + Config::get("port"));

    Logger::log("Connected to port! Listening for requests...");
}