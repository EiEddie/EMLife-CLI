#include <EMLife/EMLife.h>

ItemManager::ItemManager(const Maze* maze):
width(maze->GetWidth()), height(maze->GetHeight()) {
	srand(time(nullptr));
	
	// TODO: 更好的生成算法
	SetCoordList(maze);
}

void ItemManager::SetItem(int coin, int diamond) {
	try {
		for(int d=0; d<diamond; d++) {
			Coord coord = GetCoordFromVector(coord_list);
			items[coord.y*width + coord.x] = DIAMOND;
			diamond_count++;
		}
	} catch(std::out_of_range& error) {
		throw DiamondTooMuch();
	}
	
	try {
		for(int c=0; c<coin; c++) {
			Coord coord = GetCoordFromVector(coord_list);
			items[coord.y*width + coord.x] = COIN;
			coin_count++;
		}
	} catch(std::out_of_range& error) {
		throw CoinTooMuch(coin_count);
	}
}

void ItemManager::SetCoordList(const Maze* maze) {
	for(int y=1; y<maze->GetHeight(); y++) {
		for(int x=1; x<maze->GetWidth(); x+=2) {
			if(maze->GetBlock({x, y}) == ROAD && maze->GetBlock({x+1, y}) == ROAD)
				coord_list.emplace_back(x, y);
		}
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
