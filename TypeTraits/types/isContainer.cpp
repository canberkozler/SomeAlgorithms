#include <iostream>
#include <vector>
#include <list>
#include <type_traits>

template <typename T>
struct IsContainer {
private:
    template <typename U>
    static std::true_type test(decltype(std::declval<U>().begin())*);
    
    template <typename U>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

// Version 2
template <typename T, typename = void>
struct IsContainer2 : std::false_type {};

template <typename T>
struct IsContainer2<T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {};

template <typename T>
constexpr bool IsContainer2_v = IsContainer2<T>::value;

int main() {
    std::vector<int> vec = {5, 2, 9, 1, 5};
    std::list<double> lst = {3.14, 1.41, 2.71, 0.577};
    int num = 42;

    std::cout<<"\nIsContainer:\n";
    if (IsContainer<decltype(vec)>::value) {
        std::cout << "vec is a container.\n";
    } else {
        std::cout << "vec is not a container.\n";
    }

    if (IsContainer<decltype(num)>::value) {
        std::cout << "num is a container.\n";
    } else {
        std::cout << "num is not a container.\n";
    }

    std::cout<<"\nIsContainer2:\n";

    if (IsContainer2_v<decltype(lst)>) {
        std::cout << "lst is a container.\n";
    } else {
        std::cout << "lst is not a container.\n";
    }

    if (IsContainer2_v<decltype(num)>) {
        std::cout << "num is a container.\n";
    } else {
        std::cout << "num is not a container.\n";
    }

    return 0;
}