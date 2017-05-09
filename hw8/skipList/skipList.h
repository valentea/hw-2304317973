#ifndef SKIPLIST_H
#define SKIPLIST_H


#include <functional>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

template <typename K, typename V, typename Comp>
struct SkipNode{
    K key_;
    V value_;
    SkipNode** forward;
    SkipNode(K& key, V& val, int level) {
        key_ = key;
        value_ = val;
        forward = new SkipNode*[level + 1];
    }
};


template <typename K, typename V, typename Comp>
class SkipList{
private:
    SkipNode<K, V, Comp>* head;
    SkipNode<K, V, Comp>* tail;
    int maxLevel = 0;
    float prob;

    SkipNode<K, V, Comp>* makeNode(K key, V val, int level);
    int randomLev();
    int nodeLev(SkipNode<K, V, Comp>** temp);

public:
    SkipList(int max){
        maxLevel = max;
        K minKey = INT_MIN;
        V minVal = INT_MIN;
        head = new SkipNode<K, V, Comp>(minKey, minVal, maxLevel);
        K maxKey = INT_MAX;
        V maxVal = INT_MAX;
        SkipNode<K, V, Comp>* end = new SkipNode<K, V, Comp>(maxKey, maxVal, maxLevel);
        for (int i = 0; i < maxLevel; ++i) {
            head->forward[i] = end;
        }
    }
    ~SkipList();

    void print();
    SkipNode<K, V, Comp>* find(K searchKey);
    void insert(K searchKey, V val);
    void erase(K searchKey);
};

template <typename K, typename V, typename Comp>
SkipList<K, V, Comp>::~SkipList(){
    delete head;
    delete tail;
};

template <typename K, typename V, typename Comp>
int SkipList<K, V, Comp>::randomLev(){
    int val = 1;
    while((((double)std::rand() / RAND_MAX)) < this->prob && std::abs(val) < this->maxLevel){
        val += 1;
    }
    return abs(val);
};

template <typename K, typename V, typename Comp>
int SkipList<K, V, Comp>::nodeLev(SkipNode<K, V, Comp>** temp) {
    int curLevel = 1;
    K tailKey = INT_MAX;

    if(temp[0]->key_ == tailKey){
        return curLevel;
    }

    for(int i = 0; i < sizeof(temp); i++){
        if(temp[i] != NULL && temp[i]->key_ != tailKey){
            curLevel++;
        }else{
            break;
        }
    }
    return curLevel;
}

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::print() {
    SkipNode<K, V, Comp>* list = head;
    int lineLen = 1;

    std::cout << "{";

    while(list->forward[0] != NULL){
        for(int i =0; i < nodeLev(list->forward); i++){
            cout << list->forward[0]->value_ << " ";
        }
        list = list->forward[0];
        if(list->forward[0] != NULL){
            cout << endl;
        }
        if(++lineLen % 2 == 0){
            cout << endl;
        }
    }
}

template <typename K, typename V, typename Comp>
SkipNode<K, V, Comp>* SkipList<K, V, Comp>::find(K searchKey) {
    SkipNode<K, V, Comp>* temp = head;

    for(int i = maxLevel; i-- > 0;){
        while(temp->forward[i]->key_ < searchKey){
            temp = temp->forward[i];
        }
    }
    temp = temp->forward[0];

    if(temp->key_ == searchKey){
        return temp;
    }else{
        return NULL;
    }
}

template <typename K, typename V, typename Comp>
SkipNode<K, V, Comp>* SkipList<K, V, Comp>::makeNode(K key, V val, int level) {
    return new SkipNode<K, V, Comp>(key, val, level);
}

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::insert(K searchKey, V val) {
    SkipNode<K, V, Comp>* temp = NULL;
    temp = find(searchKey);
    if(temp){
        temp->value_ = val;
        return;
    }

    SkipNode<K, V, Comp>** update = head->forward;
    int currMax = nodeLev(head->forward);
    temp = head;

    for(int i = currMax; i-- > 0;){
        while(temp->forward[i] != NULL && temp->forward[i]->key_ < searchKey){
            temp = temp->forward[i];
        }
        update[i] = temp;
    }
    temp = temp->forward[0];

    int newNodeLev = 1;
    if(temp->key_ != searchKey){
        newNodeLev = randomLev();
        int currLev = nodeLev(update);

        if(newNodeLev > currLev){
            for(int i = currLev + 1; i < newNodeLev; i++){
                update[i] = head;
            }
        }
        temp = makeNode(searchKey, val, newNodeLev);
    }
    for(int i = 0; i < newNodeLev; i++){
        temp->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = temp;
    }
}

template <typename K, typename V, typename Comp>
void SkipList<K, V, Comp>::erase(K searchKey){
    SkipNode<K, V, Comp>** update = head->forward;
    SkipNode<K, V, Comp>* temp = head;
    int currMax = nodeLev(head->forward);

    for(int i = currMax; i-- > 0;){
        while (temp->forward[i] != NULL && temp->forward[i]->key_ < searchKey){
            temp = temp->forward[i];
        }
        update[i] = temp;
    }
    temp = temp->forward[0];

    if(temp->key_ == searchKey){
        for(int i = 0; i < sizeof(update); i++){
            if(update[i]->forward[i] != temp){
                break;
            }
            update[i]->forward[i] = temp->forward[i];
        }
        delete temp;
    }
}

#endif

