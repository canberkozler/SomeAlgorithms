#include "2DTransformations.hpp"

int main(){
    Data dt(1.0,0.0);
    double theta{3.14/6.0};
    std::cout << rotate_clockwise2D(dt, theta);
}