#pragma once
#include <ostream>

template<typename T>
class OstreamIterator{
public:
    OstreamIterator(std::ostream& os, const char* p = " "): m_os{os}, m_p{p}{}
    OstreamIterator& operator++(){ return *this; }
    OstreamIterator& operator++(int){ return *this; }
    OstreamIterator& operator*(){ return *this; }
    OstreamIterator& operator=(const T& x){ 
        m_os << x << m_p;
        return *this; 
    }
private:
    std::ostream& m_os;
    const char* m_p;
};