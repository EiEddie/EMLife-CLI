#include <EMLife/EMLife.h>
#include <iostream>

int main() {
	setlocale(LC_ALL, "");
	MazeBuilder mb;
	
	int width = 11, height = 11;
	scanf("%d%d", &width, &height);
	
	Maze* maze = mb.GetMaze(width, height);
	const wchar_t* str = maze->GetMazeStr();
	printf("%ls\n", str);
	mb.DestroyMaze(maze);
	delete[] str;
	
	return 0;
}
