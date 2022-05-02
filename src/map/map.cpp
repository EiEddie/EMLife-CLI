#include <EMLife/EMLife.h>

int ItemManager::SetItem(int coin, int diamond, const std::vector<Coord>& coord_list) {
	auto iter = coord_list.begin();
	
	// 设置终点
	if(iter == coord_list.end())
		return FAILED_TO_SPECIFY_ENDPOINT;
	maze_endpoint = *iter++;
	
	// 添加diamond
	for(int d=0; d<diamond; d++) {
		if(iter == coord_list.end())
			return FAILED_TO_SPECIFY_ALL_DIAMOND;
		
		items[iter->x + iter->y*width] = DIAMOND;
		iter++;
	}
	
	// 添加coin
	int coin_c = 0;
	for(; coin_c<coin; coin_c++) {
		if(iter == coord_list.end())
			// TODO: 记录此处WARNING
			break;
		
		items[iter->x + iter->y*width] = COIN;
		iter++;
	}
	
	return SUCCESS;
}

void ItemManager::SetCoordList(std::vector<Coord>* coord_list) {
	for(int y=1; y<maze->GetHeight(); y++) {
		for(int x=1; x<maze->GetWidth(); x++) {
			// 不将点(1, 1)存入, 因为它是出生点
			if(x == 1 && y == 1)
				continue;
			
			if(maze->GetBlock({x, y}) == ROAD)
				coord_list->emplace_back(x, y);
		}
	}
}
