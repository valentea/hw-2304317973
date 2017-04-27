#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <numeric>

using namespace std;

unsigned long long power(unsigned long long base, unsigned long long top);

int main() {
    string password = "csci104";
    vector<char> singleLetters;
    vector<unsigned long long> numbers;
    unsigned long long hash = 0;
    array<unsigned long long, 4> significantNumbs;

    cout << "single letters" << endl;
    for (int i = 0; i < password.length(); ++i) {
        singleLetters.push_back(password[i]);
        cout << singleLetters[i] << " ";
    }
    cout << endl << endl;

    cout << "single letters (int)" << endl;
    for (int i = 0; i < password.length(); ++i) {
        cout << (int)singleLetters[i] << " ";
    }
    cout << endl << endl;


    cout << "single letter 'int' conversion IN REVERSE" << endl;
    for (int j = (int)singleLetters.size()-1; j >= 0; j--) {
        cout << (int)singleLetters[j] << " ";
        numbers.push_back((unsigned long long) power(128,(singleLetters.size() - (j+1))) * (int)singleLetters[j]);
    }
    cout << endl << endl;

    cout << "numbers: " << endl;
    for (int l = 0; l < numbers.size(); ++l) {
        cout << l << ": " << numbers[l] << endl;
    }
    cout << endl;


    cout << "hash before encryption: " << endl;
    for (int k = 0; k < singleLetters.size(); ++k) {
        hash = hash + numbers[k];
    }
    cout << hash << endl;

    if(hash == 452236385531886){
        cout << "correct this far" << endl << endl;
    }

    significantNumbs[3] = hash % 65521;
    significantNumbs[2] = (hash/65521) % 65521;
    significantNumbs[1] = ((hash/65521)/65521) % 65521;
    significantNumbs[0] = (((hash/65521)/65521)/65521) % 65521;

    cout << "significant numbs: " << endl;
    for (int n = 0; n < 4; ++n) {
        cout << "w" << n+1 << ": " << significantNumbs[n] << endl;
    }
    cout << endl << endl;

    unsigned long long finalVal;

    finalVal = (45912*significantNumbs[0]) + (35511*significantNumbs[1]) + (65169*significantNumbs[2]) + (4625*significantNumbs[3]);
    cout << "Final Val Pre Mod: " << finalVal << endl;
    finalVal = finalVal % 65521;

    cout << "Final Val: " << finalVal << endl;

    if(finalVal == 29703){
        cout << "boom" << endl;
    }
    return 0;
}

unsigned long long power(unsigned long long base, unsigned long long top){
    unsigned long long answer = 1;
    for (int i = 0; i < top; ++i) {
        answer = answer * base;
    }
    return answer;
}