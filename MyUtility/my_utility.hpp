#pragma once

#include <random>
#include <string>
#include <iostream>
#include <set>
#include <forward_list>

#define getValueCat(s) std::cout << "Value category of '" << #s << "' is " << Value_Category_Detector<decltype((s))>::p << "\n";

class Irand {
public:
	Irand() = default;
	Irand(int min, int max) : m_dist{ min, max } {}
	int operator()();
private:
	std::uniform_int_distribution<int> m_dist;
};

class Drand {
public:
	Drand() = default;
	Drand(double dmin, double dmax) : m_dist{ dmin, dmax } {}
    double operator()();

private:
	std::uniform_real_distribution<double> m_dist;
};

void randomize();

[[nodiscard]] std::string rname();
[[nodiscard]] std::string rfname();
[[nodiscard]] std::string rtown();
[[nodiscard]] std::string rperson();

std::ostream& dline(std::ostream& os);

constexpr int ndigit(int val)
{
	if (val == 0)
		return 1;

	int digit_count = 0;

	while (val != 0) {
		val /= 10;
		++digit_count;
	}

	return digit_count;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
{
	return os << "[" << p.first << ", " << p.second << "]";
}

template<typename C, typename F>
void rfill(C& c, size_t n, F frand)
{
	while (c.size() < n)
		c.insert(c.end(), frand());
}

template<typename T, typename F>
void rfill(std::forward_list<T>& c, size_t n, F frand)
{
	while (n--)
		c.insert_after(c.before_begin(), frand());
}

template<typename T, int n>
constexpr int Size(const T(&)[n]){ // sizeof(a)/sizeof(*a); // More elegant
    return n;
}

template<typename C>
void print(const C& c, const char* p = " ", std::ostream& os = std::cout)
{
	for (const auto& elem : c)
		os << elem << p;
	os << dline;
}

template<typename InIter>
void print(InIter beg, InIter end, const char* p = " ", std::ostream& os = std::cout)
{
	while (beg != end) {
		os << *beg++ << p;
	}
	os << dline;
}

template<typename T>
void variadic_print_v1(const T& t){
    std::cout << __PRETTY_FUNCTION__<<" => "; // Shows which function called.
    std::cout<< t<<"\n";
}

template<typename T, typename ...Args>
void variadic_print_v1(const T& t, Args... args){
    std::cout << __PRETTY_FUNCTION__<<" => "; // Shows which function called.
    std::cout<< t<<"\n";
    
    variadic_print_v1(args...);
}

#include<initializer_list>
// Comma operator return right handside value.
template<typename ...Types>
void variadic_print_v2(const Types& ...params){
    // int a[] = {(std::cout << params <<" ", 0)...}; 

    (void)std::initializer_list<int> {(std::cout << params <<" ", 0)...}; // Cast void to prevent warnings.
}

template<typename T, typename ... Args>
std::ostream& variadic_print_v3(std::ostream& os, const T& t, const Args& ...rest){
    os<<t;
    if constexpr(sizeof...(rest)>0){
        os<<", ";
    }
    else{
        os<<"\n";
    }
    if constexpr(sizeof...(rest)!= 0)
        variadic_print_v3(os, rest...);
    
    return os;
}

template<typename T>
struct Value_Category_Detector
{
	static constexpr const char* p = "Pr Value";
};

template<typename T>
struct Value_Category_Detector<T&>
{
	static constexpr const char* p = "L Value";
};

template<typename T>
struct Value_Category_Detector<T&&>
{
	static constexpr const char* p = "X Value";
};
