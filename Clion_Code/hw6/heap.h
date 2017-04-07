#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <stdexcept>
#include <vector>




template<typename T, typename Comparator = std::less<T> >
class Heap {
public:
    /// Constructs an m-ary heap for any m >= 2
    Heap(int m, Comparator c = Comparator());

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T &item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const &top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    int size();

    struct less
    {
        bool operator()(const T& v1, const T& v2){
            return v1 < v2;
        }
    };

private:
    /// Add whatever helper functions and data members you need below

    int currSize_ = 0;
    T currItem_;
    std::vector<T> heap_;
    void heapify(int idx);
    void trickleUp(int loc);




};

// Add implementation of member functions here


template<typename T, typename Comparator>
void Heap<T, Comparator>::trickleUp(int loc) {
    int parent = loc / 2;
    while (parent >= 1 && heap_[loc] < heap_[parent]) {
        T temp;
        temp = heap_[parent];
        heap_[parent] = heap_[loc];
        heap_[loc] = temp;
        parent = loc / 2;
    }
}

template<typename T, typename Comparator>
Heap<T, Comparator>::Heap(int m, Comparator c){

}

template<typename T, typename Comparator>
Heap<T, Comparator>::~Heap() {

}

template<typename T, typename Comparator>
void Heap<T, Comparator>::push(const T &item){
    heap_.push_back(item);
    trickleUp((int)heap_.size()-1);
    currSize_++;

}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template<typename T, typename Comparator>
T const &Heap<T, Comparator>::top() const {
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if (empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return heap_[0];
}


template<typename T, typename Comparator>
void Heap<T, Comparator>::heapify(int idx) {
    int smallerChild = 2*idx + 1; // start w/ left
    int rChild = smallerChild + 1;

    if(smallerChild>size()-1 && rChild>size()-1) return;

    if (heap_[rChild] != NULL) {
        if (heap_[rChild] < heap_[smallerChild])
            smallerChild = rChild;
    }
    if (heap_[idx] > heap_[smallerChild]) {
        T temp;
        temp = heap_[idx];
        heap_[idx] = heap_[smallerChild];
        heap_[smallerChild] = temp;
        heapify(smallerChild);
    }
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template<typename T, typename Comparator>
void Heap<T, Comparator>::pop() {
    if (empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    heap_[0] = heap_.back();
    heap_.pop_back();
    currSize_--;
    heapify(0);
}

template<typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const {
    return currSize_==0;
}

template<typename T, typename Comparator>
int Heap<T, Comparator>::size(){
    return currSize_;
};


#endif

