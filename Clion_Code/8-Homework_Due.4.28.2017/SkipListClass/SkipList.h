#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <climits>
#include <vector>


template <typename K, typename V>
struct SkipNode {
    K key_;
    V value_;

    // pointers to successor nodes
    std::vector<SkipNode<K, V>* > forward_;

    SkipNode<K, V> (K key, const V& val, int level);
};


template <typename K, typename V, typename Comp = std::less<K> >
class Skip_list {
public:

    Skip_list<K, V, Comp> (const Comp& c = Comp() );
    ~Skip_list<K, V, Comp> ();

    // non-modifying member functions
    void print ();
    SkipNode<K, V>* find (K searchKey);

    // modifying member functions
    void insert (K searchKey, V newValue);
    void erase (K searchKey);
    int size(){ return  size_; }
private:
    // pointer to first node
    SkipNode<K, V>* head;
    // last node
    SkipNode<K, V>* NIL;

    // implicitly used member functions
    int randomLevel ();
    int nodeLevel(const std::vector<SkipNode<K, V>* >& v);
    SkipNode<K, V>* makeNode (K key, V val, int level);

    // data members
    float probability;
    int maxLevel;
    Comp singleComp;
    bool lessThan = true;
    int size_ = 0;
};


template <typename K, typename V>
SkipNode<K, V>::SkipNode (K k, const V& v, int level)
        :  key_(k), value_(v)
{
    for (int i = 0; i < level; ++i) forward_.push_back(NULL);
}

//==============================================================================
// Class Skip_list member implementations
// constructor

template <typename K, typename V, typename Comp>
Skip_list<K, V, Comp>::Skip_list(const Comp& c)
        : probability(0.5), maxLevel(4), singleComp(c)
{
    // Initialize the head of the skip list

    int headKey = 0;
    int headVal = 0;
    int tailKey = 0;
    int tailVal = 0;

    if(singleComp(1,2)) {
        lessThan = true;
        headKey = INT_MIN;
        tailKey = INT_MAX;
    }else if(singleComp(2,1)){
        lessThan = false;
        headKey = INT_MAX;
        tailKey = INT_MIN;
    }else{
        std::cout << "Unknown Comp" << std::endl;
        return;
    }
    head = new SkipNode<K, V> (headKey, headVal, maxLevel);

    // Initialize the last element of the list

    NIL = new SkipNode<K, V> (tailKey, tailVal, maxLevel);

    // Connect start to end
    // connect all the levels/forward_ pointers of the header to NIL
    for (size_t i = 0; i < head->forward_.size(); ++i) {
        head->forward_[i] = NIL;
    }
}

// destructor
template <typename K, typename V, typename Comp >
Skip_list<K, V, Comp>::~Skip_list<K, V, Comp> () {
    delete head;
    delete NIL;
}

// Helper functions
/*
    Function: randomLevel()
    Use: implicit in class Skip_list
    It generates node levels in the range
    [1, maxLevel).

    It uses rand() scaled by its maximum
    value_: RAND_MAX, so that the randomly
    generated numbers are within [0,1).
*/
template <typename K, typename V, typename Comp >
int Skip_list<K, V, Comp>::randomLevel () {
    int level = 1;

    while ( ((double)std::rand() / RAND_MAX) < probability &&
           std::abs(level) < maxLevel - 1) {

        level += 1;
    }
    return abs(level);
}

/*
    Function: nodeLevel()
    Use: Implicitly in most of the member functions.

    It returns the number of non-null pointers
    corresponding to the level of the current node.
    (the node that contains the checked vector of
    forward_ pointers)

    If list empty returns 1.
*/
template <typename K, typename V, typename Comp >
int Skip_list<K, V, Comp>::nodeLevel (const std::vector<SkipNode<K, V>* >& v) {
    int currentLevel = 1;
    // last element's key_ is the largest
    int tailKey = 0;
    if(singleComp(1,2)) {
        tailKey = INT_MAX;
    }else if(singleComp(2,1)){
        tailKey = INT_MIN;
    }

    if (v[0]->key_ == tailKey) {
        return currentLevel;
    }

    for (size_t i = 0; i < v.size(); ++i) {

        if (v[i] != nullptr && v[i]->key_ != tailKey) {
            ++currentLevel;
        } else {
            break;
        }
    }
    return currentLevel;
}

