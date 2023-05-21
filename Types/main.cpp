#include "pair.hpp"
#include<iomanip>

int main(){
    auto x = MakePair(1.2,11);
    auto y{x};

    y.set(23.2,22);
    std::cout<<std::boolalpha;
    std::cout << x << y << "x < y: "<< (x<y) <<"\n" 
                        <<"x > y: "<< (x>y) <<"\n" 
                        <<"x >= y: "<< (x>=y) <<"\n" 
                        <<"x <= y: "<< (x<=y) <<"\n" 
                        <<"x != y: "<< (x!=y) <<"\n"
                        <<"x == y: "<< (x==y) <<"\n";

    auto z = x+y;
    std::cout << z;
}