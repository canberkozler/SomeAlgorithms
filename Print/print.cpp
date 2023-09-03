#include<vector>
#include<string>
#include<iterator>
#include<algorithm>

#include "print.hpp"
#include"spaceDeleter.h"

int main(){
    {
        std::vector<std::pair<std::string, int>> myvec{{"ali", 23}, {"can", 22}, {"berk", 13}};
        print(myvec.begin(), myvec.end(), "\n");
    }

    // { // TODO: fix locale err.
    //     std::ostream os{std::cout.rdbuf()};
    //     os.imbue(std::locale{""});
    //     os<<87555111;
    // }

    {
        std::string str;
        std::cout<<"Type a sentence.\n";
        getline(std::cin, str);
        std::cout<<"| " << str <<" |\n";
        extra_space_deleter(str);
        std::cout<<"| " << str <<" |\n";
    }

    {
        "Hi, Github!"_print;

        88.9_print;
    }

    std::cout << "Apply double new line..."<<double_new_line;
    {
        std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
        println("The vector contains: ", ivec);
    }

    { // Using STL algorithm to print.
        std::vector<int> ivec{34, 2, 10, -9, 22, 356, 124, 89, -98, -23, 56};

        std::ostream_iterator<int> outputIter{std::cout, " "};
        std::cout << "Using std::copy to print: ";
        std::copy(ivec.begin(), ivec.end(), outputIter);
        std::cout <<'\n';

        std::cout << "Using std::transform to print: ";
        std::transform(ivec.begin(), ivec.end(), outputIter, [](auto elem)
                       { return elem; });
        std::cout <<'\n';

        std::cout << "Using std::generate_n to print: ";
        std::generate_n(outputIter, ivec.size(),
                        [&ivec](){
                            static size_t index = 0;
                            return ivec[index++];
                        });
        std::cout <<'\n';
    }

    { // print forwards and backwards.
        print_args_backwards(1,2,"hello",4,5,"Github!");
    }
}