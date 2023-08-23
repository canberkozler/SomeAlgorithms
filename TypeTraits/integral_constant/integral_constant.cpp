#include <type_traits>
#include <iostream>
#include <type_traits>

// Implementation of integral_constant
template<class T, T v>
struct Integral_Constant {
    static constexpr T value = v;
    using value_type = T;
    using type = Integral_Constant; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; } // C++14
};

using True_Type = Integral_Constant<bool, true>;
using False_Type = Integral_Constant<bool, false>;

template <bool B>
using Bool_Constant = Integral_Constant<bool, B>;  //C++ 17

// Implementation of is_const
template<typename T> 
struct Is_Const : True_Type{};

template<typename T> 
struct Is_Const<const T> : False_Type{};

// Helper variable template
template <typename T>
inline constexpr bool Is_Const_v = Is_Const<T>::value;

// Implementation of is_same
template <typename T, typename U>
struct Is_Same : True_Type{};

template <typename T>
struct Is_Same<T, T> : False_Type{};

// Helper variable template
template <typename T, typename U>
inline constexpr bool Is_Same_v = Is_Same<T, U>::value;

int main()
{
    std::cout << std::boolalpha;
	
	using itype = int;
	std::cout << std::is_const<itype>::value << '\n'; 

	using ValueType = std::is_const<itype>::value_type;	
	using Type = std::is_const<itype>::type;				
	
	std::cout << std::is_same<ValueType, bool>::value << '\n'; 
	std::cout << std::is_same<Type, std::integral_constant<bool, false>>::value << '\n'; 
	std::cout << std::is_same<Type, std::bool_constant<false>>::value << '\n'; 
	constexpr auto ic = std::is_const<itype>(); 
	std::cout << std::is_same<decltype(ic), std::is_const<int>>::value << '\n'; 	
	std::cout << ic() << '\n'; 
	
	static constexpr auto mytypeIsConst = std::is_const<itype>{};
	
	if constexpr (mytypeIsConst) {} 
	static_assert(!std::is_const<itype>{}, "itype const olmamali");
	constexpr auto val = std::integral_constant<int, 5>{} + std::integral_constant<int, 3>{};

    constexpr std::integral_constant<int, 5> x;
	constexpr std::integral_constant<int, 2> y;

	constexpr auto val2 = x + y + x() + y(); //val ==> 14
}