#include <type_traits>
#include <iostream>

template <typename T>
struct isPointer_helper : std::false_type{};

template <typename T>
struct isPointer_helper<T *> : std::true_type{};

template <typename T>
struct isPointer : isPointer_helper<typename std::remove_cv<T>::type>{};

template <typename T>
inline constexpr bool isPointer_v = isPointer<T>::value;

int main(){
    std::cout << std::boolalpha << isPointer_v<int> <<"\n" // false
              << isPointer_v<double*>; // true
}