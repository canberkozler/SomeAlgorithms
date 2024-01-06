#include <iostream>
#include <vector>
#include <utility>
#include <exception>

// Define the Leonardo numbers
int leonardo(int k)
{
    if (k < 2) {
        return 1;
    }
    return leonardo(k - 1) + leonardo(k - 2) + 1;
}
 
// Build the Leonardo heap by merging
// pairs of adjacent trees
void heapify(std::vector<int>& arr, int start, int end){
    int i = start;
    int j{};
    int k{};
 
    while (k < end - start + 1) {
        if (k & 0xAAAAAAAA) {
            j = j + i;
            i = i >> 1;
        }
        else {
            i = i + j;
            j = j >> 1;
        }
 
        k = k + 1;
    }
 
    while (i > 0) {
        j = j >> 1;
        k = i + j;
        while (k < end) {
            if (arr[k] > arr[k - i]) {
                break;
            }
            std::swap(arr[k], arr[k - i]);
            k = k + i;
        }
 
        i = j;
    }
}
 
// Smooth Sort function
std::vector<int> smooth_sort(std::vector<int> ivec){
    int p = static_cast<int>(ivec.size()) - 1, q = p;
    int r {};
 
    // Build the Leonardo heap by merging
    // pairs of adjacent trees
    while (p > 0) {
        if ((r & 0x03) == 0) {
            heapify(ivec, r, q);
        }
 
        if (leonardo(r) == p) {
            r = r + 1;
        }
        else {
            r = r - 1;
            q = q - leonardo(r);
            heapify(ivec, r, q);
            q = r - 1;
            r = r + 1;
        }
 
        std::swap(ivec[0], ivec[p]);
        p = p - 1;
    }
 
    // Convert the Leonardo heap
    // back into an array
    for (std::size_t i{}; i < ivec.size() - 1; ++i)
        for (std::size_t j = i + 1 ; (j > 0) && (ivec[j] < ivec[j - 1]); j = --j) 
            std::swap(ivec[j], ivec[j - 1]);
 
    return ivec;
}

int main(){
    std::vector<int> ivec { 1, 7, 8, 2, 3, 5, 4, 6 };

    std::vector<int> sorted_ivec = smooth_sort(ivec);

    std::cout << "Input:   ";
    for (std::size_t i{}; i < ivec.size(); ++i) {
        std::cout << ivec[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Output:  ";
    for (std::size_t i{}; i < sorted_ivec.size(); ++i) {
        std::cout << sorted_ivec[i] << " ";
    }
}