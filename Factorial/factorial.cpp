#include <iostream>

// Iterative
size_t factorial1(size_t n){
    size_t factorial {1};

    if (n < 0)
        std::cout << "Error! Factorial of a negative number doesn't exist.";
    else {
        for(int i = 1; i <= n; ++i) {
            factorial *= i;
        }
         
    }

    return factorial;
}

// Recursive
size_t factorial2(size_t n) {
    return (n < 2) ? 1 : n * factorial2(n - 1);
}


// Elegant Way
template<size_t n>
struct Fact {
	static const size_t value{ n > 1 ? n * Fact<n - 1>::value : 1};
};

template<>
struct Fact<0> {
	static const size_t value{ 1 };
};

int main()
{
    std::cout << factorial1(5) << "\n";
    std::cout << factorial2(5) << "\n";
	std::cout << Fact<5>::value << "\n";
}