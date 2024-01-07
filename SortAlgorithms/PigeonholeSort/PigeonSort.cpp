#include<vector>
#include<iostream>
#include<iterator> 
#include<algorithm>

void pigeonhole_sort(std::vector<int>& ivec){
    const auto [min, max] = std::minmax_element(ivec.begin(), ivec.end());
    auto range = *max - *min + 1; 
    
    std::vector<std::vector<int>> holes(range);
 
    // Traverse through input vector and put every
    // element in its respective hole
    for (std::size_t i{}; i < ivec.size(); ++i)
        holes[ivec[i]-*min].push_back(ivec[i]);
 
    // Traverse through all holes one by one. For
    // every hole, take its elements and put in vector.
    for (std::size_t index{}, i{}; i < range; ++i){
       for (auto&& elem: holes[i]) ivec[index++]  = elem;
    }
}

int main(){
    std::vector<int> ivec{8, 3, 2, 7, 4, 6, 8};
 
    pigeonhole_sort(ivec);

    std::cout <<"Sorted vector is: ";
    std::transform(ivec.begin(), ivec.end(), std::ostream_iterator<int>{std::cout, " "}, [](auto&& elem){ return elem;});
}