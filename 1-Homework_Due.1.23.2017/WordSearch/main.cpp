#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Location
{
    Location()
    {
        row = -1;
        col = -1;
    }
    Location(int r, int c)
    {
        row = r;
        col = c;
    }
    int row;
    int col;
};

// @param[in] instream - Input (file) stream for the input file.  Opened in main()
// @param[out] grid Blank vector of vectors.  Should be updated with the
//                  contents of the grid from the input file
// @return true if successful, false otherwise (see HW writeup for details
//         about possible error cases to be checked)
bool readGrid(istream& instream, vector<vector<char> >& grid ) { //PASS 'GRID' BY REFERENCE.
    /** You complete **/
    string tempLine;
    int rowNumber = 0;
    int maxLength = 0;
    while (getline(instream, tempLine)) { //KEEP GETTING LINES UNTIL END OF FILE.
        if (tempLine.empty()) { //RETURN IF NOTHING IS ON LINE.
            return false;
        }
        int lineLength = 0;
        vector<char> row; //CONSTRUCT A VECTOR TO PASS INTO GRID.
        for (int i = 0; i < tempLine.size(); i += 2) { //ITERATE EVERY OTHER CHAR TO ACCOUNT FOR SPACES.
            char tempChar = tempLine[i];
            if (tempChar == ' ' || tempChar == '\t') continue; //CHECK TO SEE IF CHARACTER IS VALID.
            row.push_back(tempChar); //ADD NEW CHAR TO BACK OF 'ROW' VECTOR.
            lineLength++;
        }
        if(rowNumber == 0){
            maxLength = lineLength; //SET MAX LENGTH TO FIRST ROW.
        }
        if(maxLength != lineLength){
            return false; //MAKE SURE ALL ROWS ARE SAME LENGTH, OTHERWISE UNEVEN AND INVALID.
        }
        rowNumber++;
        grid.push_back(row); //ADD 'ROW' VECTORS TO THE 2D VECTOR 'GRID'.
    }
    if(rowNumber >= 1) { //AFTER 'WHILE' LOOP ENDS, IF THERE ARE MORE THAN 1 ROW, RETURN FN AND 'GRID' IS STORED.
        return 1;
    }
    else return false; //IF ANYTHING ELSE IS WRONG, FAIL.
}

// prototype - will be implemented below
bool findWordHelper(
        const vector<vector<char> >& grid,
        Location currLoc,
        Location delta,
        string word,
        unsigned int currWordIndex);

void printGrid(vector<vector<char> > grid){ //PRINT GRID FN, FOR EASE
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            cout << grid.at(row).at(col) << " ";
        }
        cout << endl;
    }
}

// Do not change
void printSolution(const string& targetWord, const Location& start, string direction) {
    cout << targetWord << " starts at (row,col) = (" << start.row << "," << start.col
         << ") and proceeds " << direction << "." << endl;
}

// Do not change
void printNoSolution(const string& targetWord) {
    cout << targetWord << " does NOT occur." << endl;
}

// Complete - you should not need to change this.
void findWord(const vector<vector<char> >& grid,
              const string& targetWord) {
    bool found = false;
    if (targetWord.size() < 2) {
        cout << "Need a word of length 2 or more." << endl;
        return;
    }
    for (unsigned int r = 0; r < grid.size(); r++) {
        for (unsigned int c = 0; c < grid[r].size(); c++) {
            if (grid[r][c] == targetWord[0]) {
                Location loc(r, c);
                if (findWordHelper(grid, Location(r - 1, c), Location(-1, 0), targetWord, 1)) {
                    printSolution(targetWord, loc, "up");
                    found = true;
                }
                if (findWordHelper(grid, Location(r, c - 1), Location(0, -1), targetWord, 1)) {
                    printSolution(targetWord, loc, "left");
                    found = true;
                }
                if (findWordHelper(grid, Location(r + 1, c), Location(1, 0), targetWord, 1)) {
                    printSolution(targetWord, loc, "down");
                    found = true;
                }
                if (findWordHelper(grid, Location(r, c + 1), Location(0, 1), targetWord, 1)) {
                    printSolution(targetWord, loc, "right");
                    found = true;
                }

            }
        }
    }
    if (!found) {
        printNoSolution(targetWord);
    }
}

/**
 * @param[in] grid The 2D vector containing the entire search contents
 * @param[in] currLoc Current row and column location to try to match
 *                    with the next letter
 * @param[in] delta   Indicates direction to move for the next search
 *                    by containing the *change* in row, col values
 *                    (i.e. 1,0 = down since adding 1 will move down 1 row)
 * @param[in] word The word for which you are searching
 * @param[in] currWordIndex The index to word indicating which letter must
 *                          be matched by this call
 */
bool findWordHelper(const vector<vector<char> >& grid,
                    Location currLoc,
                    Location delta,
                    string word,
                    unsigned int currWordIndex) {
    /*** You complete ***/
    if (currLoc.row == -1 or currLoc.col == -1) { //MAKE SURE 'CURRLOC' IS LOOKING AT VALID SPOT ON 'GRID'
        return false;
    }
    if (currLoc.row == grid.size() or currLoc.col == grid[1].size()) { //MAKE SURE 'CURRLOC' IS LOOKING AT VALID SPOT ON 'GRID'
        return false;
    }
    if (grid.at(currLoc.row).at(currLoc.col) == word[currWordIndex]) {
        currWordIndex++;
        if (currWordIndex == word.size() ) { //IF THE NUMBER OF CORRECT LETTERS IS THE SAME AS THE LENGTH OF THE WORD
            return true;                            //WE FOUND THE TARGET WORD, SO RETURN 'TRUE'
        }
        return findWordHelper(grid, Location(currLoc.row + delta.row, currLoc.col + delta.col), delta, word,
                              currWordIndex);
    }
    return false; //GENERAL CASE OF FN
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please provide a grid filename and targetWord" << endl;
        return 1;
    }
    ifstream ifile(argv[1]);
    string targetWord(argv[2]);
    if (ifile.fail()) {
        cerr << "Unable to open input grid file" << endl;
        return 1;
    }

    vector<vector<char> > mygrid;
    if (!readGrid(ifile, mygrid)) {
        cerr << "Error reading grid" << endl;
        ifile.close();
        return 1;
    }

    printGrid(mygrid); //UNCOMMENT TO VIEW INPUT GRID
    findWord(mygrid, targetWord);
    return 0;
}