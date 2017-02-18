#include "llistint.h"
#include "queueint.h"
#include <cstdlib>

using namespace std;


QueueInt::QueueInt(){
    LListInt myList;
}

int QueueInt::size() const {
    return myList.size();
}

bool QueueInt::empty() const {
    return myList.size() == 0;
}

void QueueInt::push(const int& val){
    myList.push_back(val);
}

void QueueInt::pop() {
    myList.remove(0);
}

int const & QueueInt::front() const{
    return myList.get(0);
}

void QueueInt::concatenate(QueueInt& other){
    myList += other.myList;
}