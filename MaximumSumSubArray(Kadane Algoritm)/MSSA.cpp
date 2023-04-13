#include <iostream>
#include <vector>
#include <algorithm>
 
// Function to find the maximum sum of a contiguous subarray
// in a given integer array
int kadane(const std::vector<int>& ivec)
{
    // find the maximum element present in a given array
    int max_num = *max_element(ivec.begin(), ivec.end());
 
    // if the array contains all negative values, return the maximum element
    if (max_num < 0) return max_num;
 
    // stores the maximum sum subarray found so far
    int max_so_far = 0;
 
    // stores the maximum sum of subarray ending at the current position
    int max_ending_here = 0;
 
    // traverse the given array
    for (int i = 0; i < ivec.size(); i++)
    {
        // update the maximum sum of subarray "ending" at index 'i' (by adding the
        // current element to maximum sum ending at previous index 'i-1')
        max_ending_here = max_ending_here + ivec[i];
 
        // if the maximum sum is negative, set it to 0 (which represents
        // an empty subarray)
        max_ending_here = std::max(max_ending_here, 0);
 
        // update the result if the current subarray sum is found to be greater
        max_so_far = std::max(max_so_far, max_ending_here);
    }
 
    return max_so_far;
}
 
int main()
{
    std::vector<int> ivec = { 71, -8, -3, -66 ,-2, -5, -4,3,4,66,6 };
 
    std::cout << "The maximum sum of a contiguous subarray is " << kadane(ivec);
 
    return 0;
}
