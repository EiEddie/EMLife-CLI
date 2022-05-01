#include <EMLife/EMLife.h>
#include <gtest/gtest.h>

#ifdef NO_SPDLOG_LIB
#include <cstdio>
#else
#include <spdlog/spdlog.h>
#endif //NO_SPDLOG_LIB

TEST(EMLifeTest, test_demon) {
	DemonManager::Demon demon(5);
	
	for(int i=0; i<5; i++)
		demon.SetPath(i, {i, i});
	
	// 正向走一遍
	for(int i=0; i<4; i++) {
		Coord pos = demon.GetPos();
#ifdef NO_SPDLOG_LIB
		printf("[\033[34mpos\033[0m] (%d, %d)", pos.x, pos.y);
#else
		spdlog::info("[\033[34mpos\033[0m] ({:d}, {:d})", pos.x, pos.y);
#endif //NO_SPDLOG_LIB
		EXPECT_EQ(Coord(i, i), pos);
		demon.Move();
	}
	// 转向
	
	// 反向走一遍
	for(int i=0; i<4; i++) {
		Coord pos = demon.GetPos();
#ifdef NO_SPDLOG_LIB
		printf("[\033[34mpos\033[0m] (%d, %d)", pos.x, pos.y);
#else
		spdlog::info("[\033[34mpos\033[0m] ({:d}, {:d})", pos.x, pos.y);
#endif //NO_SPDLOG_LIB
		EXPECT_EQ(Coord(4-i, 4-i), pos);
		demon.Move();
	}
	// 再转向
	
	// 正向再走一遍
	for(int i=0; i<4; i++) {
		Coord pos = demon.GetPos();
#ifdef NO_SPDLOG_LIB
		printf("[\033[34mpos\033[0m] (%d, %d)", pos.x, pos.y);
#else
		spdlog::info("[\033[34mpos\033[0m] ({:d}, {:d})", pos.x, pos.y);
#endif //NO_SPDLOG_LIB
		EXPECT_EQ(Coord(i, i), pos);
		demon.Move();
	}
}