#include <vector>
#include <type_traits>
#include <iostream>

template <typename T>
struct TypeIdentity {
	using type = T;
};

// Implementation of conditional.
template <bool Cond, typename T, typename U>
struct Conditional : TypeIdentity<T> {};

template <typename T, typename U>
struct Conditional<false, T, U> : TypeIdentity<U> {};

template< bool Cond, typename T, typename U >
using Conditional_t = typename conditional<B,T,U>::type;


// Usage of conditional.
template <typename T>
void func(T x)
{
	std::conditional_t<std::is_floating_point_v<T>, int, double> val{};
	std::cout << typeid(val).name() << "\n";
}

int main()
{
	func(20);
	func(2.3);

    using Type = std::conditional<sizeof(int) >= sizeof(double), int, double>::type; // => double
}