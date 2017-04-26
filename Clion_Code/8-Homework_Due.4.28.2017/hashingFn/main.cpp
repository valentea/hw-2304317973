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

    for (int i = 0; i < password.length(); ++i) {
        singleLetters.push_back(password[i]);
        cout << singleLetters[i] << " ";
    }
    cout << endl;

    for (int j = (int)singleLetters.size(); j > 0; j--) {
        numbers.push_back(pow(128,(singleLetters.size() - j)) * (int)singleLetters[j]);
    }
    for (int l = 0; l < 8; ++l) {
        cout << l << ": " << numbers[l] << endl;
    }
    cout << endl;

    for (int k = 0; k < singleLetters.size(); ++k) {
        hash = hash + singleLetters[k];
    }

    cout << hash << endl;




    return 0;


}