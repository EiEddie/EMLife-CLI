#include <EMLife/EMLife.h>
#include <iostream>

int main() {
	MazeBuilder mb;
	
	setlocale(LC_ALL, "");
	Maze* maze = mb.GetMaze(31, 31);
	const wchar_t* str = maze->GetMazeStr();
	printf("%ls\n", str);
	mb.DestroyMaze(maze);
	delete[] str;
	
	return 0;
}
