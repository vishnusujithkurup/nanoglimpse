cmake_minimum_required(VERSION 3.11)

project(nanoglimpse VERSION 1.0)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Application.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Log.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Window.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/LayerStack.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Input.cc
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/TimeUtils.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/Context.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/Shader.cc
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

add_library(nanoglimpse SHARED ${SOURCES})

target_compile_definitions(nanoglimpse PRIVATE NG_BUILD_SHARED)
target_compile_definitions(nanoglimpse PRIVATE GLFW_INCLUDE_NONE)

target_include_directories(nanoglimpse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(nanoglimpse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog/include)
target_include_directories(nanoglimpse PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include)
target_include_directories(nanoglimpse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glm)
target_include_directories(nanoglimpse PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)

target_link_libraries(nanoglimpse PRIVATE spdlog::spdlog_header_only)
target_link_libraries(nanoglimpse PRIVATE glfw)
target_link_libraries(nanoglimpse PRIVATE glm::glm)
target_link_libraries(nanoglimpse PRIVATE glad)