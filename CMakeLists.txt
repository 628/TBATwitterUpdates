cmake_minimum_required(VERSION 3.14)
project(TBATwitterUpdates)

set(CMAKE_CXX_STANDARD 14)

add_executable(TBATwitterUpdates main.cpp twitterwrapper/HttpRequest.cpp twitterwrapper/HttpRequest.h)

target_link_libraries(TBATwitterUpdates curl)
target_link_libraries(TBATwitterUpdates oauth)