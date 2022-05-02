#include <EMLife/EMLife.h>
#include <gtest/gtest.h>

TEST(EMLifeTest, test_except) {
	ErrorManager em;
	
	em.CreateError(FAILED_TO_SPECIFY_ENDPOINT);
	em.CreateError(FAILED_TO_SPECIFY_ALL_DIAMOND);
	
	em.PrintAll();
	
	
	WarningManager wm;
	
	wm.CreateFailedToSpecifyAllCoin(10);
	
	wm.PrintAll();
}