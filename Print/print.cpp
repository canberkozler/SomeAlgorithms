#include<iostream>
#include<vector>
#include<string>

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

int main(){
    std::vector<std::pair<std::string, int>> myvec{ {"ali", 23}, {"can", 22}, {"berk", 13}};
    print(myvec.begin(), myvec.end(),"\n");
}