#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "heap.h"

int main(int argc, char *argv[]) {
    /*if (argc < 5) {
        cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
        return 1;
    }*/

    struct item
    {
    public:
        item *rightC_;
        item *leftC_;
        item *parent_;
        int data;
    };
/*    template <typename T>
    struct less
    {
        bool operator()(const T& v1, const T& v2){
            return v1 < v2;
        }
    };
    template <typename T>
    struct greater
    {
        bool operator()(const T& v1, const T& v2){
            return v1 > v2;
        }
    };*/

    Heap test(2);

    item anything1;
    item anything2;
    item anything3;

    anything1.parent_ = NULL;
    anything1.rightC_ = &anything3;
    anything1.leftC_ = &anything2;
    anything1.data = 1;

    anything2.rightC_ = NULL;
    anything2.leftC_ = NULL;
    anything2.parent_ = &anything1;
    anything2.data = 2;

    anything3.rightC_ = NULL;
    anything3.leftC_ = NULL;
    anything3.parent_ = &anything1;
    anything3.data = 3;


    test.push(anything1);
    test.push(anything2);
    test.push(anything3);

    for(int i = 0; i != 3; i++){
        cout << test.top().data << " " << endl;
        test.pop();
    }

    if(test.empty()){
        cout << "test is now empty" << endl;
    }

    return 0;
}
