#ifndef TBATWITTERUPDATES_LOGGER_H
#define TBATWITTERUPDATES_LOGGER_H


#include <string>

class Logger {
public:
    static void log(std::string log);

    static void debug(std::string log);

    static void error(std::string log);
};


#endif //TBATWITTERUPDATES_LOGGER_H
