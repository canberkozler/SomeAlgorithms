#include <iostream>
#include <cmath>

float fastInverseSquareRoot(float number) {
    float x = number * 0.5f;
    float y = number;
    int32_t i = *(reinterpret_cast<int32_t*>(&y));
    i = 0x5f3759df - (i >> 1);
    y = *(reinterpret_cast<float*>(&i));
    y = y * (1.5f - (x * y * y));
    return y;
}

int main() {
    float number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    float result = fastInverseSquareRoot(number);
    std::cout << "Inverse square root: " << result << std::endl;
    return 0;
}