// Non-modifying member functions
/*
    Function: print()
    Use: skip_list_obj.print();

    It prints the key_, value_, level
    of each node of the skip list.

    Prints two nodes per line.
*/
template <typename K, typename V, typename Comp >
void Skip_list<K, V, Comp>::print () {
    SkipNode<K, V>* list = head;
    int lineLenght = 1;

    if(size() == 0){
        std::cout << "Empty List" << std::endl;
        return;
    }

   std::cout << "Key: Val" << std::endl;

    while (list->forward_[0]->forward_[0] != NULL) {
        std::cout << list->forward_[0]->key_ << ": " ;
        for (int i = 0; i < nodeLevel(list->forward_); ++i) {
            std::cout << list->forward_[0]->value_ << " ";
        }
        std::cout << std::endl;
        list = list->forward_[0];

        //if (list->forward_[0] != nullptr) std::cout <<" : ";

        //if (++lineLenght % 2 == 0) std::cout <<"\n";
    }
    //3std::cout <<"}\n";
}

/*
    Function: find()
    Use: SkipNode* found = skip_list_obj.find(searchKey);

    It searches the skip list and
    returns the element corresponding
    to the searchKey; otherwise it returns
    failure, in the form of null pointer.
*/
template <typename K, typename V, typename Comp >
SkipNode<K, V>* Skip_list<K, V, Comp>::find(K searchKey) {
    SkipNode<K, V>* x = head;
    int currentMaximum = nodeLevel(head->forward_);
    bool sortPass = false;


    for (int i = currentMaximum; i-- > 0;) {
            while (x->forward_[i] != nullptr && singleComp(x->forward_[i]->key_, searchKey)) {
                x = x->forward_[i];
            }
    }
    x = x->forward_[0];

    if (x->key_ == searchKey) {
        return x;
    } else {
        return nullptr;
    }
}

// Modifying member functions
/*
    Function: makeNode ()
    Use: Implicitly in member function insert().

    It wraps the SkipNode constructor which creates
    a node on the heap and returns a pointer to it.
*/
template <typename K, typename V, typename Comp >
SkipNode<K, V>* Skip_list<K, V, Comp>::makeNode (K key, V val, int level) {
    return new SkipNode<K, V> (key, val, level);
}

/*
    Function: insert();
    Use: void insert(searchKey, newValue);

    It searches the skip list for elements
    with seachKey, if there is an element
    with that key_ its value_ is reassigned to the
    newValue, otherwise it creates and splices
    a new node, of random level.
*/
template <typename K, typename V, typename Comp >
void Skip_list<K, V, Comp>::insert(K searchKey, V newValue) {
    // reassign if node exists
    SkipNode<K, V>* x = nullptr;
    x = find(searchKey);
    if (x) {
        x->value_ = newValue;
        return;
    }

    // vector of pointers that needs to be updated to account for the new node
    std::vector<SkipNode<K, V>* > update(head->forward_);
    int currentMaximum = nodeLevel(head->forward_);
    x = head;
    bool sortPass = false;

    // search the list
    for (int i = currentMaximum; i-- > 0;) {
            while (x->forward_[i] != nullptr && singleComp(x->forward_[i]->key_, searchKey)) {
                x = x->forward_[i];
            }
        update[i] = x;
    }
    x = x->forward_[0];

    // create new node
    int newNodeLevel = 1;
    if (x->key_ != searchKey) {
        newNodeLevel = randomLevel();
        int currentLevel = nodeLevel(update);
        if (newNodeLevel > currentLevel) {
            for (int i = currentLevel + 1; i < newNodeLevel; ++i) {
                update[i] = head;
            }
        }
        x = makeNode(searchKey, newValue, newNodeLevel);
        size_++;
    }

    // connect pointers of predecessors and new node to successors
    for (int i = 0; i < newNodeLevel; ++i) {

        x->forward_[i] = update[i]->forward_[i];
        update[i]->forward_[i] = x;
    }
}

/*
    Function: delete_node()
    Use: skip_list_obj.erase(searchKey)

    It deletes the element containing
   searchKey, if it exists.
*/
template <typename K, typename V, typename Comp >
void Skip_list<K, V, Comp>::erase (K searchKey) {
    // vector of pointers that needs to be updated to account for the deleted node
    std::vector<SkipNode<K, V>* > update(head->forward_);
    SkipNode<K, V>* x = head;
    int currentMaximum = nodeLevel(head->forward_);

    // search and update pointers
    for (int i = currentMaximum; i-- > 0;) {

        while (x->forward_[i] != nullptr &&  singleComp(x->forward_[i]->key_, searchKey)) {

            x = x->forward_[i];
        }
        update[i] = x;
    }
    x = x->forward_[0];

    // update pointers and delete node
    if (x->key_ == searchKey) {
        for (size_t i = 0; i < update.size(); ++i) {

            if (update[i]->forward_[i] != x) {

                break;
            }
            update[i]->forward_[i] = x->forward_[i];
        }
        delete x;
        size_ --;
    }
}

#endif