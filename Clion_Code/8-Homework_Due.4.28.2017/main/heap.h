#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

using namespace std;

template <
         typename T,
         typename TComparator = std::equal_to<T>,
         typename PComparator = std::less<double>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const TComparator& tcomp = TComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item with the provided priority
    void push(double pri, const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey reduces the current priority of
    /// item to newpri, moving it up in the heap
    /// as appropriate.
    void decreaseKey(double newpri, const T& item);

    void print();

private:
    /// Add whatever helper functions you need below
    void reHeapUp(int hole);
    int smallestChild(int hole);
    int kthChild(int i, int k);
    void reHeapDown(int hole);


    // These should be all the data members you need.
    std::vector< std::pair<double, T> > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, TComparator> keyToLocation_;
    int parent(int hole);
    int size_;

};

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const TComparator& tcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, tcomp),
    size_(0)

{

}

// Complete
template <typename T, typename TComparator, typename PComparator, typename Hasher >
Heap<T,TComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::push(double priority, const T& item)
{
    int hole = size_;
    size_++;
    std::pair<double, T> temp;
    temp = make_pair(priority, item);
    store_.push_back(temp);
    reHeapUp(hole);
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::decreaseKey(double priority, const T& item)
{
    // You complete

}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
T const & Heap<T,TComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // You complete
    return store_[0].second;
}

/// Removes the top element
template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T,TComparator,PComparator,Hasher>::pop(){
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    // You complete
    size_--;
    store_.pop_back();
    reHeapDown(size_);
}

/// returns true if the heap is empty
template <typename T, typename TComparator, typename PComparator, typename Hasher >
bool Heap<T,TComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
int Heap<T, TComparator, PComparator, Hasher>::parent(int hole){
        return (hole - 1) / m_;
};


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::reHeapUp(int hole) {
    int parNode = parent(hole);

    while (parNode >= 0) {
        if (c_(store_[hole].first, store_[parNode].first)) {
            swap(store_[hole], store_[parNode]);
            hole = parNode;
            parNode = parent(hole);
        }
        else {
            break;
        }
    }
}


template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::reHeapDown(int hole){
    // child array to store indexes of all
    // the children of given node
    int child[m_+1];

    while (1)
    {
        // child[i]=-1 if the node is a leaf
        // children (no children)
        for (int i=1; i<=m_; i++) {
            child[i] = ((m_ * hole + i) < size_) ? (m_ * hole + i) : -1;
        }

        // max_child stores the maximum child and
        // max_child_index holds its index
        pair<double, T> max_child = make_pair((double)-1, (T)-1);
        int max_child_index = -1;

        // loop to find the maximum of all
        // the children of a given node
        for (int i = 1; i <= m_; i++) {
            if (child[i] != -1 && store_[child[i]].first < max_child.first) {
                max_child_index = child[i];
                max_child = store_[child[i]];
            }
        }

        // leaf node
        if (max_child.first == -1) {
            break;
        }

        // swap only if the key of max_child_index
        // is greater than the key of node
        if (store_[hole].first < store_[max_child_index].first)
            swap(store_[hole], store_[max_child_index]);

        hole = max_child_index;
    }
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
int Heap<T, TComparator, PComparator, Hasher>::smallestChild(int hole) {
    int bestChildYet = kthChild(hole, 1);
    int k = 2;
    int candidateChild = kthChild(hole, k);
    while ((k <= m_) && (candidateChild < size_)) {
        if (store_[candidateChild].first < store_[bestChildYet].first)
            bestChildYet = candidateChild;
        k++;
        candidateChild = kthChild(hole, k);
    }
    return bestChildYet;
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
int Heap<T, TComparator, PComparator, Hasher>::kthChild(int i, int k)
{
    return m_ * i + k;
}

template <typename T, typename TComparator, typename PComparator, typename Hasher >
void Heap<T, TComparator, PComparator, Hasher>::print(){
    if(empty()){
        cout << "empty heap" << endl;
    }
    for (int i = 0; i < size_; ++i) {
        cout << store_[i].first << ", " << store_[i].second << " " << endl;
    }
    cout << endl;
}

#endif

