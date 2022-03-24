#pragma once

#include <EMLife/EMLife.h>

#ifndef EMLIFE_MAP_H
#define EMLIFE_MAP_H
enum WallId {
	UP                 = 0b0001,
	DOWN               = 0b0010,
	DOWN_UP            = 0b0011,
	LEFT               = 0b0100,
	LEFT_UP            = 0b0101,
	LEFT_DOWN          = 0b0110,
	LEFT_DOWN_UP       = 0b0111,
	RIGHT              = 0b1000,
	RIGHT_UP           = 0b1001,
	RIGHT_DOWN         = 0b1010,
	RIGHT_DOWN_UP      = 0b1011,
	RIGHT_LEFT         = 0b1100,
	RIGHT_LEFT_UP      = 0b1101,
	RIGHT_LEFT_DOWN    = 0b1110,
	RIGHT_LEFT_DOWN_UP = 0b1111
};


static struct WallsChar {
private:
	wchar_t walls[0b1111 + 1] = {
		L'\0',
		L'\u2575',
		L'\u2577',
		L'\u2502',
		L'\u2574',
		L'\u2518',
		L'\u2510',
		L'\u2524',
		L'\u2576',
		L'\u2514',
		L'\u250c',
		L'\u251c',
		L'\u2500',
		L'\u2534',
		L'\u252c',
		L'\u253c'
	};
	
public:
	wchar_t Get(int id) const {
		return walls[id];
	}
	
	wchar_t Get(WallId id) const {
		return walls[id];
	}
} walls_char;


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
	
	inline int GetWallId(const Coord& coord) const {
		int id = 0;
		Coord dirs[4] = {
			{ 1,  0}, // right
			{-1,  0}, // left
			{ 0,  1}, // down
			{ 0, -1}  // up
		};
		
		for(Coord dir: dirs) {
			id |= GetBlock(
				{coord.x + dir.x, coord.y + dir.y}
			) == wall;
			id <<= 1;
		}
		
		return id >> 1;
	}
	
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
	
	inline int GetWidth() const {
		return width;
	}
	
	inline int GetHeight() const {
		return height;
	}
	
	/**
	 * \brief 获取迷宫字符串
	 * 使用完应delete
	 */
	const wchar_t* GetMazeStr() const ;
};


class MazeBuilder {
private:
	Dir dirs_list[24][4]{};
	
	void GetDirs();
	
	static inline void Move(Coord& coord, Dir dir, int step=1) {
		Coord dirs[4] = {
			{ 1,  0}, // right
			{-1,  0}, // left
			{ 0,  1}, // down
			{ 0, -1}  // up
		};
		
		coord.x += dirs[dir].x * step;
		coord.y += dirs[dir].y * step;
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

// FIXME: 调试使用
void Show(Maze* maze);
#endif //EMLIFE_MAP_H
