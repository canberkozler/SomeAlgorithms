/* 
 * Tim Sort is a hybrid sorting algorithm derived from merge sort and insertion sort. 
 * It was designed to perform well on many kinds of real-world data. Tim Sort is the 
 * default sorting algorithm used by Python’s sorted() and list.sort() functions.
 */
 
#include <iostream>
#include <array>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <vector>

static constexpr std::size_t RUN = 32; 

// This function sorts array from left 
// index to to right index which is 
// of size atmost RUN 
void insertionSort(int arr[], int left, int right) { 
    for (int i = left + 1; i <= right; ++i) { 
        auto temp = arr[i]; 
        auto j = i-1; 
        while (j >= left && arr[j] > temp) { 
            arr[j + 1] = arr[j]; 
            --j; 
        } 
        arr[j + 1] = temp; 
    } 
} 
  
// Merge function merges the sorted runs 
template<std::size_t n>
void merge(std::array<int, n>& arr, std::size_t l, std::size_t m, std::size_t r) {
    // Original array is divided into two 
    // parts left and right array 
    std::size_t len1 = m - l + 1, len2 = r - m; 
    std::vector<int> left(len1), right(len2);

    std::copy(std::next(arr.begin(), l), std::next(arr.begin(), l + len1), left.begin());
    std::copy(std::next(arr.begin(), m + 1), std::next(arr.begin(), m + 1 + len2), right.begin());

    std::size_t i{}, j{}, k{1};

    // After comparing, we
    // merge those two array
    // in larger sub array
    while (i < len1 && j < len2){
        if (left[i] <= right[j]){
            arr[k] = left[i];
            ++i;
        }
        else{
            arr[k] = right[j];
            ++j;
        }
        ++k;
    }

    // Copy remaining elements of
    // left, if any
    while (i < len1){
        arr[k] = left[i];
        ++k;
        ++i;
    }

    // Copy remaining element of
    // right, if any
    while (j < len2){
        arr[k] = right[j];
        ++k;
        ++j;
    }
}

// Iterative Timsort function to sort the 
// array[0...n-1] (similar to merge sort) 
template<std::size_t n>
void timSort(std::array<int, n>& arr){
    // Sort individual subarrays of size RUN 
    for (std::size_t i = 0; i < n; i += RUN)
        insertionSort(arr.data(), static_cast<int>(i), static_cast<int>(std::min((i + RUN - 1), (n - 1)))); 
  
    // Start merging from size RUN (or 32). 
    // It will merge 
    // to form size 64, then 128, 256 
    // and so on .... 
    for (std::size_t size = RUN; size < n; size = 2 * size){ 
  
        // pick starting point of 
        // left sub array. We 
        // are going to merge 
        // arr[left..left+size-1] 
        // and arr[left+size, left+2*size-1] 
        // After every merge, we 
        // increase left by 2*size 
        for (std::size_t left = 0; left < n; left += 2 * size){ 
  
            // Find ending point of 
            // left sub array 
            // mid+1 is starting point 
            // of right sub array 
            std::size_t mid = left + size - 1; 
            std::size_t right = std::min((left + 2 * size - 1),(n - 1)); 
  
            // merge sub array arr[left.....mid] & 
            // arr[mid+1....right] 
            if (mid < right) 
                merge(arr, left, mid, right);
        } 
    } 
}

int main() 
{ 
    std::array<int, 15> arr{-2, 7, 15, -14, 0, 15, 0, 7, 
                  -7, -4, -13, 5, 8, -14, 12}; 
    std::cout<< "Given array is: ";
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout<<"\n";

    timSort(arr); 
    std::cout<< "Sorted array is: ";
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>{std::cout, " "});
}