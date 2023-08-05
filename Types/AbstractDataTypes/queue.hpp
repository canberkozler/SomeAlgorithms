#pragma once

#include <deque>
#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <type_traits>

template<typename T, typename C = std::deque<T>>
class Queue{
public:
    Queue() = default;
    ~Queue()= default;\

    explicit Queue(const C& dq) : c(dq){}
    explicit Queue(C&& ct) : c(std::move(ct)) {}

    template <typename InputIt>
    Queue(InputIt first, InputIt last) : c(first, last) {}

    Queue(const Queue& other) : c(other.c) {}
    Queue& operator=(const Queue& other){
        // no need to check for self-assignment (other than performance)
        auto tmp = other;
        std::swap(*this, tmp);
        return *this;
    }

    Queue(Queue&& other) noexcept : c(std::move(other.c)) {}
    Queue& operator=(Queue&& other){
        if(this == &other) 
            return *this;

        c = std::move(other.c);
        return *this;
    }

    /*
    !TODO: Implement Constructors to adjust Allocator
    
    template <class Alloc>
    explicit Queue(const Alloc &alloc);
    */
    
    void push(const T& t){
        c.push_back(t);
    }
    void push(T&& t){
        c.push_back(std::move(t));
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        c.emplace_back(std::forward<Args>(args)...);
    }

    T& back(){
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.back();
    }
    const T& back()const{
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.back();
    }

    T& front(){
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.front();
    }
    const T& front()const{
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.front();
    }

    void pop(){
        c.pop_back();
    }

    typename C::size_type size()const{
        return c.size();
    }

    [[nodiscard]] bool is_empty()const{
        return c.empty();
    }

    void swap(Queue& other) noexcept(std::is_nothrow_swappable_v<C>) // noexcept(noexcept(swap(c, other.c))) // until c++17
    {
        using std::swap;
        swap(c, other.c);
    }

protected:
    C c;
};