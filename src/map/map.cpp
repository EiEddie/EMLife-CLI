#include <EMLife/EMLife.h>

const wchar_t* Maze::GetMazeStr() const {
	wchar_t* str = new wchar_t[2*width*height + 1]{0};
	std::fill(str, str + (2*width)*height + 1, L' ');
	
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x+=(y&0b1) + 1) {
			if(GetBlock({x, y}) != wall)
				continue;
			
			int wall_id = GetWallId({x, y});
			str[2*y*width + 2*x] = walls_char.Get(wall_id);
			if(wall_id & 0b1000)
				str[2*y*width + 2*x + 1] = walls_char.Get(RIGHT_LEFT);
		}
		str[2*width*(y + 1) - 1] = L'\n';
	}
	str[2*width*height] = L'\0';
	
	return str;
}


void MazeBuilder::GetDirs() {
	Dir dirs[4] = {right, left, down, up};
	int i = 0;
	do {
		std::copy(dirs, dirs + 4, dirs_list[i++]);
	} while(std::next_permutation(dirs, dirs + 4));
}

Maze* MazeBuilder::GetMaze(int w, int h) {
	// 初始化迷宫, 将迷宫每个点设置为0且加入起点, 起点恒为(1, 1)
	Maze* maze = new Maze(w, h);
	Maze* maze_temp = new Maze(w, h, undefined);
	
	std::stack<Coord> walls;
	walls.push({1, 1});
	
	while(!walls.empty()) {
		// 在 walls 中随随机选取一点并删除
		Coord road_coord = walls.top();
		walls.pop();
		maze->SetBlock(road_coord, road);
		
		// 将 road_point 与其四周随机一个路点打通
		Dir* dirs = dirs_list[rand()%24]; //NOLINT
		for(int i=0; i<4; i++) {
			Coord road_coord_temp = road_coord;
			Move(road_coord_temp, dirs[i], 2);
			if(maze_temp->GetBlock(road_coord_temp) == road) {
				maze->SetBlock(
					{(road_coord.x + road_coord_temp.x)/2,
					 (road_coord.y + road_coord_temp.y)/2},
					road
				);
				maze_temp->SetBlock(
					{(road_coord.x + road_coord_temp.x)/2,
					 (road_coord.y + road_coord_temp.y)/2},
					road
				);
				break;
			}
		}
		
		// 将 road_point 设置为路
		maze_temp->SetBlock(road_coord, road);
		
		// 加入 road_point 周围不在 walls 中的墙点
		for(int i=0; i<4; i++) {
			Coord road_coord_temp = road_coord;
			Move(road_coord_temp, dirs[i], 2);
			if(
					maze_temp->In(road_coord_temp)
					&& maze_temp->GetBlock(road_coord_temp) == undefined
			) {
				maze_temp->SetBlock(road_coord_temp, wall);
				walls.push(road_coord_temp);
			}
		}
	}
	
	delete maze_temp;
	return maze;
}
