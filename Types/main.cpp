#include "pair.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "date.hpp"
#include "AbstractDataTypes/stack.hpp"


int main(){
    // Pair
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
    std::cout<<"\n\n";

    // Matrix
    Matrix<double> A(2, 2);
    A[0][0] = 1.0;
    A[0][1] = 2.0;
    A[1][0] = 3.0;
    A[1][1] = 4.0;

    Matrix<double> B(2, 2);
    B(0, 0) = 5.0;
    B(0, 1) = 6.0;
    B(1, 0) = 7.0;
    B(1, 1) = 8.0;

    Matrix<double> C = A + B;
    std::cout << "C:\n" << C << '\n';

    Matrix<double> D = A * B;
    std::cout << "D:\n" << D << '\n';
    std::cout << "D * 10:\n" << D*10 << '\n';
    std::cout << "Transpose of D:\n" << D.transpose() << '\n';
    // std::cout << "Inverse of D:\n" << D.inverse() << '\n';

    // Vector
    Vector<double> V_A(3);
    V_A(0) = 2.0;
    V_A(1) = 4.0;
    V_A(2) = 3.0;

    Vector<double> V_B(3);
    V_B(0) = 5.0;
    V_B(1) = 2.0;
    V_B(2) = 6.0;

    std::cout<< "V_A + V_B:\n"<<V_A+V_B<<"\n";
    std::cout<< "V_A - V_B:\n"<<V_A-V_B<<"\n";

    //Date
    Date date{23, 12, 2021};
    Date date2{Date::random()};

    std::cout<<date<<'\n'<<date2<<"\nThe difference in the number of days between 2 dates: "<<date-date2<<'\n';

    //***** ABSTRACT DATA TYPES *****//
    // Stack
    Stack<int> istack;
    int i{15};
    istack.emplace(22);
    istack.push(i);

    std::cout<<istack.top()<<"\n";

    istack.pop();

    std::cout<<istack.top()<<"\n";

    std::cout<<std::boolalpha << istack.is_empty();
}