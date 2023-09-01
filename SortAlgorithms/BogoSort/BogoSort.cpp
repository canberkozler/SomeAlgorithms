#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

template<typename C>
void bogo_sort(C& cont){
    static std::mt19937 eng(std::random_device{}());

    while (!std::is_sorted(cont.begin(), cont.end())){
        std::shuffle(cont.begin(), cont.end(), eng);
    }
}

int main(){
    std::vector<int> ivec{ 3, 2, 5, 1, 0, 4 };
    bogo_sort(ivec);
    printf("Sorted array :");
    for(auto elem : ivec)
        std::cout<<elem << " ";
    std::cout << "\n";
}