#include<iostream>
#include<vector>
#include<string>
#include<string_view>
#include<iterator>

#include"spaceDeleter.h"

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p){
    return os << "[ " << p.first << ", " << p.second << " ]";
}

template<typename C>
void print(const C& c, const char* p = " ", std::ostream& os = std::cout){
    for(const auto& elem : c)
        os<<elem<<p;
    
    os<<'\n';
}

template<typename InIter>
void print(InIter beg, InIter end, const char* p = " ", std::ostream& os = std::cout){
    while(beg != end)
        os<< *beg++ <<p;
    
    os<< '\n';
}

// User defined literal
void operator"" _print(const char* str, std::size_t size)
{
    std::cout << str << '\n';
}

// User defined literal
void operator"" _print(long double ld)
{
    std::cout << ld << '\n';
}

// Manipulator
std::ostream& double_new_line(std::ostream& os){
    return os << "\n\n";
}

template<typename C>
void println(std::string_view rem, const C& v){
    std::cout << rem;
    if constexpr (std::is_scalar<std::decay_t<decltype(v)>>::value)
        std::cout << v;
    else
        for (auto e : v)
            std::cout << e << ' ';
    std::cout << '\n';
}

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
}