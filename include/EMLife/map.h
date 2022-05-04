#pragma once

#include <EMLife/EMLife.h>

#ifndef EMLIFE_MAP_H
#define EMLIFE_MAP_H


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
	
	bool operator==(const Coord& val) const {
		if(x == val.x && y == val.y)
			return true;
		else
			return false;
	}
	
	bool operator!=(const Coord& val) const {
		return !(*this == val);
	}
};


class Maze {
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
	explicit Maze(int w, int h, Block blk=WALL):
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
	
	/**
	 * \return 是否成功设置
	 * \retval  1 成功
	 * \retval -1 失败: 坐标不在迷宫内
	 */
	inline int SetBlock(const Coord& coord, Block blk) {
		if(In(coord)) {
			maze[coord.y*width + coord.x] = blk;
			return 1;
		} else {
			return -1;
		}
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
	
public:
	explicit MazeBuilder() {
		srand(time(nullptr));
		GetDirs();
	}
	
	Maze* GetMaze(int w, int h) const;
	
	inline void DestroyMaze(Maze* maze) const {
		delete maze;
	}
};


/**
 * \brief 迷宫中的物品
 **/
enum Item {
	NONE    = 0,
	COIN    = 1,
	DIAMOND = 2
};


// TODO: 完成此类
/**
 * \brief 生成与管理迷宫中的物品
 */
class ItemManager {
private:
	const Maze* maze;
	
	int width, height;
	
	Item* items = new Item[width*height]{NONE};
	
	Coord maze_endpoint;
	
private:
	void SetCoordList(std::vector<Coord>* coord_list);
	
	int SetItem(int coin, int diamond, const std::vector<Coord>& coord_list);
	
public:
	explicit ItemManager(const Maze* maze):
	maze(maze), width(maze->GetWidth()), height(maze->GetHeight()) {
		srand(time(nullptr));
	}
	
	~ItemManager() {
		delete[] items;
	}
	
	inline int Init(int coin, int diamond) {
		std::vector<Coord> coord_list;
		
		SetCoordList(&coord_list);
		
		// 打乱列表
		std::shuffle(
			coord_list.begin(), coord_list.end(),
			std::mt19937(std::random_device()())
		);
		
		return SetItem(coin, diamond, coord_list);
	}
	
	inline Coord GetMazeEndPoint() const {
		return maze_endpoint;
	}
	
	inline Item GetItem(const Coord& coord) const {
		if(!maze->In(coord))
			return NONE;
		
		return items[coord.x + coord.y*width];
	}
	
	inline int GetWidth() const {
		return width;
	}
	
	inline int GetHeight() const {
		return height;
	}
};


// TODO: 完成此类
/**
 * \brief 管理迷宫中游荡的怪物
 */
class DemonManager {
#ifdef DEBUG
public:
#else
private:
#endif // DEBUG
	int demon_count = 0;
	
	/**
	 * \brief 怪物
	 */
	struct Demon {
	private:
		/**
		 * \brief demon总步数
		 */
		int step_count;
		
		/**
		 * \brief demon的移动路径
		 */
		Coord* path = new Coord[step_count];
		
		/**
		 * \brief demon当前位置在path内的下标
		 */
		int coord_index = 0;
		
		/**
		 * \brief 行进方向
		 *
		 *  1 正向
		 * -1 反向
		 */
		int dir = 1;
		
	public:
		explicit Demon(int step_count=5):
		step_count(step_count) {}
		
		~Demon() {
			delete[] path;
		}
		
		/**
		 * \param step_len 步长
		 */
		inline void Move(int step_len=1) {
			// 若到达路径头或尾, 反向运动
			if(coord_index + dir == -1 || coord_index + dir == step_count)
				dir *= -1;
			
			coord_index += dir*step_len;
		}
		
		/**
		 * \return 是否成功设置
		 * \retval  0 成功
		 * \retval -1 失败: 下标越界
		 */
		inline int SetPath(int index, const Coord& coord) {
			if(index > -1 && index < step_count) {
				path[index] = coord;
				return SUCCESS;
			} else {
				return -1;
			}
		}
		
		inline Coord GetPos() {
			return path[coord_index];
		}
	}* demons = nullptr;
	
	
	struct Node {
		Node* last = nullptr;
		Node* next[4] = {nullptr};
		
		Coord value;
		
		Node(const Coord& coord) {
			value = coord;
		}
		
		~Node() {
			for(Node*& i: next)
				delete i;
		}
	};
	
	Node* point_tree = nullptr;
	
	Node* maze_endpoint = nullptr;
	
private:
	static inline Coord MoveCoord(Coord coord, int dir, int step= 1) {
		Coord dirs[4] = {
			{ 1,  0}, // RIGHT
			{-1,  0}, // LEFT
			{ 0,  1}, // DOWN
			{ 0, -1}  // UP
		};
		
		coord.x += dirs[dir].x*step;
		coord.y += dirs[dir].y*step;
		
		return coord;
	}
	
	/**
	 * \brief 根据迷宫创建树
	 */
	void CreateTree(
			Coord coord,
			Node* last, Node*& now,
			const Maze* maze, const Coord& endpoint
	);
	
	/**
	 * \brief 在指定节点创建demon
	 *
	 * \param steps 步数
	 *
	 * \retval  0 成功
	 * \retval -1 失败: 不是岔路
	 * \retval -2 失败: 位置不够
	 */
	int SetDemon(const Node* pos, int steps);
	
public:
	explicit DemonManager(int demon_count):
	demons(new Demon[demon_count]) {}
	
	~DemonManager() {
		delete[] demons;
		delete point_tree;
	}
	
	void Init(const Maze* maze, const Coord& endpoint, int demon_step_count=5);
};


/**
 * \brief 游戏地图
 */
class Map {
private:
	Maze* maze;
	
public:
	Map(int w, int h):
	maze(new Maze(w, h)) {}
};
#endif //EMLIFE_MAP_H
