#include <EMLife/EMLife.h>
#include <gtest/gtest.h>
#include "test_maze.h"

TEST(EMLifeTest, test_map_items) {
	setlocale(LC_ALL, "");
	
	// 生成迷宫
	MazeBuilder mb;
	int width = 11, height = 11;
	Maze* maze = mb.GetMaze(width, height);
	printf("Maze:\n");
	ShowMaze(maze);
	
	putc('\n', stdout);
	
	// 向迷宫内添加适量物品
	ItemManager im1(maze);
	int coin1 = 10, diamond1 = 10;
	im1.Init(coin1, diamond1);
	printf("items(coin*%d, diamond*%d) in maze:\n", coin1, diamond1);
	ShowItems(&im1);
	
	putc('\n', stdout);
	
	// 向迷宫内添加超过迷宫中空格数的物品
	// 用于测试错误报告功能
	ItemManager im2(maze);
	int coin2 = 100, diamond2 = 10;
	im2.Init(coin2, diamond2);
	printf("items(coin*%d, diamond*%d) in maze:\n", coin2, diamond2);
	ShowItems(&im2);
	
	warning_manager.PrintAll();
	
	mb.DestroyMaze(maze);
}