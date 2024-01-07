#include<vector>
#include<iostream>
#include<limits>

std::vector<int> merge_piles(std::vector<std::vector<int>>& v){
    // Store minimum element from the top of stack
    std::vector<int> ans;
 
    // In every iteration find the smallest element
    // of top of pile and remove it from the piles
    // and store into the final array
    while(true){
        // Stores the smallest element
        // of the top of the piles
        int minu = std::numeric_limits<int>::max();
 
        // Stores index of the smallest element
        // of the top of the piles
        std::size_t index = std::numeric_limits<std::size_t>::max();
 
        // Calculate the smallest element
        // of the top of the every stack
        for (std::size_t i{}; i < v.size(); ++i){
            // If minu is greater than
            // the top of the current stack
            if (minu > v[i][v[i].size() - 1]) {
 
                // Update minu
                minu = v[i][v[i].size() - 1];
 
                // Update index
                index = i;
            }
        }
 
        // Insert the smallest element
        // of the top of the stack
        ans.push_back(minu);
 
        // Remove the top element from
        // the current pile
        v[index].pop_back();
 
        // If current pile is empty
        if (v[index].empty()) {
 
            // Remove current pile
            // from all piles
            v.erase(v.begin() + index);
        }
 
        // If all the piles are empty
        if (v.empty()) break;
    }
    return ans;
}

std::vector<int> patienceSorting(const std::vector<int>& ivec){
    // Store all the created piles
    std::vector<std::vector<int>> piles;
 
    // Traverse the array
    for (std::size_t i{}; i < ivec.size(); ++i) {
 
        // If no piles are created
        if (piles.empty()) piles.push_back({ivec[i]});
        else {
            // Check if top element of each pile
            // is less than or equal to
            // current element or not
            bool flag = 1;
 
            // Traverse all the piles
            for (std::size_t j{}; j < piles.size(); ++j) {
 
                // Check if the element to be
                // inserted is less than
                // current pile's top
                if (ivec[i] < piles[j][piles[j].size() - 1]) {
                    piles[j].push_back(ivec[i]);
 
                    // Update flag
                    flag = 0;
                    break;
                }
            }
 
            // If the element is greater than current piles' top.
            if (flag) piles.push_back({ivec[i]});
        }
    }

    return merge_piles(piles);
}
 
int main(){
    std::vector<int> ivec{ 6, 12, 2, 8, 3, 7 };

    auto sorted_ivec = patienceSorting(ivec);
    std::cout<< " Sorted vector is: ";
    for (std::size_t i{}; i < sorted_ivec.size(); ++i)
        std::cout << sorted_ivec[i] << " ";
}