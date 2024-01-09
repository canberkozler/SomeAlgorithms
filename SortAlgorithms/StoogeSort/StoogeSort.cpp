#include <iostream> 
#include <vector>
#include <utility>

void stooge_sort(std::vector<int>& ivec, std::size_t l, std::size_t h){
    if (l >= h) 
        return; 

    if (ivec[l] > ivec[h]) 
        std::swap(ivec[l], ivec[h]); 

    if (h - l + 1 > 2){ 
        auto t = (h - l + 1) / 3; 
  
        // First 2/3 elements 
        stooge_sort(ivec, l, h - t); 
  
        // Last 2/3 elements 
        stooge_sort(ivec, l + t, h); 
  
        // First 2/3 elements again
        stooge_sort(ivec, l, h - t); 
    }
}

int main() 
{
    std::vector<int> ivec{2, 4788, 5, 31, 1, 205, 4, 0, 2, 22, 1, 123, 112, 156, 196, 23, 4};

    stooge_sort(ivec, 0, ivec.size() - 1); 

    std::cout << "Sorted vector is: ";
    for (auto&& ival : ivec) 
        std::cout << ival<< " "; 

} 