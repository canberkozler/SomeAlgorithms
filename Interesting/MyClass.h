#pragma once
#include <cstddef>
#include <algorithm>
#include <iterator>

class MyClass{
public:
    static constexpr std::size_t buffer_size = 1024;
    static constexpr std::size_t max_no_of_dynamic_object = 100;
    void* operator new(std::size_t n);

    void operator delete(void* vp);

    bool is_there_space()const;
    std::size_t space_count()const;
private:
    unsigned char m_buff[MyClass::buffer_size];
    static unsigned char s_buffer[];
    static bool s_flags[];
};
