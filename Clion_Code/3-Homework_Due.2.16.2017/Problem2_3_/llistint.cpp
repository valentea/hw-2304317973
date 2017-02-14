#include "llistint.h"
#include <cstdlib>
#include <iostream>

using namespace std;

LListInt::LListInt() {
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

LListInt::~LListInt() {
    clear();
}

bool LListInt::empty() const {
    return size_ == 0;
}

int LListInt::size() const {
    return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int &val) {
    Item *temp = new Item;
    temp->val = val;
    temp->prev = NULL;
    temp->next = NULL;

    if(loc < 0 || loc > size()) return;

    if (size() == loc && loc != 0) {
        Item *current = getNodeAt(loc - 1);
        temp->prev = current;
        current->next = temp;
        tail_ = temp;
        size_++;
    } else if (empty()) {
        head_ = temp;
        tail_ = temp;
        size_++;
    } else if (loc == 0 ) {
        Item* current = getNodeAt(loc);
        temp->next = current;
        current->prev = temp;
        head_ = temp;
        size_++;
    } else {
        Item *current = getNodeAt(loc);
        Item *current1 = getNodeAt(loc - 1);
        temp->next = current;
        current->prev = temp;
        temp->prev = current1;
        current1->next = temp;
        size_++;
    }
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc) {
    if(loc < 0 || loc > size()-1) {cout << "you fail" << endl; return;}

    if(loc == size() - 1){
        cout << "loc == size" << endl;
        Item* temp = getNodeAt(loc);
        temp->next = NULL;
        tail_ = temp;
        size_--;
    }
    else if(loc == 0){
        cout << "loc == 0" << endl;
        Item* temp = getNodeAt(loc + 1);
        temp->prev = NULL;
        head_ = temp;
        size_--;
    }else{
        Item* temp = getNodeAt(loc);
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        size_--;
        delete(temp);
    }
}

void LListInt::set(int loc, const int &val) {
    Item *temp = getNodeAt(loc);
    temp->val = val;
}

int &LListInt::get(int loc) {
    Item *temp = getNodeAt(loc);
    return temp->val;
}

int const &LListInt::get(int loc) const {
    Item *temp = getNodeAt(loc);
    return temp->val;
}

void LListInt::clear() {
    while (head_ != NULL) {
        Item *temp = head_->next;
        delete head_;
        head_ = temp;
    }
    tail_ = NULL;
    size_ = 0;
}


LListInt::Item *LListInt::getNodeAt(int loc) const {
    Item *temp = head_;
    if (loc >= 0 && loc < size_) {
        while (temp != NULL && loc > 0) {
            temp = temp->next;
            loc--;
        }
        return temp;
    } else {
        //throw std::invalid_argument("bad location");
        return NULL;
    }
}


LListInt::LListInt(const LListInt& other){

}