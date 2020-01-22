#include "Config.h"

using json = nlohmann::json;

std::string Config::config;

void Config::loadConfig(const std::string &filePath) {
    std::ifstream input;
    input.open(filePath);

    config = std::string(dynamic_cast<std::stringstream const &>(
                                 std::stringstream() << input.rdbuf()).str());

    input.close();
}

std::string Config::get(const std::string &key) {
    json configJson = json::parse(config);

    return configJson.value(key, "");
}
