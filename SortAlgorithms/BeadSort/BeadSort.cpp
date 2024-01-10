#include <iostream> 
#include <algorithm>
#include <vector>
 
std::vector<int> bead_sort(std::vector<int> unsorted_vec){
    auto max_it = std::max_element(unsorted_vec.begin(), unsorted_vec.end());

    std::vector<std::vector<int>> beads(unsorted_vec.size());

    for (std::size_t i{}; i < unsorted_vec.size(); ++i) {
        beads[i].resize(*max_it, 0);
        // std::fill(beads[i].begin(), beads[i].end(), 0);
    }

    // mark the beads 
    for (std::size_t i{}; i < unsorted_vec.size(); ++i) { 
        for (std::size_t j{}; j < unsorted_vec[i]; ++j) { 
            beads[i][j] = 1; 
        } 
    } 

    // move down the beads 
    for (std::size_t j{}; j < *max_it; ++j) { 
        int sum = 0;
        for (std::size_t i{}; i < unsorted_vec.size(); ++i) { 
            sum += beads[i][j]; 
            beads[i][j] = 0; 
        } 
        for (int i = static_cast<int>(unsorted_vec.size())-1; i >= static_cast<int>(unsorted_vec.size())-sum; --i) { 
            beads[i][j] = 1; 
        } 
    } 

    // to get sorted array 
    std::vector<int> result;
    result.resize(unsorted_vec.size());
    for (std::size_t i{}; i < unsorted_vec.size(); ++i) { 
        int sum = 0; 
        for (std::size_t j{}; j < *max_it; ++j) { 
            sum += beads[i][j]; 
        } 
        result[i] = sum; 
    } 
    return result; 
} 
 
int main(){
    std::vector<int> ivec = {3, 1, 4, 1, 5};
    std::vector<int> sorted_vector = bead_sort(ivec);

    std::cout << "The sorted vector is: ";
    for (auto&& ival: sorted_vector) 
        std::cout << ival << " "; 
}