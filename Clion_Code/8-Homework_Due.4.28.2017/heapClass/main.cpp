#include <iostream>

#include "heap.h"

using namespace std;

int main()
{
    Heap<int, std::equal_to<int>, std::greater<double> > test;
    int j = 0;

    for (double i = 0.01; i <= 0.2; i += .01) {
        test.push(i, j);
        j++;
    }


// for (double i = .2; i >= 0; i -= .01) {
//        test.push(i, j);
//        j++;
//    }

    test.print();

    for (int k = 0; k < 20; ++k) {
        test.pop();
        test.print();
    }



    return 99;
}


