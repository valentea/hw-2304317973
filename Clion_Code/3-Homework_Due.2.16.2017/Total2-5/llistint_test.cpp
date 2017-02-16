#include "llistint.h"
#include <iostream>

using namespace std;


int main() {

    LListInt list;

    if(list.empty()){
        cout << "Passed Empty Intialize test" << endl;
    }

    list.insert(0, 1);
    list.insert(1, 2);
    list.insert(1, 3);

    LListInt list2;

    list += list2;


    return 1;
}
