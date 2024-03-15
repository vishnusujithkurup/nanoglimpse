cmake_minimum_required(VERSION 3.11)

project(nanoglimpse-all)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions(NG_DEBUG)

if(WIN32)
    add_compile_definitions(NG_PLATFORM_WINDOWS)
elseif(APPLE)
    add_compile_definitions(NG_PLATFORM_APPLE)
elseif(UNIX)
    add_compile_definitions(NG_PLATFORM_LINUX)
else()
    message(FATAL_ERROR "nanoglimpse build failed!\nERROR: Unknown platform.")
endif()

add_subdirectory(nanoglimpse)
add_subdirectory(sandbox)