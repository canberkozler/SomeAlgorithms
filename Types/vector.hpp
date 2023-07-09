#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cstddef>
#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Vector {
public:
    Vector() = default;
    explicit Vector(std::size_t n) : n{n}, elements(n) {}
    explicit Vector(std::initializer_list<T> values) : elements(values) {}

    T& operator()(std::size_t index) {
            return elements[index];
        }

    const T& operator()(std::size_t index) const {
        return elements[index];
    }

    T& operator[](std::size_t index) {
        return elements[index];
    }

    const T& operator[](std::size_t index) const {
        return elements[index];
    }

    constexpr std::size_t size() const {
        return elements.size();
    }

    // Vector addition
    Vector &operator+=(const Vector &other){
        if (n != other.size())
            throw std::runtime_error{"Unmatched size."};

        for (std::size_t i{}; i < size(); ++i){
            (*this)(i) += other(i);
        }
        return *this;
    }

    template<typename U>
    friend Vector<U> operator+(Vector<U> lhand, const Vector<U>& rhand){
        return lhand += rhand;
    }

    // Vector substraction
    Vector &operator-=(const Vector &other){
        if (n != other.size())
            throw std::runtime_error{"Unmatched size."};

        for (std::size_t i{}; i < size(); ++i){
            (*this)(i) -= other(i);
        }
        return *this;
    }

    template<typename U>
    friend Vector<U> operator-(Vector<U> lhand, const Vector<U>& rhand){
        return lhand -= rhand;
    }

    // Output stream operator for Matrix
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Vector<U> &vec){
        for (const auto &elem : vec.elements){
            os << elem << '\n';
        }
        return os;
    }

private:
    std::size_t n;
    std::vector<T> elements;
};


#endif