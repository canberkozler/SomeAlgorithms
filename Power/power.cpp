#include <iostream>

template <size_t base, size_t exp>
struct Power {
	constexpr static size_t value = base * Power<base, exp - 1>::value;
};

template <size_t base>
struct Power<base, 0u> {
	constexpr static size_t value = 1;
};


int main()
{
	constexpr auto val = Power<5, 4>::value;
    std::cout<<val << '\n';
}