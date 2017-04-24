#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "heap.h"




int main(int argc, char *argv[]) {
    less<int> hat;
    Heap<int> test(2, hat);
    test.push(0);
    test.push(2);
    test.push(4);
    test.push(6);
    test.push(8);
    test.push(10);
    test.push(12);
    test.push(14);


    test.push(1);






    return 0;
}
