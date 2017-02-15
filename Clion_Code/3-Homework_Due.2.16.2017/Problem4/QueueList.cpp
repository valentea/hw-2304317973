#include "queueint.h"
#include <iostream>

using namespace std;

int main(){

    QueueInt myQue;
    for (int i = 0; i < 5; ++i) {
        myQue.push(i);
    }

    int queSize = myQue.size();
    for(int i = 0; i < queSize; ++i){
        cout << myQue.front() << " ";
        myQue.pop();
    }
    cout << endl;

    if(myQue.empty()){
        cout << "empty" << endl;
    }

    QueueInt myQue1;
    for (int i = 0; i < 5; ++i) {
        myQue1.push(i);
    }
    QueueInt myQue2;
    for (int i = 0; i < 5; ++i) {
        myQue2.push(i+myQue1.size());
    }



    myQue1.concatenate(myQue2);
    if(myQue2.empty()){
        cout << "que2 empty" << endl;
    }
    int queSize1 = myQue1.size();
    for(int i = 0; i < queSize1; ++i){
        cout << myQue1.front() << " ";
        myQue1.pop();
    }



    return 1;
}