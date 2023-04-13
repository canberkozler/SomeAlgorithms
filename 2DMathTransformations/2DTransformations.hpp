#ifndef TWO_DIMENSIONAL_TRANSFORMATIONS
#define TWO_DIMENSIONAL_TRANSFORMATIONS
#include <cmath>
#include <iostream>

template<typename T>
struct Data{
    Data() = default;
    Data(T x_,T y_) : x(x_), y(y_) {}
    T x{}, y{};
    friend std::ostream& operator<<(std::ostream& os, const Data& dt)const{
        return os<< "[ "<< dt.x<<", " <<dt.y<< " ]\n";
    }
    friend std::istream& operator>>(std::istream& is, const Data& d){
        return is >> dt.x >> dt.y;
    }
};

template <typename Type>
inline decltype(auto) rotate_clockwise2D(Type pt, const double theta){
    auto temp = pt;
    pt.x = (temp.x) * std::cos(theta) - (temp.y) * std::sin(theta);
    pt.y = (temp.y) * std::cos(theta) + (temp.x) * std::sin(theta);
    return pt;
}

#endif