#include <iostream>
#include <vector>
#include <algorithm>
// Merge two sorted subarrays `arr[low … mid]` and `arr[mid+1 … high]`
void Merge(std::vector<int>& ivec, std::vector<int>& aux, int low, int mid, int high)
{
    int k = low, i = low, j = mid + 1;
 
    // while there are elements in the left and right runs
    while (i <= mid && j <= high)
    {
        if (ivec[i] <= ivec[j]) {
            aux[k++] = ivec[i++];
        }
        else {
            aux[k++] = ivec[j++];
        }
    }
 
    // copy remaining elements
    while (i <= mid) {
        aux[k++] = ivec[i++];
    }
 
    // No need to copy the second half (since the remaining items
    // are already in their correct position in the auxiliary array)
 
    // copy back to the original array to reflect sorted order
    for (int i = low; i <= high; i++) {
        ivec[i] = aux[i];
    }
}
 
// Sort array `arr[low…high]` using auxiliary array `aux`
void mergesort(std::vector<int>& ivec, std::vector<int>& auxvec, int low, int high)
{
    // base case
    if (high <= low) {        // if run size <= 1
        return;
    }
 
    // find midpoint
    int mid = (low + ((high - low) >> 1));
 
    // recursively split runs into two halves until run size <= 1,
    // then merge them and return up the call chain
 
    mergesort(ivec, auxvec, low, mid);          // split/merge left half
    mergesort(ivec, auxvec, mid + 1, high);     // split/merge right half
 
    Merge(ivec, auxvec, low, mid, high);        // merge the two half runs.
}

// Implementation of merge sort algorithm in C
int main(void)
{
    std::vector<int> ivec{3,2,5,67,7,1,8,4,22};
    std::vector<int> auxvec{ivec};
 
    // sort array `arr` using auxiliary array `aux`
    mergesort(ivec, auxvec, 0, ivec.size() - 1);
 
    if (is_sorted(begin(ivec), end(ivec))){
        for (const auto& elem : ivec) std::cout<< elem << " ";
    }
    else{
        std::cout<< "Not Sorted...\n";
    }
}