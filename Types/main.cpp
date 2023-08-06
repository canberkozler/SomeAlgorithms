#include "pair.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "date.hpp"
#include "AbstractDataTypes/stack.hpp"
#include "AbstractDataTypes/queue.hpp"
#include "AbstractDataTypes/priority_queue.hpp"
#include <random>

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
    std::cout <<"\n--------- Stack ----------\n\n";
    Stack<int> istack;
    int i{15};
    istack.emplace(22);
    istack.push(i);

    std::cout<<istack.top()<<"\n";

    istack.pop();

    std::cout<<istack.top()<<"\n";

    std::cout<<std::boolalpha << istack.is_empty() << "\n";

    // Queue
    std::cout <<"\n--------- Queue ----------\n\n";
    Queue<double> dque;    

    dque.push(5.1);
    dque.push(22.3);
    dque.push(52.2);
    dque.push(13.6);

    std::cout<< "dque is empty: " << (!dque)<<"\n";
    std::cout<< "dque is empty: " << (dque.is_empty())<<"\n";

    std::cout<< "Queue Size: " << dque.size()<<"\n"
             << "First Elem in Queue: " <<dque.front()<<"\n"
             << "Last Elem in Queue: " <<dque.back()<<"\n";

    dque.pop();
    std::cout<< "Last Elem in Queue: " <<dque.back()<<"\n";

    std::deque<double> d{124567.7, 88322.5, 23462.0};
    Queue<double> tmp_dq(d);
    std::cout<< "dque is equals to tmp_dq: " << (dque == tmp_dq)<<"\n";
    
    dque.swap(tmp_dq);
    std::cout<< "\nAfter Queue swap:\n";
    while(!dque.is_empty()){
        std::cout<< dque.back()<<"\n";
        dque.pop();
    }

    // Priority Queue
    std::cout <<"\n--------- Priority Queue ----------\n\n";
    std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<int> dist;

    Priority_Queue<long> max_que;
	for (int i = 0; i < 20; ++i)
		max_que.push(dist(eng) % 10000);

    std::cout <<"Before pop max elem:\n";
    for (auto lval: max_que.get_container())
		std::cout << lval << " ";
    std::cout <<"\n";

    std::cout<< "Max Elem: " << max_que.top()<<"\n";

    max_que.pop();

    std::cout <<"After pop max elem:\n";
    for (auto lval: max_que.get_container())
		std::cout << lval << " ";
    std::cout <<"\n\n";

    std::cout <<"Sort Container:\n";
    for (auto lval: max_que.get_container_sorted())
		std::cout << lval << " ";
}