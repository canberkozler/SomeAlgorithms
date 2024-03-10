#include <iostream>

int the_greatest_common_divisor(int x, int y){
    if(x == 0 || y == 0){
        return (x == 0) ? y : x;
    }

    int powof2{};
    for(; ((x|y)&1) == 0; ++powof2){
        x >>=1;
        y >>=1;
    }

    while((x & 1) == 0){
        x>>=1;
    }
    if (y != 0)
    {
        while ((y & 1) == 0)
        {
            y >>= 1;
        }

        if(x>y) std::swap(x,y);

        y -= x;
    }

    return x << powof2;
}

int main() {
	std::cout << the_greatest_common_divisor(258, 321)<<"\n";
}