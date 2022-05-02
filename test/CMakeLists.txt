cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
project(EMLife_Test)


set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(EMLife_DIR ${PROJECT_SOURCE_DIR}/../cmake)
find_package(EMLife CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG)

if(NOT spdlog_FOUND)
	add_definitions(-DNO_SPDLOG_LIB)
	message(STATUS "Add macro \"NO_SPDLOG_LIB\"")
endif()

# test_maze
set(TEST_MAZE_FILE
	"${PROJECT_SOURCE_DIR}/test_maze.cpp"
)
add_executable(test_maze ${TEST_MAZE_FILE})

target_link_libraries(test_maze
	EMLife
	GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main
)


# test_demon
set(TEST_DEMON_FILE
	"${PROJECT_SOURCE_DIR}/test_demon.cpp"
)
add_executable(test_demon ${TEST_DEMON_FILE})

target_link_libraries(test_demon
	EMLife
	GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main
	spdlog::spdlog spdlog::spdlog_header_only
)


# test_map_items
set(TEST_MAP_ITEMS_FILE
	"${PROJECT_SOURCE_DIR}/test_map_items.cpp"
)
add_executable(test_map_items ${TEST_MAP_ITEMS_FILE})

target_link_libraries(test_map_items
	EMLife
	GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main
)
