#include<iostream>
#include<utility>

// Elegant Way
template<size_t n>
struct Fibonacci {
	static const size_t value{ n > 1 ? n + Fibonacci<n - 1>::value : 1};
};

template<>
struct Fibonacci<0> {
	static const size_t value{ 0 };
};

int main(){
	std::cout << Fibonacci<10>::value << "\n";

    // https://en.cppreference.com/w/cpp/utility/exchange
    size_t N{};
    std::cout << "Enter the upper bound?\n";
    std::cin >> N;

    std::cout << "\nFibonacci sequence: ";
    for (size_t a{0}, b{1}; a < N; a = std::exchange(b, a + b))
        std::cout << a << ", ";
    std::cout << "...\n";
}