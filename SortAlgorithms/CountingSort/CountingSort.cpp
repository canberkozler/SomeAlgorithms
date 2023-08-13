#include <iostream>
#include <vector>
#include <algorithm>
 
void countsort(std::vector<int>& ivec){
    // create an integer vector of size `n` to store the sorted array
    std::vector<int> output(ivec.size());
 
    // create an integer vector of size `MAX_ELEM+1`, initialized by all zero
    std::vector<int> freq(*max_element(begin(ivec),end(ivec))+1, 0);
 
    // 1. Using the value of each item in the input array as an index,
    // store each integer's count in `freq[]`
    for (size_t i{0}; i < ivec.size(); ++i) {
        freq[ivec[i]]++;
    }
 
    // overwrite the input array with sorted order
    int index = 0;
    for (size_t i{0}; i <freq.size(); ++i)
    {
        while (freq[i]--) {
            ivec[index++] = i;
        }
    }
}
 
int main()
{
    std::vector<int> ivec = { 4, 2, 10, 10, 1, 4, 2, 1, 10 };
    // range of array elements
 
    countsort(ivec);
 
    for (const auto& ival : ivec) {
        std::cout<< ival << " ";
    }
 
    return 0;
}