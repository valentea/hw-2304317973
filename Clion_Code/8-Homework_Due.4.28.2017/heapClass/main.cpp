#include <iostream>

#include "heap.h"

using namespace std;

int main() {
    Heap<int, std::equal_to<int>, std::less<double> > test;

    int j = 0;
    for (double i = 0.00; i <= 0.2; i += .01) {
        test.push(i, j);
        j++;
    }
//    cout << endl << endl;

//    for (double i = .2; i > .01; i -= .01) {
//        test.push(i, j);
//        j++;
//    }
    test.print();
    cout << endl << endl;

    test.decreaseKey(.01, 7);
    test.decreaseKey(.05, 13);
    test.decreaseKey(.02, 17);
    test.decreaseKey(.09, 18);
    test.decreaseKey(.01, 9);
    test.decreaseKey(.01, 11);
    test.decreaseKey(.001, 19);

    test.print();

    return 99;
}


