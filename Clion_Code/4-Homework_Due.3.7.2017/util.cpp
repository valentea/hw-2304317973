#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;

std::string convToLower(std::string src) {
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
    set<string> keyWords;
    stringstream ss(rawWords);
    string uncheckedWord;
    string uncheckedWord2;
    while (ss >> uncheckedWord) {
        if(uncheckedWord.length() == 1){ //IF WORD LENGTH IS ONE, GO TO NEXT BECAUSE BY DEFAULT TOO SHORT
            continue;
        }
        for (int i = 0; i < uncheckedWord.length(); ++i) { //LOOP THROUGH ALL CHAR IN WORD
            if (ispunct(uncheckedWord[i])) { //CHECK TO SEE IF A CHAR IS PUNCTUATION
                if(uncheckedWord[i] == uncheckedWord.back() && uncheckedWord.length() < 2){
                    break;
                }
                string temp = uncheckedWord.substr(0,  i);
                if(uncheckedWord[i] == uncheckedWord.back()){
                    uncheckedWord = temp;
                    continue;
                }
                char firstLetterPostPunk = uncheckedWord[i+1];
                size_t punkT =  uncheckedWord.find(firstLetterPostPunk);
                string temp2 = uncheckedWord.substr(punkT);
                uncheckedWord2 = temp2;
                uncheckedWord = temp;
            }
        }
        if (uncheckedWord.length() >= 2) { //CHECK IF WORD IS LONGER THAN TWO CHAR
            for (int i=0; i < uncheckedWord.length(); ++i) {
                uncheckedWord[i] = tolower(uncheckedWord[i]); //TURN WORD TO ALL LOWERCASE
            }

            keyWords.insert(uncheckedWord); //ADD TO KEYWORD
        }
        if (uncheckedWord2.length() >= 2) {
            for (int i=0; i < uncheckedWord2.length(); ++i) {
                uncheckedWord2[i] = tolower(uncheckedWord2[i]);
            }
            keyWords.insert(uncheckedWord2);
        }
    }
    return keyWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
            std::find_if(s.rbegin(),
                         s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
            s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
