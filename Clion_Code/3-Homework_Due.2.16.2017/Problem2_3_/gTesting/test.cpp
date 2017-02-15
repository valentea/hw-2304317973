#include "llistint.h"
#include "gtest/gtest.h"

class LListIntTest : public testing::Test {
protected:

   LListIntTest() {

	}
	
	virtual ~LListIntTest() {
	
	}

	virtual void SetUp() {
	   for(int i = 0; i < 10; ++i){
		   myList.push_back(i);
		}
	}
	
	virtual void TearDown() {
	   myList.clear();
	}

	LListInt myList;
};

TEST_F(LListIntTest, SizeTest) {
	// Exepct 0th element to be 1, 1st elemnt to be 2, etc.
   EXPECT_EQ(10, myList.size());
}
