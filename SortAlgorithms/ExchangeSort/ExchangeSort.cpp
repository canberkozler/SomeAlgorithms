#include <array>
#include <iostream>
#include <utility>

template<typename T, std::size_t N, typename Order = std::greater<T>>
void exchanges_sort(std::array<T, N>& num, Order ordr = Order{}){
    for (std::size_t i{}; i < N - 1; ++i) 
        for (std::size_t j{i + 1}; j < N; ++j) 
            if (ordr(num[i], num[j])) std::swap(num[i], num[j]);
}
int main(){
    std::array<int, 5> arr { 5, 1, 4, 2, 8 };
 
    exchanges_sort(arr);
    std::cout << "Exchanges sort in ascending order: ";
    for (std::size_t i{}; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    
    std::cout<< "\n";

    exchanges_sort<int, arr.size(), std::less<int>>(arr);
    std::cout << "Exchanges sort in descending order: ";
    for (std::size_t i{}; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
}