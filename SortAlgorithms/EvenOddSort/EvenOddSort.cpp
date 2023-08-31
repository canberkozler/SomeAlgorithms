#include <iostream>
#include <array>
#include <algorithm>
#include <utility>
#include <iterator>
 
// Odd Even Sort (Brick Sort) Implementation
template<typename C, typename Cmp = std::greater<>>
void odd_even_sort(C& cont, Cmp cp= Cmp{}){
    bool isSorted = false; // Initially container is unsorted
 
    while (!isSorted){
        isSorted = true;

        // Perform Bubble sort on odd indexed element
        for (std::size_t i{1}; i<cont.size()-1; i+=2){
            if (cp(cont[i], cont[i+1])){
                std::swap(cont[i], cont[i+1]);
                isSorted = false;
            }
        }

        // Perform Bubble sort on even indexed element
        for (std::size_t i{}; i<cont.size()-1; i+=2){
            if (cp(cont[i], cont[i+1])){
                std::swap(cont[i], cont[i+1]);
                isSorted = false;
            }
        }
    }
}

int main(){
    std::array<int, 10> i_arr{34, 2, 10, -9, 23, -56, 9, 64, -1, 234};
    std::cout << "The container: "; 
    std::copy(std::begin(i_arr), std::end(i_arr), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<"\n";

    odd_even_sort(i_arr);
    std::cout << "The sorted container: "; 
    std::copy(std::begin(i_arr), std::end(i_arr), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<"\n";

    odd_even_sort(i_arr, std::less{});
    std::cout << "The sorted container (greater to less): "; 
    std::copy(std::begin(i_arr), std::end(i_arr), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<"\n";
}