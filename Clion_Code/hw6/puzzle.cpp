#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "heap.h"




int main(int argc, char *argv[]) {
    if (argc < 5) {
        cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
        return 1;
    }
    int size = (int)*argv[1];
    int initMoves = (int)*argv[2];
    int seed = (int)*argv[3];
    int heur = (int)*argv[4];

    Board mainStage(size, initMoves, seed);

    cout << mainStage << endl;
    cout << "enter tile number to move or -1 for a cheat: " << endl;
    int move = 0;
    while(mainStage.solved() || move == -2) {
        cin >> move;
        if (move == 0) {
            cout << "can not move empty space" << endl;
        } else if (move == -1) {
            cout << "cheat stuff i dont know how to use yet" << endl;
        } else {
            mainStage.move(move);
        }
    }



    return 0;
}
