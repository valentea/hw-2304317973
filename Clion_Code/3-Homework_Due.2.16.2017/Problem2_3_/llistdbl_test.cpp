#include "llistint.h"
#include <iostream>

using namespace std;


int main() {

    LListInt list;

    if(list.empty()) cout << "list is empty" << endl;

    list.insert(0,1);
    cout << "-----------------ADD TO EMPTY LIST" << endl;
    cout << "List should be: 1" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    list.insert(1,2); //ADD ELEMENT TO BACK
    cout << "-----------------ADD TO BACK OF LIST" << endl;
    cout << "List should be: 1 2" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    list.insert(2,3); //ADD ELEMENT TO BACK
    cout << "-----------------ADD TO BACK OF LIST" << endl;
    cout << "List should be: 1 2 3" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    list.insert(0,4); //ADD ELEMENT TO FRONT OF LIST WITH OBJECTS ALREADY IN IT
    cout << "-----------------ADD ELEMENT TO FRONT OF LIST WITH OBJECTS ALREADY IN IT" << endl;
    cout << "List should be: 4 1 2 3" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    list.insert(2,5); //ADD ELEMENT TO MIDDLE OF LIST
    cout << "-----------------ADD ELEMENT TO MIDDLE OF LIST" << endl;
    cout << "List should be: 4 1 5 2 3" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;
    cout << "-----------------CLEAR LIST AND START OVER FOR EASE" << endl;
    list.clear(); //RE-SET LIST

    if(list.empty()) cout << "List is empty!" << endl;

    cout << "-----------------CONSTRUCT LIST FROM 1 TO 5" << endl;
    for (int j = 0; j < 5; ++j) { //CONSTRUCT LIST OF FIVE QUICKLY
        list.insert(j,j+1);
    }
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    cout << "-----------------REMOVE ITEM FROM BACK OF LIST" << endl;
    list.remove(list.size()-1); //REMOVE ITEM FROM BACK OF LIST
    cout << "List should be: 1 2 3 4" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    cout << "-----------------REMOVE ITEM FROM FRONT OF LIST" << endl;
    list.remove(0); //REMOVE ITEM FROM FRONT OF LIST
    cout << "List should be: 2 3 4" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    cout << "-----------------REMOVE ITEM FROM MIDDLE OF LIST" << endl;
    list.remove(1); //REMOVE ITEM FROM MIDDLE OF LIST
    cout << "List should be: 2 4" << endl;
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;


    cout << "-----------------CLEAR LIST AND START OVER FOR EASE" << endl;
    list.clear(); //RE-SET LIST

    if(list.empty()) cout << "List is empty!" << endl;

    cout << "-----------------CONSTRUCT LIST FROM 1 TO 5" << endl;
    for (int j = 0; j < 5; ++j) { //CONSTRUCT LIST OF FIVE QUICKLY
        list.insert(j,j+1);
    }
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    cout << "-----------------TRY TO ADD DATA BEOND BOWNDS IN EITHER DIRECTION" << endl;
    cout << "-----------------LIST SHOULD REMAIN UNCHANGED" << endl;
    list.insert(-1, 0);
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;
    list.insert(list.size()+1, 6);
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    cout << "-----------------TRY TO REMOVE DATA BEOND BOWNDS IN EITHER DIRECTION" << endl;
    cout << "-----------------LIST SHOULD REMAIN UNCHANGED" << endl;
    list.remove(-1);
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;
    list.remove(list.size());
    cout << "List currently equals: ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.get(i) << " ";
    }
    cout << endl;

    cout << "====================PASSED ALL REQUIRED TESTS====================";
    return 1;
}