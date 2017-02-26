#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template<typename T>
std::set<T> setIntersection(std::set<T> &s1, std::set<T> &s2) {
    std::set<std::string> returnSet;
    int CCount = 0;
    for (typename std::set<std::string>::iterator test = s2.begin(); test != s2.end(); test++) {
        typename std::set<std::string>::iterator test1 = s1.find(*test);
        if (test1 != s1.end()) {
            returnSet.insert(*test1);
            CCount++;
        }
    }
    if (CCount == s2.size()) {
        return returnSet;
    } else {
        returnSet.clear();
        return returnSet;
    }
}

template<typename T>
std::set<T> setUnion(std::set<T> &s1, std::set<T> &s2) {
    std::set<std::string> returnSet;
    int CCount = 0;
    for (typename std::set<std::string>::iterator test = s2.begin(); test != s2.end(); test++) {
        typename std::set<std::string>::iterator test1 = s1.find(*test);
        if (test1 != s1.end()) {
            returnSet.insert(*test1);
            CCount++;
        }
    }
    if (CCount > 0) {
        return returnSet;
    } else {
        returnSet.clear();
        return returnSet;
    }
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s);

// trim from end
std::string &rtrim(std::string &s);

// trim from both ends
std::string &trim(std::string &s);

#endif
