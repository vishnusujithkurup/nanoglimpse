cmake_minimum_required(VERSION 3.11)

project(sandbox VERSION 1.0)

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

set(SOURCES
    TestApp.cc
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets.h
)

add_executable(sandbox ${SOURCES})

target_link_libraries(sandbox PRIVATE nanoglimpse)