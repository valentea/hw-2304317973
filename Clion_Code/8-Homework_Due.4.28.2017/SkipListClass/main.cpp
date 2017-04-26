#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>

#include "SkipList.h"

//==================================================
int main () {
    //SET rand() SEED
    srand(time(NULL));

    // INITIALIZE SKIP LIST
    Skip_list<int, int, std::greater<int> > testList;

    // INSERT 20 RANDOM VALS
    for (int i = 0; i < 20;){
        SkipNode<int, int>* temp = testList.find(i);

        if(temp == NULL) {
            testList.insert(rand() % 20, rand() % 100);
            i++;
        }
    }
    //PRINT OUT LIST, KEY FIRST AND THEN VALUE
    std::cout << "Test 1: List with multiple objects." << std::endl;
    testList.print();
    std::cout << "List Size: " << testList.size() << std::endl;
    std::cout << std::endl << std::endl;

    //ERASE EVERYTHING FROM THE LIST
    for(int i = 0; i < 20; i++){
        testList.erase(i);
    }

    //SEE IF LIST IS TRULY EMPTY
    std::cout << "Test 2: List Should Be Empty" << std::endl;
    testList.print();
    std::cout << "List Size: " << testList.size() << std::endl;
    std::cout << std::endl << std::endl;

    //INSERT ANOTHER 20 VALS
    for (int i = 0; i < 20; i++){
        testList.insert(rand()%20, rand()%20);
    }

    //REMOVE HALF
    for (int j = 0; j < 10; ++j) {
        testList.erase((j*rand())%20);
    }

    std::cout << "Test 3: List should have aprox half of the data it had originaly" << std::endl;
    testList.print();
    std::cout << "List Size: " << testList.size() << std::endl;
    std::cout << std::endl << std::endl << "All Basic Tests Complete!" << std::endl;

    return 0;
}