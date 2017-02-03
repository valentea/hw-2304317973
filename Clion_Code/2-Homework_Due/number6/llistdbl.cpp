#include "llistdbl.h"
#include <cstdlib>
#include <iostream>

using namespace std;

LListDbl::LListDbl() {
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

LListDbl::~LListDbl() {
    clear();
}

bool LListDbl::empty() const {
    return size_ == 0;
}

int LListDbl::size() const {
    return size_;
}

/**
 * Complete the following function
 */
void LListDbl::insert(int loc, const double &val) {
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
void LListDbl::remove(int loc) {
    if(loc < 0 || loc > size()-1) return;

    if(loc == size() - 1){
        Item* temp = getNodeAt(loc);
        temp->next = NULL;
        tail_ = temp;
        size_--;
    }
    else if(loc == 0){
        Item* temp = getNodeAt(loc + 1);
        temp->prev = NULL;
        head_ = temp;
        size_--;
    }else{
        Item* temp = getNodeAt(loc);
        Item* currForward = getNodeAt(loc + 1);
        Item* currBehind = getNodeAt(loc - 1);
        temp->next = currForward;
        temp->prev = currBehind;
        currBehind->next = temp;
        currForward->prev = temp;
        size_--;
    }
}

void LListDbl::set(int loc, const double &val) {
    Item *temp = getNodeAt(loc);
    temp->val = val;
}

double &LListDbl::get(int loc) {
    Item *temp = getNodeAt(loc);
    return temp->val;
}

double const &LListDbl::get(int loc) const {
    Item *temp = getNodeAt(loc);
    return temp->val;
}

void LListDbl::clear() {
    while (head_ != NULL) {
        Item *temp = head_->next;
        delete head_;
        head_ = temp;
    }
    tail_ = NULL;
    size_ = 0;
}


LListDbl::Item *LListDbl::getNodeAt(int loc) const {
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
