cmake_minimum_required(VERSION 3.11)

project(nanoglimpse VERSION 1.0)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Application.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Log.cc
)

add_library(nanoglimpse SHARED ${SOURCES})

target_compile_definitions(nanoglimpse PRIVATE NG_BUILD_SHARED)

target_include_directories(nanoglimpse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(nanoglimpse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog/include)