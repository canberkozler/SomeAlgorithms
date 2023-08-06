#pragma once

#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <type_traits>
#include <functional>
#include <algorithm>

template<typename T, typename C = std::vector<T>, typename Comp = std::less<T>>
class Priority_Queue{
public:
    Priority_Queue() = default;
    ~Priority_Queue()= default;

    explicit Priority_Queue(const C& dq) : c(dq){ std::make_heap(c.begin(),c.end(), Comp{}); }
    explicit Priority_Queue(C &&ct) : c(std::move(ct)) { std::make_heap(c.begin(), c.end(), Comp{}); }

    template <typename InputIt>
    Priority_Queue(InputIt first, InputIt last) : c(first, last) { std::make_heap(c.begin(), c.end(), Comp{}); }

    Priority_Queue(const Priority_Queue &other) : c(other.c) { std::make_heap(c.begin(), c.end(), Comp{}); }
    Priority_Queue& operator=(const Priority_Queue& other){
        // no need to check for self-assignment (other than performance)
        auto tmp = other;
        std::swap(*this, tmp);
        std::make_heap(c.begin(), c.end(), Comp{});
        return *this;
    }

    Priority_Queue(Priority_Queue &&other) noexcept : c(std::move(other.c)) { std::make_heap(c.begin(), c.end(), Comp{}); }
    Priority_Queue& operator=(Priority_Queue&& other){
        if(this == &other) 
            return *this;

        c = std::move(other.c);
        std::make_heap(c.begin(), c.end(), Comp{});
        return *this;
    }

    /*
    !TODO: Implement Constructors to adjust Allocator
    
    template <class Alloc>
    explicit Priority_Queue(const Alloc &alloc);
    */
    
    void push(const T& t){
        c.push_back(t);
        std::make_heap(c.begin(), c.end(), Comp{});
    }
    void push(T&& t){
        c.push_back(std::move(t));
        std::make_heap(c.begin(), c.end(), Comp{});
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        c.emplace_back(std::forward<Args>(args)...);
        std::make_heap(c.begin(), c.end(), Comp{});
    }

    T& top(){
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.front();
    }
    const T& top()const{
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.front();
    }

    void pop(){
        std::pop_heap(c.begin(), c.end(), Comp{});
        c.pop_back();
    }

    C get_container_sorted()const{
        auto temp = c;
        std::sort_heap(temp.begin(), temp.end(), Comp{});

        return temp;
    }

    const C& get_container()const{
        return c;
    }
    C& get_container(){
        return c;
    }

    typename C::size_type size()const{
        return c.size();
    }

    [[nodiscard]] bool is_empty()const{
        return c.empty();
    }

    void swap(Priority_Queue& other) noexcept(std::is_nothrow_swappable_v<C>) // noexcept(noexcept(swap(c, other.c))) // until c++17
    {
        using std::swap;
        swap(c, other.c);
    }

    bool operator<(const Priority_Queue& other)const{
        return c < other.c;
    }
    bool operator>(const Priority_Queue& other)const{
        return c > other.c;
    }

    friend bool operator<=(const Priority_Queue& lh,const Priority_Queue& rh){
        return !(lh > rh);
    }
    friend bool operator>=(const Priority_Queue& lh,const Priority_Queue& rh){
        return !(lh < rh);
    }

    bool operator==(const Priority_Queue& other) const {
        return c == other.c;
    }

    friend bool operator!=(const Priority_Queue& lh,const Priority_Queue& rh){
        return !(lh == rh);
    }

    bool operator!() const {
        return is_empty();
    }

protected:
    C c;
};