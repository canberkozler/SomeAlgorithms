#pragma once
#include <iostream>

template<int n>
class Count: Count<n-1>{
public:
    Count(){std::cout<< n <<" ";}
};

template<>
class Count<0>{};
