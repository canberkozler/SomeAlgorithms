#include <iostream>
#include <array>
#include <utility>
#include <cstddef>

// To find gap between elements
std::size_t get_next_gap(std::size_t gap){
    gap = gap*10/13; // Shrink gap w 1.3.
 
    if (gap < 1)
        return 1;
    
    return gap;
}

template<typename C, typename Comp = std::greater<>>
void combSort(C& cont, Comp cp = Comp{}){
    std::size_t gap = cont.size();
    bool flag = true;
 
    while (gap != 1 || flag){
        gap = get_next_gap(gap);
 
        flag = false;
 
        // Compare all elements with current gap
        for (std::size_t i{}; i<cont.size()-gap; ++i){ // Gap can not be bigger than cont.size().
            if (cp(cont[i], cont[i+gap])){
                std::swap(cont[i], cont[i+gap]);
                flag = true;
            }
        }
    }
}

int main(){
    std::array<int, 10> i_arr{8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    std::cout<<"The container: ";
    for (auto elem : i_arr)
        std::cout<<elem<<" ";
    std::cout<<"\n";

    combSort(i_arr);
 
    std::cout<<"The sorted container: ";
    for (auto elem : i_arr)
        std::cout<<elem<<" ";
    std::cout<<"\n";
}