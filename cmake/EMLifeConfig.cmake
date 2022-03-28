cmake_minimum_required(VERSION 3.19)
project(EMLife)


add_definitions(-DDEBUG)
message(STATUS "Add macro \"DEBUG\"")


find_package(spdlog CONFIG REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/../include")

file(GLOB_RECURSE SRC_FILE "${PROJECT_SOURCE_DIR}/../src/*")
list(FILTER SRC_FILE EXCLUDE REGEX "main")


add_library(EMLife ${SRC_FILE})

target_link_libraries(EMLife spdlog::spdlog spdlog::spdlog_header_only)