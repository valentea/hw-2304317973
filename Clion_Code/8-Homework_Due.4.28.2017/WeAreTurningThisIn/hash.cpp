#include "hash.h"

unsigned long long power(unsigned long long base, unsigned long long top){
    unsigned long long answer = 1;
    for (int i = 0; i < top; ++i) {
        answer = answer * base;
    }
    return answer;
}

unsigned long long hasher(string password) {
    vector<char> singleLetters;
    vector<unsigned long long> numbers;
    unsigned long long hash = 0;
    array<unsigned long long, 4> significantNumbs;

    for (int i = 0; i < password.length(); ++i) {
        singleLetters.push_back(password[i]);
    }

    for (int j = (int) singleLetters.size() - 1; j >= 0; j--) {
        numbers.push_back(power(128, (singleLetters.size() - (j + 1))) * (int) singleLetters[j]);
    }

    for (int k = 0; k < singleLetters.size(); ++k) {
        hash = hash + numbers[k];
    }

    significantNumbs[3] = hash % 65521;
    significantNumbs[2] = (hash / 65521) % 65521;
    significantNumbs[1] = ((hash / 65521) / 65521) % 65521;
    significantNumbs[0] = (((hash / 65521) / 65521) / 65521) % 65521;

    unsigned long long finalVal;

    finalVal = (45912 * significantNumbs[0]) + (35511 * significantNumbs[1]) + (65169 * significantNumbs[2]) +
               (4625 * significantNumbs[3]);
    finalVal = finalVal % 65521;

    return finalVal;
}
