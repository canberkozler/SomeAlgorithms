#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

/*
std::vector<int> merge(const std::vector<int>& ivec1, const std::vector<int>& ivec2){
    std::vector<int> merged_vector;
    merged_vector.reserve(ivec1.size() + ivec2.size());

    std::size_t i{}, j{};
 
    while (i < ivec1.size() && j < ivec2.size()) {
        if (ivec1[i] < ivec2[j])
            merged_vector.push_back(ivec1[i++]);
        else
            merged_vector.push_back(ivec2[j++]);
    }
 
    while (i < ivec1.size())
        merged_vector.push_back(ivec1[i++]);
 
    while (j < ivec2.size())
        merged_vector.push_back(ivec2[j++]);
 
    return merged_vector;
}
*/

/*
std::vector<int> merge(const std::vector<int>& ivec1, const std::vector<int>& ivec2) {
    std::vector<int> merged_vector;
    merged_vector.reserve(ivec1.size() + ivec2.size());

    auto ivec1_it = ivec1.begin();
    auto ivec2_it = ivec2.begin();

    while (ivec1_it != ivec1.end() && ivec2_it != ivec2.end()) {
        if (*ivec1_it < *ivec2_it)
            merged_vector.push_back(*ivec1_it++);
        else
            merged_vector.push_back(*ivec2_it++);
    }

    merged_vector.insert(merged_vector.end(), ivec1_it, ivec1.end());
    merged_vector.insert(merged_vector.end(), ivec2_it, ivec2.end());

    return merged_vector;
}
*/


// efficient for sorting strings
std::vector<int> merge(const std::vector<int>& ivec1, const std::vector<int>& ivec2){
    std::vector<int> merged_vector;
    
    std::merge(ivec1.begin(), ivec1.end(), ivec2.begin(), ivec2.end(), std::back_inserter(merged_vector));
 
    return merged_vector;
}

// Divides an vector into two parts
std::vector<std::vector<int>> split(const std::vector<int>& ivec){
    return {{ivec.begin(), ivec.begin() + (ivec.size() / 2)}, {ivec.begin() + (ivec.size() / 2), ivec.end()}};
}

std::vector<int> burst_sort(const std::vector<int>& ivec){
    if (ivec.size() == 1)
        return ivec;
 
    std::vector<std::vector<int>> sub_vectors = split(ivec);

    std::vector<int> arr1 = burst_sort(sub_vectors[0]);
    std::vector<int> arr2 = burst_sort(sub_vectors[1]);

    return merge(arr1, arr2);
}

int main()
{
    std::vector<int> ivec{1, 5, 3, 7, 2, 4, 6, 21, 31, 23, 12, 4, 15, 12, 52, 35, 23, 41, 34, 2};
    ivec = burst_sort(ivec);
    
    std::cout << "The sorted vector is: ";
    for (auto&& ival: ivec)
        std::cout << ival << " ";
 
}