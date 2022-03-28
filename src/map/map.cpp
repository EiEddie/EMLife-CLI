#include <EMLife/EMLife.h>

ItemManager::ItemManager(Maze* maze, int coin_count, int diamond_count) {
	items = new Item[maze->GetWidth()*maze->GetHeight()]{NONE};
	// TODO: 填充硬币与钻石, 不可重叠
}
