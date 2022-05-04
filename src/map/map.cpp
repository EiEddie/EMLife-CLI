#include <EMLife/EMLife.h>
#include <EMLife/map.h>


WarningManager warning_manager;


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
		if(iter == coord_list.end()) {
			// 记录警告
			warning_manager.CreateFailedToSpecifyAllCoin(coin_c);
			break;
		}
		
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


void DemonManager::CreateTree(
		Coord coord,
		Node* last, Node*& now,
		const Maze* maze, const Coord& endpoint
) {
	if(maze->GetBlock(coord) != ROAD)
		return;
	
	if(now == nullptr)
		now = new Node(coord);
	now->last = last;
	
	// 储存终点节点位置
	if(now->value == endpoint)
		maze_endpoint = now;
	
	for(int i=0; i<4; i++) {
		Coord next_coord = MoveCoord(coord, i);
		// 如果此位置已被记录, 跳过
		if(last != nullptr) {
			if(last->value == next_coord)
				continue;
		}
		
		CreateTree(next_coord, now, now->next[i], maze, endpoint);
	}
}

int DemonManager::SetDemon(const Node* pos, int steps) {
	// 如果是树的根部
	if(pos->last == nullptr)
		return -1;
	
	// FIXME: 完成函数
}

void DemonManager::Init(const Maze* maze, const Coord& endpoint, int demon_step_count) {
	CreateTree({1, 1}, nullptr, point_tree, maze, endpoint);
	
	// TODO: 添加demon
}
