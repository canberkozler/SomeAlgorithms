#include<iostream>
#include<utility>

// https://en.cppreference.com/w/cpp/utility/exchange

int main(){
    size_t N{};
    std::cout << "Enter the upper bound?\n";
    std::cin >> N;

    std::cout << "\nFibonacci sequence: ";
    for (size_t a{0}, b{1}; a < N; a = std::exchange(b, a + b))
        std::cout << a << ", ";
    std::cout << "...\n";
}