#pragma once
template<typename T, int n>
constexpr int Size(const T(&)[n]){ // sizeof(a)/sizeof(*a); // More elegant
    return n;
}