#pragma once

#include <deque>
#include <cstdlib>
#include <stdexcept>
#include <utility>

template<typename T, typename C = std::deque<T>>
class Stack{
public:
    Stack() = default;
    explicit Stack(const C& dq) : c(dq){}
    explicit Stack(C&& ct) : c(std::move(ct)) {}

    template <typename InputIt>
    Stack(InputIt first, InputIt last) : c(first, last) {}

    Stack(const Stack& other) : c(other.c) {}
    Stack(Stack&& other) noexcept : c(std::move(other.c)) {}
    
    /*
    !TODO: Implement Constructor to adjust Allocator
    
    template <class Alloc>
    explicit Stack(const Alloc &alloc);
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

    T& top(){
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.back();
    }
    const T& top()const{
        if(c.empty())
            throw std::runtime_error{"Container is empty!"};

        return c.back();
    }

    void pop(){
        c.pop_back();
    }

    std::size_t size()const{
        return c.size();
    }

    [[nodiscard]] bool is_empty()const{
        return c.empty();
    }

protected:
    C c;
};