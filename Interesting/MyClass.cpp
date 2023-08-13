#include "MyClass.h"

unsigned char MyClass::s_buffer[MyClass::max_no_of_dynamic_object * sizeof(MyClass)]{};
bool MyClass::s_flags[MyClass::max_no_of_dynamic_object]{};

void* MyClass::operator new(std::size_t n){
    auto iter = std::find(std::begin(s_flags), std::end(s_flags), false);
    if (iter == std::end(s_flags))
        throw std::bad_alloc{};

    auto idx = iter - std::begin(s_flags);

    s_flags[idx] = true;

    return s_buffer + sizeof(MyClass) * idx;
}

void MyClass::operator delete(void *vp){
    if (!vp)
        return;

    auto idx = (static_cast<unsigned char *>(vp) - s_buffer) / sizeof(MyClass);
    s_flags[idx] = false;
    
}

bool MyClass::is_there_space() const
{
    return std::any_of(std::begin(s_flags), std::end(s_flags),  [](auto b){return !b;});
}
std::size_t MyClass::space_count() const
{
    return static_cast<size_t>(std::count_if(std::begin(s_flags), std::end(s_flags), [](auto b){return !b;}));
}

