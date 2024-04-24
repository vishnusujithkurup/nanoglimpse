cmake_minimum_required(VERSION 3.11)

project(stb_image VERSION 1.0)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image.cc
)

add_library(stb_image STATIC ${SOURCES})

set_property(TARGET stb_image PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)