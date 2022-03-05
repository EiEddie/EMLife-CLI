#pragma once

#include <EMLife/EMLife.h>


#ifndef EMLIFE_MAP_H
#define EMLIFE_MAP_H
enum Block {
	undefined = -1,
	road      =  0,
	wall      =  1
};


/**
 * \brief 方向
 * 按坐标方式排列: 先横再纵, 先右再左, 先下再上
 */
enum Dir {
	right = 0,
	left  = 1,
	down  = 2,
	up    = 3
};


struct Coord {
	int x, y;
	
	Coord(int x=-1, int y=-1):
	x(x), y(y) {}
};


struct Maze {
private:
	int width, height;
	
	Block* maze = new Block[width * height];
	
public:
	Maze(int w, int h, Block blk=wall):
	width(w), height(h) {
		std::fill(maze, maze + width*height, blk);
	}
	
	~Maze() {
		delete[] maze;
	}
	
	/**
	 * \brief 坐标是否在迷宫区域内
	 */
	inline bool In(const Coord& coord) const {
		bool temp = coord.x >= 0 && coord.x < width;
		temp &= coord.y >= 0 && coord.y < height;
		return temp;
	}
	
	inline void SetBlock(const Coord& coord, Block blk) {
		if(In(coord))
			maze[coord.y*width + coord.x] = blk;
	}
	
	inline Block GetBlock(const Coord& coord) const {
		if(In(coord))
			return maze[coord.y*width + coord.x];
		else
			return undefined;
	}
};


class MazeBuilder {
private:
	Dir dirs_list[24][4];
	
	void GetDirs();
	
	static inline void Move(Coord& coord, Dir dir, int step=1) {
		switch(dir) {
		case right:
			coord.x += step;
			break;
		case left:
			coord.x -= step;
			break;
		case down:
			coord.y += step;
			break;
		case up:
			coord.y -= step;
			break;
		}
	}
	
	/**
	 * \brief 不放回随机抽样
	 */
	static inline Coord RandSample(std::vector<Coord>& list) {
		int rand_num = rand()%list.size(); // NOLINT
		Coord rand_element = list[rand_num];
		list.erase(list.begin() + rand_num);
		return rand_element;
	}
	
public:
	MazeBuilder() {
		srand(time(nullptr));
		GetDirs();
	}
	
	Maze* GetMaze(int w, int h);
	
	inline void DestroyMaze(Maze* maze) {
		delete maze;
	}
};

void Show(Maze* maze, const char msg[]);
#endif //EMLIFE_MAP_H
