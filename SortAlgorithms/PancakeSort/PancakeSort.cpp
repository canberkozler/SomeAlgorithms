#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

void flip(std::vector<int>& ivec, std::size_t i) {    
    for (std::size_t start{}; start < i; ++start) { 
        std::swap(ivec[start], ivec[i]);
        --i; 
    } 
} 

void pancake_sort(std::vector<int>& ivec) {
    // Start from the complete array and one by one reduce current size by one.
    // detractive_cntr is for reducing size.
    for (std::size_t curr_size = ivec.size(), detractive_cntr{}; curr_size > 1; --curr_size) { 
        // Find index of the maximum element in arr[0..curr_size-1] 
        auto mi = std::distance(ivec.begin(), std::max_element(ivec.begin(), ivec.end() - detractive_cntr));
 
        // Move the maximum element to end of current array if it's not already at the end 
        if (mi != curr_size-1){ 
            // To move at the end, first move maximum number to beginning 
            flip(ivec, mi); 

            // Move the maximum number to end by reversing current array 
            flip(ivec, curr_size-1); 
        } 
        ++detractive_cntr;
    }
} 

int main(){ 
    std::vector<int> ivec{23, 10, 20, 11, 12, 6, 7}; 

    pancake_sort(ivec);

    // for printing
    std::cout << "Sorted container is: ";
    std::transform(ivec.begin(), ivec.end(), std::ostream_iterator<int>{std::cout, " "}, [](auto elem) { return elem; });
}