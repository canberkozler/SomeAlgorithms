#include <iostream>
#include <algorithm>
 
// Partition using the Lomuto partition scheme
int partition(int a[], int start, int end)
{
    // Pick the rightmost element as a pivot from the array
    int pivot = a[end];
 
    // elements less than the pivot will be pushed to the left of `pIndex`
    // elements more than the pivot will be pushed to the right of `pIndex`
    // equal elements can go either way
    int pIndex = start;
 
    // each time we find an element less than or equal to the pivot, `pIndex`
    // is incremented, and that element would be placed before the pivot.
    for (int i{start}; i < end; ++i){
        if (a[i] <= pivot){
            std::swap(a[i], a[pIndex]);
            ++pIndex;
        }
    }
 
    // swap `pIndex` with pivot
    std::swap(a[pIndex], a[end]);
 
    // return `pIndex` (index of the pivot element)
    return pIndex;
}
 
// Quicksort routine
void quicksort(int a[], int start, int end)
{
    // if matris is empty or has one-element, quicksort returns
    if (start >= end) {
        return;
    }
 
    // rearrange elements across pivot
    int pivot = partition(a, start, end);
 
    // recur on subarray containing elements that are less than the pivot
    quicksort(a, start, pivot - 1);
 
    // recur on subarray containing elements that are more than the pivot
    quicksort(a, pivot + 1, end);
}
 
// C++ implementation of the Quicksort algorithm
int main()
{
    int a[] = { 9, -3, 5, 2, 6, 8, -6, 1, 3 }; 
    quicksort(a, 0, std::size(a) - 1); // parameters are array, idx of first element and idx of last element

    // print the sorted array
    for (const auto& ival: a) {
        std::cout << ival << " ";
    }
}
