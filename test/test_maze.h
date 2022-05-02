#include <EMLife/EMLife.h>
#include <cstdio>

#ifndef EMLIFE_TEST_MAZE_H
#define EMLIFE_TEST_MAZE_H
void ShowMaze(const Maze* maze) {
	for(int y=0; y<maze->GetHeight(); y++) {
		for(int x=0; x<maze->GetWidth(); x++) {
			putc(maze->GetBlock({x, y}) == WALL? '#': ' ', stdout);
		}
		putc('\n', stdout);
	}
	
	fflush(stdout);
}

void ShowItems(const ItemManager* im) {
	for(int y=0; y<im->GetHeight(); y++) {
		for(int x=0; x<im->GetWidth(); x++) {
			Item temp = im->GetItem({x, y});
			switch(temp) {
			case NONE:
				printf("  ");
				break;
			case COIN:
				printf("🪙");
				break;
			case DIAMOND:
				printf("💎");
				break;
			}
			
			if(im->GetMazeEndPoint() == Coord(x, y))
				printf("🚩");
		}
		putc('\n', stdout);
	}
	
	fflush(stdout);
}
#endif //EMLIFE_TEST_MAZE_H
