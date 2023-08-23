#pragma once

#include <iostream>
using namespace std;
template<class ...Args>
inline auto sum(Args... args) // GOOD, and much more flexible
{
    return (... + args); // note: C++17 "fold expression"
}

template<typename T>
inline T summer(T u){
    return u;
}
template<typename T, typename ...Args>
inline T summer(const T& fs, Args... args){
    return fs + summer(args...);
}

template<int n>
class sequential_number_summer{
public:
    int get() const{
        return value;
    }
    constexpr static int value = n+sequential_number_summer<n-1>::value;

    friend std::ostream& operator<<(std::ostream& os, const sequential_number_summer& s){
        return os<<"[ "<<s.get()<<" ]\n";
    }
};

template<>
class sequential_number_summer<0>{
public:
    constexpr static int value = 0;
};

