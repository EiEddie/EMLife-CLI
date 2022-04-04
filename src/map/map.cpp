#include <EMLife/EMLife.h>

ItemManager::ItemManager(const Maze* maze, int coin_count, int diamond_count) {
	items = new Item[maze->GetWidth()*maze->GetHeight()]{NONE};
	std::vector<Coord> coord_list;
	
	// TODO: 更好的生成算法
	for(int y=1; y<maze->GetHeight(); y++) {
		for(int x=1; x<maze->GetWidth(); x+=2) {
			if(maze->GetBlock({x, y}) == ROAD && maze->GetBlock({x+1, y}) == ROAD)
				coord_list.emplace_back(x, y);
		}
	}
	
	srand(time(nullptr));
	try {
		for(int i = 0; i < diamond_count; i++) {
			Coord coord = GetCoordFromVector(coord_list);
			items[coord.y*maze->GetWidth() + coord.x] = DIAMOND;
		}
		for(int i = 0; i < coin_count; i++) {
			Coord coord = GetCoordFromVector(coord_list);
			items[coord.y*maze->GetWidth() + coord.x] = COIN;
		}
	} catch(std::out_of_range& error) {
		throw ItemTooMuch();
	}
}

Coord ItemManager::GetCoordFromVector(std::vector<Coord>& vec) const {
	// TODO: 更好的写法
	/**
	 * \brief 共调用了多少次此函数
	 */
	static unsigned long count = 0;
	unsigned long size = vec.size() - count;
	
	if(size < 1)
		throw std::out_of_range("all extracted");
	
	int rand_index = rand()%size;
	
	Coord temp = vec[rand_index];
	std::rotate(vec.begin() + rand_index, vec.begin() + rand_index + 1, vec.end());
	count++;
	
	return temp;
}
