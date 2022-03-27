cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 14)
project(EMLife_Test)


set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(EMLife_DIR ${PROJECT_SOURCE_DIR}/../cmake)
find_package(EMLife CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)


# test_maze
set(TEST_MAZE_FILE
	"${PROJECT_SOURCE_DIR}/test_maze.cpp"
)
add_executable(test_maze ${TEST_MAZE_FILE})

target_link_libraries(test_maze
	EMLife
	GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main
)
