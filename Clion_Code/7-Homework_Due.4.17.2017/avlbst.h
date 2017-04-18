#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "math.h"
#include "bst.h"
#include<stdio.h>
#include<stdlib.h>

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getBalance () const;
    void setBalance (int balance);
    void updateBalance(int diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int diff)
{
    balance_ = balance_ + (diff);
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);
    void eraseHelp(Node<Key, Value> key, int diff);

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    /* You should write these helpers for sure.  You may add others. */
    AVLNode<Key, Value>* rotateLeft (AVLNode<Key, Value> *n);
    AVLNode<Key, Value>* rotateRight (AVLNode<Key, Value> *n);

    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair) {
    // TODO
    AVLNode<Key, Value> *curr = new AVLNode<Key, Value> (keyValuePair.first, keyValuePair.second, NULL);

    if (this->mRoot == NULL) {
        this->mRoot = curr;
    }  else if (curr->getKey() < this->mRoot->getKey()) {
        if (this->mRoot->getLeft() == NULL) {
            curr->setParent(this->mRoot);
            this->mRoot->setLeft(curr);
            static_cast<AVLNode<Key, Value>*>(this->mRoot)->updateBalance(-1);
            insert(keyValuePair);
        }else if(this->mRoot->getLeft()->getKey() != curr->getKey()){
            this->mRoot = this->mRoot->getLeft();
            insert(keyValuePair);
        }
    } else if (curr->getKey() > this->mRoot->getKey()) {
        if (this->mRoot->getRight() == NULL) {
            curr->setParent(this->mRoot);
            this->mRoot->setRight(curr);
            static_cast<AVLNode<Key, Value>*>(this->mRoot)->updateBalance(+1);
            insert(keyValuePair);
        }else if(this->mRoot->getRight()->getKey() != curr->getKey()){
            this->mRoot = this->mRoot->getRight();
            insert(keyValuePair);
        }
    }
    /* 2. Update height of this ancestor node */
    int tempBalance = static_cast<AVLNode<Key, Value>*>(this->mRoot)->getBalance();

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (tempBalance > 1 && this->mRoot->getKey() < this->mRoot->getLeft()->getKey()) {
        rotateRight(static_cast<AVLNode<Key, Value> *>(curr));
        return;
    }
    if (tempBalance < -1 && curr->getKey() > curr->getRight()->getKey()) {
        rotateLeft(static_cast<AVLNode<Key, Value> *>(curr));
        return;
    }
    if (tempBalance > 1 && curr->getKey() > curr->getLeft()->getKey()) {
        curr->setLeft(rotateLeft(static_cast<AVLNode<Key, Value> *>(curr)->getLeft()));
        rotateRight(static_cast<AVLNode<Key, Value> *>(curr));
        return;
    }
    if (tempBalance < -1 && curr->getKey() < curr->getRight()->getKey()) {
        curr->setRight(rotateLeft(static_cast<AVLNode<Key, Value> *>(curr)->getRight()));
        rotateLeft(static_cast<AVLNode<Key, Value> *>(curr));
        return;
    }
    if(this->mRoot->getParent() != NULL){
        this->mRoot = this->mRoot->getParent();
    }
}

/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::eraseHelp(Node<Key, Value> key, int diff){
    if(&key == NULL){
        return;
    }
    int ndiff = 0;
    if(key.getParent()->getLeft()->getKey() == key.getKey()){
        ndiff = 1;
    }else{
        ndiff = -1;
    }
    Node<Key, Value> *par = key.getParent();
};


template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{
    // TODO
    while (mRoot != NULL){
        int diff = 0;
        if(mRoot->getKey() == key){
            if(mRoot->getParent()->getLeft()->getKey() == key){
                diff = 1;
            }if(mRoot->getParent()->getRight()->getKey() == key){
                diff = -1;
            }
            Node<Key, Value> *temp = mRoot;
            delete[](mRoot);
            eraseHelp(*temp, diff);
        }else if(key < mRoot->getKey()){
            mRoot = mRoot->getLeft();
            erase(key);
        }else if(key > mRoot->getKey()){
            mRoot = mRoot->getRight();
            erase(key);
        }
    }
}



/**
* Rotates n down and to the left
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *n)
{
    // TODO
    AVLNode<Key, Value> *y = n->getRight();
    AVLNode<Key, Value> *T2= y->getLeft();

    // Perform rotation
    y->setLeft(n);
    n->setRight(T2);

    //  Update heights
    n->setBalance(char (std::max(n->getLeft()->getBalance(), n->getRight()->getBalance())+1));
    y->setBalance(char (std::max(n->getLeft()->getBalance(), n->getRight()->getBalance())+1));

    return y;

}

/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{
    // TODO
    AVLNode<Key, Value> *x = n->getRight();
    AVLNode<Key, Value> *T2 = x->getLeft();

    // Perform rotation
    x->setLeft(n);
    n->setRight(T2);

    //  Update heights
    n->setBalance(char (std::max(n->getLeft()->getBalance(), n->getRight()->getBalance())+1));
    x->setBalance(char (std::max(x->getLeft()->getBalance(), x->getRight()->getBalance())+1));

    return x;
}

/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }

}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
