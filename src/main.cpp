#include <EMLife/EMLife.h>

int main() {
	MazeBuilder mb;
	
	Maze* maze = mb.GetMaze(11, 11);
	Show(maze, "maze");
	mb.DestroyMaze(maze);
	
	return 0;
}