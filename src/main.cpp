#include <EMLife/EMLife.h>

int main() {
	MazeBuilder mb;
	
	Maze* maze = mb.GetMaze(11, 11);
	const wchar_t* str = maze->GetMazeStr();
//	wprintf(str);
	Show(maze);
	mb.DestroyMaze(maze);
	delete[] str;
	
	return 0;
}
