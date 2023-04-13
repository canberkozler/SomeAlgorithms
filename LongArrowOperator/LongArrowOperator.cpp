#include <iostream>

// void func(const char *= "Error");
// Syntax error because of Maximal Munch Rule. To solve this write code as below
void func(const char* = "Error");

// alias template but template parameter is non-type parameter
template <int>
using Int = int;

// void foo(Int<5>= 0);
// Syntax error because of Maximal Munch Rule. To solve this write code as below
void foo(Int<5> = 0);

int main(){
    int n{3};
    while(n --> 0){ //Maximal Munch Rule (-- >)
        std::cout<<"Just kidding. There is no Long Arrow Operator in C++.\n";
    }

    int x{20}, y{30};
    int c = x+++y;
    // Thanks to Maximal Munch Rule, Compiler writes as x++ + y.

    std::cout<< x <<" "<< y <<" "<<c; // 21 30 50

    int a{20}, b{30}, *p{&b};

    // x= x /*p; 
    // Syntax error because of Maximal Munch Rule. To solve this write code as below
    x = x / *p;
}