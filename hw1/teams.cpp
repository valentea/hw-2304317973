#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string *team1,
                   const string *team2,
                   int len) {
    cout << "\nCombination " << combo++ << endl;
    cout << "T1: ";
    for (int i = 0; i < len; i++) {
        cout << team1[i] << " ";
    }
    cout << endl;
    cout << "T2: ";
    for (int i = 0; i < len; i++) {
        cout << team2[i] << " ";
    }
    cout << endl;
}

// You may add additional functions here
void findTeamB(string *names, string *teamA, int numberOfPlayers, int teamSize, string* &teamB) {
    int aIndex = 0;
    int bIndex = 0;
    int totalIndex = 0;
    while (totalIndex < numberOfPlayers) {
        while (aIndex < teamSize) {
            if (names[totalIndex].compare(teamA[aIndex]) != 0) {
                teamB[bIndex++] = names[totalIndex++];
                if(bIndex == teamSize){
                    return;
                }
            } else if (names[totalIndex].compare(teamA[aIndex]) == 0) {
                aIndex++;
                totalIndex++;
            }
        }
        teamB[bIndex++] = names[totalIndex++];
    }
    return;
}


void combinationUtil(string *&names, int numberOfPlayers, int teamSize, int totalIndex, string *&teamA,
                     int aIndex, string *&teamB) {
    if (totalIndex == teamSize) {
        findTeamB(names, teamA, numberOfPlayers, teamSize, teamB);
        printSolution(teamA, teamB,teamSize);
        return;
    }
    if (aIndex >= numberOfPlayers) {
        return;
    }
    teamA[totalIndex] = names[aIndex];
    combinationUtil(names, numberOfPlayers, teamSize, totalIndex + 1, teamA, aIndex + 1, teamB);
    combinationUtil(names, numberOfPlayers, teamSize, totalIndex, teamA, aIndex + 1, teamB);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Please provide a file of names" << endl;
        return 1;
    }
    ifstream ifile(argv[1]);
    if (ifile.fail()) {
        cerr << "Error" << endl;
        return 1;
    }
    int numberOfNames;
    ifile >> numberOfNames;
    if (numberOfNames % 2 == 1) {
        cout << "Error";
        return 1;
    }
    string *names = new string[numberOfNames];
    int teamSize = numberOfNames/2;
    string *teamA = new string[teamSize];
    string *teamB = new string[teamSize];

    for (int i = 0; i < numberOfNames; ++i) {
        ifile >> names[i];
    }

    combinationUtil(names, numberOfNames, teamSize, 0, teamA, 0, teamB);

    delete[] names;
    delete[] teamA;
    delete[] teamB;

    return 0;
}
