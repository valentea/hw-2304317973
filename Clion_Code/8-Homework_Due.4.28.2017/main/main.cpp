#include <iostream>

#include "heap.h"

using namespace std;

int main()
{
    Heap<int> test;
    int j = 0;

    for (double i = 0; i < .2; i += .01) {
        test.push(i, j);
        j++;
    }
    test.print();
    cout << endl << endl;

    for (int k = 0; k < 20; ++k) {
        test.pop();
    }
    test.print();
    cout << endl << endl;

    for (double i = .2; i >= 0; i -= .01) {
        test.push(i, j);
        j++;
    }
    test.print();
    cout << endl << endl;

    for (int k = 0; k < 20; ++k) {
        test.pop();
    }
    test.print();
    cout << endl << endl;

    return 99;
}


