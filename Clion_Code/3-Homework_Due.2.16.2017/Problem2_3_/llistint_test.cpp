#include "llistint.h"
#include <iostream>
#include <sstream>

using namespace std;

int stringCompTest(LListInt test, string passing, int testNumber) {
    stringstream buffer;
    streambuf *sbuf = cout.rdbuf();
    cout.rdbuf(buffer.rdbuf());
    for (int i = 0; i < test.size(); ++i) {
        cout << test.get(i) << " ";
    }
    cout.rdbuf(sbuf);

    if (passing == buffer.str()) {
        cout << "Passed Test" << testNumber << "!" << endl;
        return 0;
    } else {
        cout << "Test Failed." << endl;
        cerr << "Test number " << testNumber << "failed." << endl;
        return 1;
    }
}


int main() {

    LListInt list;
    int testNumber = 1;
    int failFlag = 0;

    if (list.empty()) cout << "list is empty" << endl;

    cout << endl;

    list.insert(0, 1);
    cout << "TEST " << testNumber << "-----------------ADD TO EMPTY LIST" << endl;
    cout << "List should be: 1" << endl;
    failFlag += stringCompTest(list, "1 ", testNumber);
    testNumber++;

    cout << endl;

    list.insert(1, 2); //ADD ELEMENT TO BACK
    cout << "TEST " << testNumber << "-----------------ADD TO BACK OF LIST" << endl;
    cout << "List should be: 1 2" << endl;
    failFlag += stringCompTest(list, "1 2 ", testNumber);
    testNumber++;

    cout << endl;

    list.insert(2, 3); //ADD ELEMENT TO BACK
    cout << "TEST " << testNumber << "----------------ADD TO BACK OF LIST" << endl;
    cout << "List should be: 1 2 3" << endl;
    failFlag += stringCompTest(list, "1 2 3 ", testNumber);
    testNumber++;

    cout << endl;

    list.insert(0, 4); //ADD ELEMENT TO FRONT OF LIST WITH OBJECTS ALREADY IN IT
    cout << "TEST " << testNumber << "----------------ADD ELEMENT TO FRONT OF LIST WITH OBJECTS ALREADY IN IT" << endl;
    cout << "List should be: 4 1 2 3" << endl;
    stringCompTest(list, "4 1 2 3 ", testNumber);
    testNumber++;

    cout << endl;

    list.insert(2, 5); //ADD ELEMENT TO MIDDLE OF LIST
    cout << "TEST " << testNumber << "----------------ADD ELEMENT TO MIDDLE OF LIST" << endl;
    cout << "List should be: 4 1 5 2 3" << endl;
    cout << "List currently equals: ";
    failFlag += stringCompTest(list, "4 1 5 2 3 ", testNumber);
    testNumber++;

    cout << endl;

    cout << "TEST " << testNumber << "----------------CLEAR LIST AND START OVER FOR EASE" << endl;
    list.clear(); //RE-SET LIST

    if (list.empty()) cout << "List is empty!" << endl;
    else {
        cout << "List Did Not Clear: Abort Early" << endl;
        return 0;
    }

    cout << endl;

    cout << "TEST " << testNumber << "----------------CONSTRUCT LIST FROM 1 TO 5" << endl;
    for (int j = 0; j < 5; ++j) { //CONSTRUCT LIST OF FIVE QUICKLY
        list.insert(j, j + 1);
    }
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl << endl;

    testNumber++;

    cout << "TEST " << testNumber << "----------------REMOVE ITEM FROM BACK OF LIST" << endl;
    list.remove(list.size() - 1); //REMOVE ITEM FROM BACK OF LIST
    cout << "List should be: 1 2 3 4" << endl;
    failFlag += stringCompTest(list, "1 2 3 4 ", testNumber);
    testNumber++;

    cout << endl;

    cout << "TEST " << testNumber << "----------------REMOVE ITEM FROM FRONT OF LIST" << endl;
    list.remove(0); //REMOVE ITEM FROM FRONT OF LIST
    cout << "List should be: 2 3 4" << endl;
    failFlag += stringCompTest(list, "2 3 4 ", testNumber);
    testNumber++;

    cout << endl;

    cout << "TEST " << testNumber << "----------------REMOVE ITEM FROM MIDDLE OF LIST" << endl;
    list.remove(1); //REMOVE ITEM FROM MIDDLE OF LIST
    cout << "List should be: 2 4" << endl;
    failFlag += stringCompTest(list, "2 4 ", testNumber);
    testNumber++;

    cout << endl;

    cout << "TEST " << testNumber << "----------------CLEAR LIST AND START OVER FOR EASE" << endl;
    list.clear(); //RE-SET LIST

    if (list.empty()) cout << "List is empty!" << endl;
    else {
        cout << "List Did Not Clear: Abort Early" << endl;
        return 0;
    }

    cout << endl;

    cout << "TEST " << testNumber << "----------------CONSTRUCT LIST FROM 1 TO 5" << endl;
    for (int j = 0; j < 5; ++j) { //CONSTRUCT LIST OF FIVE QUICKLY
        list.insert(j, j + 1);
    }
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl << endl;

    testNumber++;

    cout << "TEST " << testNumber << "----------------TRY TO ADD DATA BEOND BOWNDS IN EITHER DIRECTION" << endl;
    cout << "-----------------------LIST SHOULD REMAIN UNCHANGED" << endl;
    list.insert(-1, 0);
    failFlag += stringCompTest(list, "1 2 3 4 5 ", testNumber);

    list.insert(list.size() + 1, 6);
    failFlag += stringCompTest(list, "1 2 3 4 5 ", testNumber);
    testNumber++;

    cout << endl;

    cout << "TEST " << testNumber << "----------------TRY TO REMOVE DATA BEOND BOWNDS IN EITHER DIRECTION" << endl;
    cout << "-----------------------LIST SHOULD REMAIN UNCHANGED" << endl;
    failFlag += stringCompTest(list, "1 2 3 4 5 ", testNumber);

    list.remove(list.size());
    failFlag += stringCompTest(list, "1 2 3 4 5 ", testNumber);

    cout << endl;

    if (failFlag == 0) {
        cout << "====================PASSED ALL REQUIRED TESTS====================" << endl;
    } else { cout << "====================" << failFlag << " TESTS FAILED====================" << endl; }


    return 1;
}