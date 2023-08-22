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