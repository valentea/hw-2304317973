#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <climits>
#include <vector>


template <typename K, typename V, typename Comp = std::less<K> >
struct SkipNode {
    K key_;
    V value_;

    // pointers to successor nodes
    std::vector<SkipNode*> forward_;

    SkipNode (int k, const std::string& v, int level);
};


class Skip_list {
public:
    Skip_list ();
    ~Skip_list ();

    // non-modifying member functions
    void print ();
    SkipNode* find (int searchKey);

    // modifying member functions
    void insert (int searchKey, std::string newValue);
    void erase (int searchKey);
private:
    // pointer to first node
    SkipNode* head;
    // last node
    SkipNode* NIL;

    // implicitly used member functions
    int randomLevel ();
    int nodeLevel(const std::vector<SkipNode*>& v);
    SkipNode* makeNode (int key, std::string val, int level);

    // data members
    float probability;
    int maxLevel;
};


SkipNode::SkipNode (int k, const std::string& v, int level)
        :  key_(k), value_(v)
{
    for (int i = 0; i < level; ++i) forward_.emplace_back(nullptr);
}

//==============================================================================
// Class Skip_list member implementations
// constructor
Skip_list::Skip_list()
        : probability(0.5), maxLevel(16)
{
    // Initialize the head of the skip list

    // smallest possible key_
    int headKey = INT_MIN;
    head = new SkipNode(headKey, "head", maxLevel);

    // Initialize the last element of the list

    // largest possible key_
    int nilKey = INT_MAX;
    NIL = new SkipNode(nilKey, "NIL", maxLevel);

    // Connect start to end
    // connect all the levels/forward_ pointers of the header to NIL
    for (size_t i = 0; i < head->forward_.size(); ++i) {
        head->forward_[i] = NIL;
    }
}

// destructor
Skip_list::~Skip_list () {
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
int Skip_list::randomLevel () {
    int v = 1;

    while ((((double)std::rand() / RAND_MAX)) < probability &&
           std::abs(v) < maxLevel) {

        v += 1;
    }
    return abs(v);
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
int Skip_list::nodeLevel (const std::vector<SkipNode*>& v) {
    int currentLevel = 1;
    // last element's key_ is the largest
    int nilKey = INT_MAX;

    if (v[0]->key_ == nilKey) {
        return currentLevel;
    }

    for (size_t i = 0; i < v.size(); ++i) {

        if (v[i] != nullptr && v[i]->key_ != nilKey) {
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
void Skip_list::print () {
    SkipNode* list = head;
    int lineLenght = 1;

    std::cout <<"{";

    while (list->forward_[0] != nullptr) {
        std::cout <<"value_: "<< list->forward_[0]->value_
                  <<", key_: "<< list->forward_[0]->key_
                  <<", level: "<< nodeLevel(list->forward_);

        list = list->forward_[0];

        if (list->forward_[0] != nullptr) std::cout <<" : ";

        if (++lineLenght % 2 == 0) std::cout <<"\n";
    }
    std::cout <<"}\n";
}

/*
    Function: find()
    Use: SkipNode* found = skip_list_obj.find(searchKey);

    It searches the skip list and
    returns the element corresponding
    to the searchKey; otherwise it returns
    failure, in the form of null pointer.
*/
SkipNode* Skip_list::find(int searchKey) {
    SkipNode* x = head;
    unsigned int currentMaximum = nodeLevel(head->forward_);

    for (unsigned int i = currentMaximum; i-- > 0;) {
        while (x->forward_[i] != nullptr && x->forward_[i]->key_ < searchKey) {
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
SkipNode* Skip_list::makeNode (int key, std::string val, int level) {
    return new SkipNode(key, val, level);
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
void Skip_list::insert(int searchKey, std::string newValue) {
    // reassign if node exists
    SkipNode* x = nullptr;
    x = find(searchKey);
    if (x) {
        x->value_ = newValue;
        return;
    }

    // vector of pointers that needs to be updated to account for the new node
    std::vector<SkipNode*> update(head->forward_);
    unsigned int currentMaximum = nodeLevel(head->forward_);
    x = head;

    // search the list
    for (unsigned int i = currentMaximum; i-- > 0;) {

        while (x->forward_[i] != nullptr && x->forward_[i]->key_ < searchKey) {

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
void Skip_list::erase (int searchKey) {
    // vector of pointers that needs to be updated to account for the deleted node
    std::vector<SkipNode*> update(head->forward_);
    SkipNode* x = head;
    unsigned int currentMaximum = nodeLevel(head->forward_);

    // search and update pointers
    for (unsigned int i = currentMaximum; i-- > 0;) {

        while (x->forward_[i] != nullptr && x->forward_[i]->key_ < searchKey) {

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
    }
}

#endif