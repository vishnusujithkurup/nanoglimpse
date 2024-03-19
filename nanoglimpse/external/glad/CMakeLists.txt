cmake_minimum_required(VERSION 3.11)

project(glad VERSION 1.0)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
)

add_library(glad STATIC ${SOURCES})

set_property(TARGET glad PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)