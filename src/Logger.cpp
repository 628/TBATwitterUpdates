#include <iostream>
#include "Logger.h"

#define RED "\033[91m"
#define BLUE "\033[34m"
#define YELLOW "\033[93m"
#define RESET "\033[0m"

void Logger::log(std::string log)
{
    std::cout << BLUE "LOG     | " RESET << log << std::endl;
}

void Logger::debug(std::string log)
{
    std::cout << YELLOW "DEBUG   | " RESET << log << std::endl;
}

void Logger::error(std::string log)
{
    std::cout << RED "ERROR   | " RESET << log << std::endl;
}
