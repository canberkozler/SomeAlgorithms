#pragma once
#include <iostream>
#include <utility>
#include <string_view>
#include <type_traits>


template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p){
    return os << "[ " << p.first << ", " << p.second << " ]";
}

template<typename C>
void print(const C& c, const char* p = " ", std::ostream& os = std::cout){
    for(const auto& elem : c)
        os<<elem<<p;
    
    os<<'\n';
}

template<typename InIter>
void print(InIter beg, InIter end, const char* p = " ", std::ostream& os = std::cout){
    while(beg != end)
        os<< *beg++ <<p;
    
    os<< '\n';
}

// User defined literal
void operator"" _print(const char* str, std::size_t size)
{
    std::cout << str << '\n';
}

// User defined literal
void operator"" _print(long double ld)
{
    std::cout << ld << '\n';
}

// Manipulator
std::ostream& double_new_line(std::ostream& os){
    return os << "\n\n";
}

template<typename C>
void println(std::string_view rem, const C& v){
    std::cout << rem;
    if constexpr (std::is_scalar<std::decay_t<decltype(v)>>::value)
        std::cout << v;
    else
        for (auto e : v)
            std::cout << e << ' ';
    std::cout << '\n';
}

template<class... Ts> 
void print_args_backwards(Ts... ts){
    auto print_one = [](auto t){
        std::cout << t << '\n';
        // Anything with a reasonable assignment operator will work here.
        return std::type_identity<void>{}; // released in C++20.
    };

    std::cout << "---Backwards---\n";
    (print_one(ts) = ...);
    /*
        auto fold_print_assign_right = [&auto... vals]{
            (print_one(vals) = ...);
        }
        fold_print_assign_right(1,2,3); ===> print(1) = (print(2) = print(3));

        Output:
        3
        2
        1

        ------------------------------------------------------------
        auto fold_print_assign_right = [&auto... vals]{
            (... = print_one(vals));
        }
        fold_print_assign_right(1,2,3); ===>( print(1) = print(2)) = print(3);

        Again, output:
        3
        2
        1
    */
    std::cout << "---Forwards---\n";
    (print_one(ts), ...);
    /*
        auto fold_print_comma_right = [&auto... vals]{
            (print_one(vals), ...);
        }
        fold_print_comma_right(1,2,3); ===> print(1), (print(2), print(3));

        Output:
        1
        2
        3

        ------------------------------------------------------------
        auto fold_print_comma_right = [&auto... vals]{
            (..., print_one(vals));
        }
        fold_print_comma_right(1,2,3); ===>( print(1), print(2)), print(3);

        Again, output:
        1
        2
        3
    */
}

template<typename T, typename... Args>
void enumerate_and_print(T f, Args... args){ //void enumerate_pack(auto f, auto... args); c++20
    [&]<std::size_t... Idxs>(std::index_sequence<Idxs...>){
        (f(Idxs, args), ...);
    }(std::make_index_sequence<sizeof...(args)>{});
}
