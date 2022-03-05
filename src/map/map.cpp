#include <EMLife/EMLife.h>

void Show(Maze* maze, const char msg[]) {
	printf("\n%s\n", msg);
	for(int i=0; i<11; i++) {
		for(int j=0; j<11; j++) {
			if(maze->GetBlock({i, j}) == wall)
				printf("🟥 ");
			else if(maze->GetBlock({i, j}) == road)
				printf("🟦 ");
			else if(maze->GetBlock({i, j}) == undefined)
				printf("🟨 ");
		}
		putc('\n', stdout);
	}
	fflush(stdout);
}

void MazeBuilder::GetDirs() {
	Dir dirs[4] = {right, left, down, up};
	int i = 0;
	do {
		std::copy(dirs, dirs + 4, dirs_list[i++]);
	} while(std::next_permutation(dirs, dirs + 4));
}

Maze* MazeBuilder::GetMaze(int w, int h) {
	Maze* maze = new Maze(w, h);
	Maze* maze_temp = new Maze(w, h, undefined);
	
	std::vector<Coord> walls = {{1, 1}};
	
	while(!walls.empty()) {
		Coord road_coord = RandSample(walls); // TODO: 是否需要随机取样
		maze->SetBlock(road_coord, road);
		
		Dir* dirs = dirs_list[rand()%24]; //NOLINT
		for(int i=0; i<4; i++) {
			Coord road_coord_temp = road_coord;
			Move(road_coord_temp, dirs[i], 2);
			if(maze_temp->GetBlock(road_coord_temp) == road) {
				maze->SetBlock(
					{(road_coord.x + road_coord_temp.x)/2 ,
					 (road_coord.y + road_coord_temp.y)/2},
					road
				);
				maze_temp->SetBlock(
					{(road_coord.x + road_coord_temp.x)/2 ,
					 (road_coord.y + road_coord_temp.y)/2},
					road
				);
				break;
			}
		} // TODO: 封装为函数
		
		maze_temp->SetBlock(road_coord, road);
		
		for(int i=0; i<4; i++) {
			Coord road_coord_temp = road_coord;
			Move(road_coord_temp, dirs[i], 2);
			if(
					maze_temp->In(road_coord_temp)
					&& maze_temp->GetBlock(road_coord_temp) == undefined
			) {
				maze_temp->SetBlock(road_coord_temp, wall);
				walls.push_back(road_coord_temp);
			}
		}
		
		Show(maze, "maze");
		Show(maze_temp, "maze temp");
	}
	
	delete maze_temp;
	return maze;
}