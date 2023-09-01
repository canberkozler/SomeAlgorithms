#include <iostream>
#include <array>
#include <utility>
#include <cstddef>

template<typename C, typename Comp = std::greater<>>
bool circleSortRec(C& cont, std::size_t low, std::size_t high, Comp cp = Comp{}){
    bool flag{};

    if (low == high)
        return false;

    std::size_t lo = low, hi = high;

    while (lo < hi){
        if (cp(cont[lo], cont[hi])){
            std::swap(cont[lo], cont[hi]);
            flag = true;
        }
        ++lo;
        --hi;
    }

    if ((lo == hi) && cp(cont[lo], cont[hi + 1])){
        std::swap(cont[low], cont[hi + 1]);
        flag = true;
    }

    std::size_t mid = (high - low) / 2;
    bool firstHalf = circleSortRec(cont, low, low+mid);
    bool secondHalf = circleSortRec(cont, low+mid+1, high);

    return flag || firstHalf || secondHalf;
}
 
template<typename C>
void circleSort(C& cont){
    if(cont.empty()){
        std::cerr << " Empty Container!!";
        return;
    }

    while (circleSortRec(cont, 0, cont.size()-1));
}

int main(){
    std::array<int, 8> i_arr{8, 4, 1, 56, 3, -44, 23, -6}; // Number of element needs to be power of 2; otherwise, code stuck at infinite loop.
    std::cout<<"The container: ";
    for (auto elem : i_arr)
        std::cout<<elem<<" ";
    std::cout<<"\n";

    circleSort(i_arr);
 
    std::cout<<"The sorted container: ";
    for (auto elem : i_arr)
        std::cout<<elem<<" ";
    std::cout<<"\n";
}