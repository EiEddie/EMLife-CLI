#include <EMLife/EMLife.h>

const wchar_t* Maze::GetMazeStr() const {
	// 横向空隙为两格, 包含换行符与字符串尾\0字符
	wchar_t* str = new wchar_t[(width + 1)*height + 1]{0};
	std::fill(str, str + (width + 1)*height + 1, L' ');
	
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x+=y&0b1? 3: x%3 + 1) {
			if(GetBlock({x, y}) != WALL)
				continue;
			
			int wall_id = GetWallId({x, y});
			if(x % 3) {
				// 两格宽
				str[y*(width + 1) + x]     = walls_char.Get(wall_id);
				str[y*(width + 1) + x + 1] = walls_char.Get(WALL_RIGHT_LEFT);
			} else {
				// 一格宽
				str[y*(width + 1) + x]     = walls_char.Get(wall_id);
			}
		}
		str[(y + 1)*(width + 1) - 1] = L'\n';
	}
	str[(width + 1)*height] = L'\0';
	
	return str;
}


void MazeBuilder::GetDirs() {
	Dir dirs[4] = {RIGHT, LEFT, DOWN, UP};
	int i = 0;
	do {
		std::copy(dirs, dirs + 4, dirs_list[i++]);
	} while(std::next_permutation(dirs, dirs + 4));
}

MazeSrc* MazeBuilder::GetMazeSrc(int w, int h) const {
	// 初始化迷宫, 将迷宫每个点设置为0且加入起点, 起点恒为(1, 1)
	MazeSrc* maze = new MazeSrc(w, h);
	MazeSrc* maze_temp = new MazeSrc(w, h, UNDEFINED);
	
	std::stack<Coord> walls;
	walls.push({1, 1});
	
	while(!walls.empty()) {
		// 在 walls 中选取一点并删除
		Coord road_coord = walls.top();
		walls.pop();
		maze->SetBlock(road_coord, ROAD);
		
		// 将 road_point 与其四周随机一个路点打通
		const Dir* dirs = dirs_list[rand()%24]; //NOLINT
		for(int i=0; i<4; i++) {
			Coord road_coord_temp = road_coord;
			Move(road_coord_temp, dirs[i], 2);
			if(maze_temp->GetBlock(road_coord_temp) == ROAD) {
				maze->SetBlock(
					{(road_coord.x + road_coord_temp.x)/2,
					 (road_coord.y + road_coord_temp.y)/2},
					ROAD
				);
				maze_temp->SetBlock(
					{(road_coord.x + road_coord_temp.x)/2,
					 (road_coord.y + road_coord_temp.y)/2},
					ROAD
				);
				break;
			}
		}
		
		// 将 road_point 设置为路
		maze_temp->SetBlock(road_coord, ROAD);
		
		// 加入 road_point 周围不在 walls 中的墙点
		for(int i=0; i<4; i++) {
			Coord road_coord_temp = road_coord;
			Move(road_coord_temp, dirs[i], 2);
			if(
					maze_temp->In(road_coord_temp)
					&& maze_temp->GetBlock(road_coord_temp) == UNDEFINED
			) {
				maze_temp->SetBlock(road_coord_temp, WALL);
				walls.push(road_coord_temp);
			}
		}
	}
	
	delete maze_temp;
	return maze;
}

void MazeBuilder::MazeSrcToMaze(Maze* dest, MazeSrc* src) const {
	for(int y=0; y<src->GetHeight(); y++) {
		for(int x=0; x<src->GetWidth(); x++) {
			Block blk = src->GetBlock({x, y});
			if(x & 0b1) {
				// 奇数
				dest->SetBlock({x*3/2    , y}, blk);
				dest->SetBlock({x*3/2 + 1, y}, blk);
			} else {
				// 偶数
				dest->SetBlock({x/2*3,     y}, blk);
			}
		}
	}
}
