#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

int main() {
    string password = "password";
    vector<char> singleLetters;
    vector<unsigned long> numbers;
    unsigned long long hash = 0;
    array<int, 4> final;

    cout << "single letters" << endl;
    for (int i = 0; i < password.length(); ++i) {
        singleLetters.push_back(password[i]);
        cout << singleLetters[i] << " ";
    }
    cout << endl << endl;

    cout << "single letter 'int' conversion" << endl;
    for (int m = 0; m < singleLetters.size(); ++m) {
        cout << (int)singleLetters[m] << " ";
    }
    cout << endl << endl;


    cout << "single letter 'int' conversion IN REVERSE" << endl;
    for (int j = (int)singleLetters.size()-1; j >= 0; j--) {
        cout << (int)singleLetters[j] << " ";
        numbers.push_back(pow(128,(singleLetters.size() - j)) * (int)singleLetters[j]);
    }
    cout << endl << endl;

    cout << "numbers: " << endl;
    for (int l = 0; l < 8; ++l) {
        cout << l << ": " << numbers[l] << endl;
    }
    cout << endl;


    cout << "hash before encryption: " << endl;
    for (int k = 0; k < singleLetters.size(); ++k) {
        hash = hash + (int)singleLetters[k];
    }

    cout << hash << endl;




    return 0;


}