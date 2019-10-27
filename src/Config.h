#ifndef TBATWITTERUPDATES_CONFIG_H
#define TBATWITTERUPDATES_CONFIG_H

#include <string>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

class Config
{
public:
    static std::string config;

    static void loadConfig(const std::string &filePath);

    static std::string get(std::string key);
};


#endif //TBATWITTERUPDATES_CONFIG_H
