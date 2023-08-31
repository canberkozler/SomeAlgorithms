#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

template<typename C>
void gnome_sort(C& cont){
    std::size_t index{};
  
    while (index < cont.size()) {
        if (index == 0)
            ++index;
        if (cont[index] >= cont[index - 1])
            ++index;
        else {
            std::swap(cont[index], cont[index - 1]);
            --index;
        }
    }
}

int main(){
    std::vector<int> ivec{ 34, 2, 10, -9, 22, 356, 124, 89, -98, -23, 56};
    
    std::cout << "The container: ";
    std::transform(ivec.begin(), ivec.end(), std::ostream_iterator<int>{std::cout, " "}, [](auto elem){return elem;});
    std::cout << '\n';

    gnome_sort(ivec);
    
    std::cout << "The sorted container: ";
    std::transform(ivec.begin(), ivec.end(), std::ostream_iterator<int>{std::cout, " "}, [](auto elem){return elem;});
    std::cout << '\n';
}