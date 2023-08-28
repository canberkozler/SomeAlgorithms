#include <type_traits>
#include <iostream>

template <typename T>
struct isNullPointer : std::is_same<std::nullptr_t, std::remove_cv_t<T>> {};

template <typename T>
constexpr bool isNullPointer_v = isNullPointer<T>::value;

int main(){
    std::cout << std::boolalpha << isNullPointer_v<decltype(nullptr)> << "\n" // true
              << isNullPointer_v<int*>; //false
}