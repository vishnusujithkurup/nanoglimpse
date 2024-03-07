cmake_minimum_required(VERSION 3.11)

project(sandbox VERSION 1.0)

set(SOURCES
    TestApp.cc
)

add_executable(sandbox ${SOURCES})

target_link_libraries(sandbox PRIVATE nanoglimpse)