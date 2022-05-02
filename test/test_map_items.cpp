#include <EMLife/EMLife.h>
#include <gtest/gtest.h>
#include "test_maze.h"

TEST(EMLifeTest, test_map_items) {
	setlocale(LC_ALL, "");
	
	MazeBuilder mb;
	
	int width = 11, height = 11;
	
	Maze* maze = mb.GetMaze(width, height);
	ShowMaze(maze);
	
	ItemManager im(maze);
	im.Init(10, 10);
	ShowItems(&im);
	
	mb.DestroyMaze(maze);
}