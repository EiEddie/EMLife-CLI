#include <EMLife/EMLife.h>

int main() {
	MazeBuilder mb;
	
	Maze* maze = mb.GetMaze(31, 31);
	Show(maze);
	mb.DestroyMaze(maze);
	
	return 0;
}