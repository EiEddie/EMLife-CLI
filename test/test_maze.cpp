#include <EMLife/EMLife.h>
#include <gtest/gtest.h>

TEST(EMLifeTest, test_maze) {
	setlocale(LC_ALL, "");
	MazeBuilder mb;
	
	int width = 11, height = 11;
	
	Maze* maze = mb.GetMaze(width, height);
	const wchar_t* str = maze->GetMazeStr();
	printf("%ls\n", str);
	mb.DestroyMaze(maze);
	delete[] str;
}