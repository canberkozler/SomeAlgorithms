#include<iostream>
#include<vector>
#include<string>
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
}