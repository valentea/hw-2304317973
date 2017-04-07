#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"

using namespace std;


Board::Board(int dim, int numInitMoves, int seed) {
    size_ = dim * dim;
    tiles_ = new int[size_];
    srand(seed);
    for (int i = 0; i < size_; i++) {
        tiles_[i] = i;
    }
    int blankLoc = 0;
    while (numInitMoves > 0) {
        int r = rand() % 4;
        int randNeighbor = -1;
        if (r == 0) {
            int n = blankLoc - dim;
            if (n >= 0) {
                randNeighbor = n;
            }
        } else if (r == 1) {
            int w = blankLoc - 1;
            if (blankLoc % dim != 0) {
                randNeighbor = w;
            }
        } else if (r == 2) {
            int s = blankLoc + dim;
            if (s < size_) {
                randNeighbor = s;
            }
        } else {
            int e = blankLoc + 1;
            if (blankLoc % dim != dim - 1) {
                randNeighbor = e;
            }
        }
        if (randNeighbor > -1) {
            tiles_[blankLoc] = tiles_[randNeighbor];
            tiles_[randNeighbor] = 0;
            blankLoc = randNeighbor;
            numInitMoves--;
        }
    }
}


void Board::move(int tile) {
    int side_dim = dim();
    int tr, tc, br, bc;

    // find tile row and column
    int i = -1;
    while (tiles_[++i] != tile);

    tr = i / side_dim;
    tc = i % side_dim;

    // find blank row and column
    int j = -1;
    while (tiles_[++j] != 0);

    br = j / side_dim;
    bc = j % side_dim;

    if (abs(static_cast<double>(tr - br)) + abs(static_cast<double>(tc - bc)) != 1) {
        cout << "Invalid move of tile " << tile << " at ";
        cout << tr << "," << tc << " and blank spot at ";
        cout << br << "," << bc << endl;
        return;
    }
    // Swap tile and blank spot
    tiles_[j] = tile;
    tiles_[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board *> Board::potentialMoves() const {
    map<int, Board *> potMoves;
    int esR = -1;
    int esC = -1;

    int emptySpace = -1;
    for (int i = 0; i < size(); i++) {
        if(tiles_[i] == 0){
            emptySpace = i;
            esR = emptySpace / dim();
            esC = emptySpace % dim();
        }
    }

    if(esR+1 == dim()){
        if(esC ==0){ //bot left corner
            Board *temp = new Board(this);
            temp->move(tiles_[emptySpace+1]); //look right
            potMoves.insert(make_pair(emptySpace+1, temp));

              Board *temp1 = new Board(this);
            temp1->move(tiles_[emptySpace-dim()]); //look up
            potMoves.insert(make_pair(emptySpace-dim(), temp1));
        }
        else if(esC+1 == dim()){ //bot right corner
            Board *temp = new Board(this);
            temp->move(tiles_[emptySpace-1]); //look left
            potMoves.insert(make_pair(emptySpace-1, temp));

              Board *temp1 = new Board(this);
            temp1->move(tiles_[emptySpace-dim()]); //loop up
            potMoves.insert(make_pair(emptySpace-dim(), temp1));;
        }else{ //bot row
            Board *temp = new Board(this);
            temp->move(tiles_[emptySpace+1]); //look right
            potMoves.insert(make_pair(emptySpace+1, temp));

              Board *temp1 = new Board(this);
            temp1->move(tiles_[emptySpace-1]); //look left
            potMoves.insert(make_pair(emptySpace-1, temp1));

            Board *temp2 = new Board(this);
            temp2->move(tiles_[emptySpace-dim()]); //look up
            potMoves.insert(make_pair(emptySpace-dim(), temp2));
        }
    }
    else if(esR == 0){
        if(esC == 0){ //top left corner
            Board *temp = new Board(this);
            temp->move(tiles_[emptySpace+1]); //look right
            potMoves.insert(make_pair(emptySpace+1, temp));

              Board *temp1 = new Board(this);
            temp1->move(tiles_[emptySpace+dim()]); //look down
            potMoves.insert(make_pair(emptySpace+dim(), temp1));
        }
        else if(esC+1 == dim()){ //top right corner
            Board *temp = new Board(this);
            temp->move(tiles_[emptySpace-1]); //look left
            potMoves.insert(make_pair(emptySpace-1, temp));

              Board *temp1 = new Board(this);
            temp1->move(tiles_[emptySpace+dim()]); //look down
            potMoves.insert(make_pair(emptySpace+dim(), temp1));
        }else{
            Board *temp = new Board(this);
            temp->move(tiles_[emptySpace+1]); //look right
            potMoves.insert(make_pair(emptySpace+1, temp));

              Board *temp1 = new Board(this);
            temp1->move(tiles_[emptySpace-1]); //look left
            potMoves.insert(make_pair(emptySpace-1, temp1));

            Board *temp2 = new Board(this);
            temp2->move(tiles_[emptySpace+dim()]); //look down
            potMoves.insert(make_pair(emptySpace+dim(), temp2));
        }
    }
    else if(esC ==0){ //left wall
        Board *temp = new Board(this);
        temp->move(tiles_[emptySpace+1]); //look right
        potMoves.insert(make_pair(emptySpace+1, temp));

        Board *temp1 = new Board(this);
        temp1->move(tiles_[emptySpace-dim()]); //look left
        potMoves.insert(make_pair(emptySpace-dim(), temp1));

        Board *temp2 = new Board(this);
        temp2->move(tiles_[emptySpace+dim()]); //look down
        potMoves.insert(make_pair(emptySpace+dim(), temp2));
    }
    else if(esC+1 == dim()){ //right wall
        Board *temp = new Board(this);
        temp->move(tiles_[emptySpace-1]); //look left
        potMoves.insert(make_pair(emptySpace-1, temp));

        Board *temp1 = new Board(this);
        temp1->move(tiles_[emptySpace-dim()]); //look left
        potMoves.insert(make_pair(emptySpace-dim(), temp1));

        Board *temp2 = new Board(this);
        temp2->move(tiles_[emptySpace+dim()]); //look down
        potMoves.insert(make_pair(emptySpace+dim(), temp2));
    }else{ //all four sides open
        Board *temp = new Board(this);
        temp->move(tiles_[emptySpace-1]); //look left
        potMoves.insert(make_pair(emptySpace-1, temp));

          Board *temp1 = new Board(this);
        temp1->move(tiles_[emptySpace-dim()]); //look left
        potMoves.insert(make_pair(emptySpace-dim(), temp1));

        Board *temp2 = new Board(this);
        temp2->move(tiles_[emptySpace+dim()]); //look down
        potMoves.insert(make_pair(emptySpace+dim(), temp2));

        Board *temp3 = new Board(this);
        temp3->move(tiles_[emptySpace-1]); //look left
        potMoves.insert(make_pair(emptySpace-1, temp3));
    }
    return potMoves;
}


const int &Board::operator[](int loc) const {
    return tiles_[loc];
}

int Board::size() const {
    return size_;
}

int Board::dim() const {
    return static_cast<int>(sqrt(size_));
}

void Board::printRowBanner(ostream &os) const {
    int side_dim = dim();
    if (side_dim == 0) return;
    os << '+';
    for (int i = 0; i < side_dim; i++) {
        os << "--+";
    }
    os << endl;
}

bool Board::operator<(const Board &rhs) const{
    for(int i = 0; i < size_; i++){
        if(this->tiles_[i] < rhs.tiles_[i]){
            return true;
        }else if(this->tiles_[i] == rhs.tiles_[i]){
            continue;
        }else{
            return false;
        }
    }
}

bool Board::solved() const{
    Board answer(dim(), 0, 0);
    if(*this < answer){
        return true;
    }
    return false;
}