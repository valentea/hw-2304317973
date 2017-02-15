#include "llistint.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream &os, const LListInt& list) {
    for (int i = 0; i < list.size(); ++i) {
        os << list.get(i) << " ";
        if ((i+1) % 10 == 0) {
            cout << endl;
        }
    }
    return os;
}


int main() {

    LListInt list;

    if(list.empty()){
        cout << "Passed Empty Intialize test" << endl;
    }



    return 1;
}