#pragma once

#include <iostream>
using namespace std;
template<class ...Args>
inline auto sum(Args... args) // GOOD, and much more flexible
{
    return (... + args); // note: C++17 "fold expression"
}
