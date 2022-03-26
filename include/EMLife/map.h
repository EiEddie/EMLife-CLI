#pragma once

#include <EMLife/EMLife.h>

#ifndef EMLIFE_MAP_H
#define EMLIFE_MAP_H
enum WallId {
	WALL_UP                 = 0b0001,
	WALL_DOWN               = 0b0010,
	WALL_DOWN_UP            = 0b0011,
	WALL_LEFT               = 0b0100,
	WALL_LEFT_UP            = 0b0101,
	WALL_LEFT_DOWN          = 0b0110,
	WALL_LEFT_DOWN_UP       = 0b0111,
	WALL_RIGHT              = 0b1000,
	WALL_RIGHT_UP           = 0b1001,
	WALL_RIGHT_DOWN         = 0b1010,
	WALL_RIGHT_DOWN_UP      = 0b1011,
	WALL_RIGHT_LEFT         = 0b1100,
	WALL_RIGHT_LEFT_UP      = 0b1101,
	WALL_RIGHT_LEFT_DOWN    = 0b1110,
	WALL_RIGHT_LEFT_DOWN_UP = 0b1111
};


static struct WallsChar {
private:
	wchar_t walls[0b1111 + 1] = {
		L'\u0020', // VOID
		L'\u2575', // UP
		L'\u2577', // DOWN
		L'\u2502', // DOWN_UP
		L'\u2574', // LEFT
		L'\u2518', // LEFT_UP
		L'\u2510', // LEFT_DOWN
		L'\u2524', // LEFT_DOWN_UP
		L'\u2576', // RIGHT
		L'\u2514', // RIGHT_UP
		L'\u250c', // RIGHT_DOWN
		L'\u251c', // RIGHT_DOWN_UP
		L'\u2500', // WALL_RIGHT_LEFT
		L'\u2534', // RIGHT_LEFT_UP
		L'\u252c', // RIGHT_LEFT_DOWN
		L'\u253c'  // RIGHT_LEFT_DOWN_UP
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
	UNDEFINED = -1,
	ROAD      =  0,
	WALL      =  1
};


/**
 * \brief 方向
 * 按坐标方式排列: 先横再纵, 先右再左, 先下再上
 */
enum Dir {
	RIGHT = 0,
	LEFT  = 1,
	DOWN  = 2,
	UP    = 3
};


struct Coord {
	int x, y;
	
	Coord(int x=-1, int y=-1):
	x(x), y(y) {}
};


class MazeBase {
protected:
	int width, height;
	
	Block* maze = new Block[width * height];
	
	inline int GetWallId(const Coord& coord) const {
		int id = 0;
		Coord dirs[4] = {
			{ 1,  0}, // RIGHT
			{-1,  0}, // LEFT
			{ 0,  1}, // DOWN
			{ 0, -1}  // UP
		};
		
		for(Coord dir: dirs) {
			id |= GetBlock(
				{coord.x + dir.x, coord.y + dir.y}
			) == WALL;
			id <<= 1;
		}
		
		return id >> 1;
	}
	
public:
	MazeBase(int w, int h, Block blk=WALL):
	width(w), height(h) {
		std::fill(maze, maze + width*height, blk);
	}
	
	~MazeBase() {
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
			return UNDEFINED;
	}
	
	inline int GetWidth() const {
		return width;
	}
	
	inline int GetHeight() const {
		return height;
	}
};


/**
 * \brief 源迷宫
 *
 * 横向间距为一格, 墙与路皆为一格
 *
 * \example
 * \verbatim
 * ┌───┬─┬───┐
 * │   │ │   │
 * ├─╴ ╵ ├─╴ │
 * │     │   │
 * ├───╴ └─╴ │
 * │         │
 * └─────────┘
 * \endverbatim
 */
class MazeSrc: public MazeBase {
public:
	MazeSrc(int w, int h, Block blk=WALL):
	MazeBase(w, h, blk) {}
};


/**
 * \brief 游戏逻辑与显示使用的迷宫
 *
 * 横向间距为两格
 *
 * \example
 * \verbatim
 * ┌─────┬──┬─────┐
 * │     │  │     │
 * ├──╴  ╵  ├──╴  │
 * │        │     │
 * ├─────╴  └──╴  │
 * │              │
 * └──────────────┘
 * \endverbatim
 */
class Maze: public MazeBase {
private:
	int width_src;
	
public:
	Maze(int w, int h, Block blk=WALL):
	width_src(w),
	MazeBase((w-1)/2*3 + 1, h, blk) {}
	
	/**
	 * \brief 获取迷宫字符串
	 * 使用完应delete
	 */
	const wchar_t* GetMazeStr() const;
	
	inline int GetSrcWidth() const {
		return width_src;
	}
	
	inline int GetSrcHeight() const {
		return height;
	}
};


class MazeBuilder {
private:
	Dir dirs_list[24][4]{};
	
	void GetDirs();
	
	static inline void Move(Coord& coord, Dir dir, int step=1) {
		Coord dirs[4] = {
			{ 1,  0}, // RIGHT
			{-1,  0}, // LEFT
			{ 0,  1}, // DOWN
			{ 0, -1}  // UP
		};
		
		coord.x += dirs[dir].x * step;
		coord.y += dirs[dir].y * step;
	}
	
	MazeSrc* GetMazeSrc(int w, int h) const;
	
	inline void DestroyMazeSrc(MazeSrc* maze) const {
		delete maze;
	}
	
	void MazeSrcToMaze(Maze* dest, MazeSrc* src) const;
	
public:
	MazeBuilder() {
		srand(time(nullptr));
		GetDirs();
	}
	
	inline Maze* GetMaze(int w, int h) const {
		MazeSrc* maze_src = GetMazeSrc(w, h);
		Maze* maze = new Maze(w, h);
		
		MazeSrcToMaze(maze, maze_src);
		
		DestroyMazeSrc(maze_src);
		return maze;
	}
	
	inline void DestroyMaze(Maze* maze) const {
		delete maze;
	}
};
#endif //EMLIFE_MAP_H
