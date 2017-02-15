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
	   //myList.clear();
	}

	LListInt myList;
};

TEST_F(LListIntTest, CopyConstructorTestSize) {
   LListInt test(myList);
   ASSERT_TRUE(test.size() == myList.size());
}

TEST_F(LListIntTest, CopyConstructorTestVals){
   LListInt test(myList);
   for(int i = 0; i < test.size(); i++){
   	EXPECT_TRUE(test.get(i) == myList.get(i));
   }
}

TEST_F(LListIntTest, CopyConstructorTestEmptyList){
   LListInt test(myList);
   myList.clear();
   LListInt test1(myList);
   ASSERT_TRUE(test1.size() == myList.size());
}

TEST_F(LListIntTest, AssignmentOperatorTestSize) {
   LListInt test;
   test = myList;
   ASSERT_TRUE(test.size() == myList.size());
}

TEST_F(LListIntTest, AssignmentOperatorTestVals){
   LListInt test;
   test = myList;
   for(int i = 0; i < test.size(); i++){
      EXPECT_TRUE(test.get(i) == myList.get(i));
   }
}

TEST_F(LListIntTest, AssignmentOperatorTestEmptyList){
   LListInt test;
   test = myList;
   myList.clear();
   LListInt test1(myList);
   ASSERT_TRUE(test1.size() == myList.size());
}

TEST_F(LListIntTest, PushBackBasic){
	myList.push_back(10);
	EXPECT_EQ(myList.get(myList.size()-1), 10);
}

TEST_F(LListIntTest, PushBackEmpty){
    myList.clear();
	myList.push_back(10);
	EXPECT_EQ(myList.get(myList.size()-1), 10);
}

TEST_F(LListIntTest, AddSumBasic){
    LListInt myList2;
    for(int i = 0; i < 10; ++i){
        myList2.push_back(i+myList.size());
    }
    myList += myList2;
    ASSERT_TRUE(myList2.size() == 0);
    for(int i = 0; i < myList.size(); ++i){
        EXPECT_EQ(myList.get(i), i);
    }
}

TEST_F(LListIntTest, AddSumMultiple){
    LListInt myList2;
    LListInt myList3;
    for(int i = 0; i < 10; ++i){
        myList2.push_back(i+myList.size());
    }
    for(int i = 0; i < 10; ++i){
        myList3.push_back(i+myList.size()+myList2.size());
    }
    myList += myList2 += myList3;
    ASSERT_TRUE(myList2.size() == 0);
    ASSERT_TRUE(myList3.size() == 0);
    for(int i = 0; i < myList.size(); ++i){
        EXPECT_EQ(myList.get(i), i);
    }
}

TEST_F(LListIntTest, AddSumEmptyList){
    LListInt myList2;
    myList += myList2;
    ASSERT_TRUE(myList2.size() == 0);
    for(int i = 0; i < myList.size(); ++i){
        EXPECT_EQ(myList.get(i), i);
    }
}




