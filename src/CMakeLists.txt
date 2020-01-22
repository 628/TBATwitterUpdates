cmake_minimum_required(VERSION 3.14)
project(TBATwitterUpdates)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp
        HttpRequest.cpp
        HttpRequest.h
        twitter/Twitter.cpp
        twitter/Twitter.h
        httpserver/handlers/WebhookHandler.cpp
        httpserver/handlers/WebhookHandler.h
        Config.cpp
        Config.h httpserver/headers/XTBAChecksum.h Logger.cpp Logger.h)

include_directories(${HEADER_SEARCH_PATHS} /usr/include/nlohmann)

target_link_libraries(${PROJECT_NAME} pistache ${LIBRARIES_SEARCH_PATHS} curl oauth pthread cryptopp)