#include <type_traits>
#include <iostream>

// Version 0

// template <typename T>
// struct isVoid : std::false_type {};

// template<> struct isVoid<void> : std::true_type{};
// template<> struct isVoid<const void> : std::true_type{};
// template<> struct isVoid<volatile void> : std::true_type{};
// template<> struct isVoid<const volatile void> : std::true_type{};

template <typename T>
struct isVoid : std::is_same<void, typename std::remove_cv<T>::type> {};

template <typename T>
constexpr bool isVoid_v = isVoid<T>::value;

int main()
{
	std::cout << std::boolalpha;
	std::cout << isVoid_v<int> << "\n"; //false
	std::cout << isVoid_v<void> << "\n"; //true
	std::cout << isVoid_v<const void> << "\n";//true
	std::cout << isVoid_v<void *> << "\n"; //false
	std::cout << isVoid_v<void const volatile> << "\n";//true
}