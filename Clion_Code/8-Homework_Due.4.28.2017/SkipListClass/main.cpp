#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>

#include "SkipList.h"

//==================================================
int main () {
    //srand(time(NULL));

    // 1.Initialize an empty Skip_list object
    Skip_list<int, int, std::greater<int> > s;

    // 2. insert()
    for (int i = 0; i < 100; ++i){

        s.insert(rand()%20, rand()%20);
    }

    // 2a. print()
    s.print();

    return 0;
}