cmake_minimum_required(VERSION 3.28)
project(libs CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Dynamic::LIBS ALIAS ${PROJECT_NAME})