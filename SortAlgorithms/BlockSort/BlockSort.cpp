#include <iostream>
#include <vector>
#include <algorithm>
 
std::vector<int> blockSort(const std::vector<int>& ivec, std::size_t blockSize){
    std::vector<std::vector<int>> blocks;

    // Divide the input array into blocks of size blockSize
    for (std::size_t i = 0; i < ivec.size(); i += blockSize) {
        std::vector<int> block;

        for (std::size_t j = i; j < i + blockSize && j < ivec.size(); ++j) {
            block.push_back(ivec[j]);
        }

        std::sort(block.begin(), block.end());
        blocks.push_back(block);
    }

    // Merge the sorted blocks into a single sorted list
    std::vector<int> result_ivec;
    while (!blocks.empty()) {
        // Find the smallest element in the first block of
        // each sorted block
        std::size_t minIdx{};
        for (std::size_t i = 1; i < blocks.size(); ++i) {
            if (blocks[i][0] < blocks[minIdx][0]) minIdx = i;
        }

        // Remove the smallest element and append it to the
        // result list
        result_ivec.push_back(blocks[minIdx][0]);
        blocks[minIdx].erase(blocks[minIdx].begin());

        // If the block is now empty, remove it from the
        // list of sorted blocks
        if (blocks[minIdx].empty()) blocks.erase(blocks.begin() + minIdx);
    }

    return result_ivec;
}
 
int main(){
    std::vector<int> ivec{ 1, 7, 8, 2, 3, 5, 4, 6 };

    // Select box size
    std::size_t blockSize = 3;
 
    // Function call
    std::vector<int> sorted_ivec = blockSort(ivec, blockSize);
    
    std::cout << "Input: ";
    for (std::size_t i{}; i < ivec.size(); ++i) {
        std::cout << ivec[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Output: ";
    for (std::size_t i{}; i < sorted_ivec.size(); ++i) {
        std::cout << sorted_ivec[i] << " ";
    }
}