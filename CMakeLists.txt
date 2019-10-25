cmake_minimum_required(VERSION 3.14)
project(TBATwitterUpdates)

set(CMAKE_CXX_STANDARD 14)

add_executable(TBATwitterUpdates main.cpp
        twitterwrapper/HttpRequest.cpp
        twitterwrapper/HttpRequest.h
        twitterwrapper/Twitter.cpp
        twitterwrapper/Twitter.h)

set(PISTACHE_INCLUDE_DIR "httpserver/pistache/include")
set(HEADER_SEARCH_PATHS ${PISTACHE_INCLUDE_DIR})
set(PISTACHE_LIBRARY "${PROJECT_SOURCE_DIR}/httpserver/pistache/lib/src/libpistache.a")
set(LIBRARIES_SEARCH_PATHS ${PISTACHE_LIBRARY})

include_directories(${HEADER_SEARCH_PATHS})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
target_link_libraries(TBATwitterUpdates curl)
target_link_libraries(TBATwitterUpdates oauth)