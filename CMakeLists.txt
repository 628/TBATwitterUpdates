cmake_minimum_required(VERSION 3.14)
project(TBATwitterUpdates)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp
        src/HttpRequest.cpp
        src/HttpRequest.h
        src/twitter/Twitter.cpp
        src/twitter/Twitter.h
        src/httpserver/handlers/WebhookHandler.cpp
        src/httpserver/handlers/WebhookHandler.h
        src/Config.cpp
        src/Config.h src/httpserver/headers/XTBAChecksum.h src/Logger.cpp src/Logger.h)

include_directories(${HEADER_SEARCH_PATHS} /usr/include/nlohmann)

target_link_libraries(${PROJECT_NAME} pistache ${LIBRARIES_SEARCH_PATHS} curl oauth pthread cryptopp)