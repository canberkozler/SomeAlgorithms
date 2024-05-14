#include <iostream>

#define ATTEMPT5 1

#ifdef ATTEMPT1
    #include "attempt1.h"
#elif ATTEMPT2 
    #include "attempt2.h"

#elif ATTEMPT3
    #include "attempt3.h"

#elif ATTEMPT4
    #include "attempt4.h"

#elif ATTEMPT5
    #include "attempt5.h"

#elif ATTEMPT6
    #include "attempt6.h"
#else
#endif

int main(){

#ifdef ATTEMPT1
    std::cout << "Attempt1!!\n";
    infinite_loop(1);
#elif ATTEMPT2 // fatal error: template instantiation depth exceeds maximum of 900 (use '-ftemplate-depth=' to increase the maximum)
    std::cout << "Attempt2!!\n";
    Infinite1<0> A{};
    std::cout << A.value;

#elif ATTEMPT3 // fatal error: template instantiation depth exceeds maximum of 900 (use '-ftemplate-depth=' to increase the maximum)
    std::cout << "Attempt3!!\n";
    Infinite2<1> A{};
    std::cout << A.value;

#elif ATTEMPT4 // fatal error: template instantiation depth exceeds maximum of 900 (use '-ftemplate-depth=' to increase the maximum)
    std::cout << "Attempt4!!\n";
    Infinite3<100> A{};
    std::cout << A.value;

#elif ATTEMPT5 // fatal error: template instantiation depth exceeds maximum of 900 (use '-ftemplate-depth=' to increase the maximum)
    std::cout << "Attempt5!!\n";
    Infinite4<int> A{};
    std::cout << A.value() << "\n";

#elif ATTEMPT6 // fatal error: template instantiation depth exceeds maximum of 900 (use '-ftemplate-depth=' to increase the maximum)
    std::cout << "Attempt6!!\n";
    Infinite5<int> A{};
    std::cout << A.value << "\n";
#else
    std::cout << "There is no freaky way!!\n";
#endif

}