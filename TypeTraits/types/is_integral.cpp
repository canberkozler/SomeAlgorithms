#include <type_traits>
#include <iostream>

template<typename> struct is_integral_base : std::false_type {};

template<> struct is_integral_base<bool> : std::true_type {};
template<> struct is_integral_base<int> : std::true_type {};
template<> struct is_integral_base<short> : std::true_type {};

template<typename T> 
struct isIntegral : is_integral_base<std::remove_cv_t<T>> {};

int main(){
    using Type = int;
    std::cout << std::boolalpha << isIntegral<Type>::value <<"\n" // true
              << isIntegral<const bool>::value <<"\n" // true
              << isIntegral<double>::value; // false
}