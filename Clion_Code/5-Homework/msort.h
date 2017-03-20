#ifndef MSORT_H
#define MSORT_H

#include "vector"
#include "string"


using namespace std;

template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp);


#endif
