#ifndef PAIR_HPP
#define PAIR_HPP
#include<utility>
#include<iostream>

template<typename T, typename U>
struct Pair{
    Pair()=default;
    Pair(const T& t, const U& u): first{t}, second{u}{}

    // copy ctor
    template<typename K, typename L>
    Pair(const Pair<K,L>& other) : first{other.first}, second{other.second}{} 

    // copy assignment
    template<typename K, typename L>
    Pair& operator=(const Pair<K,L>& other){
        if(&other == this) // self assingment
            return *this;
        
        first = other.first;
        second = other.second;

        return *this;
    }

    // move ctor
    template<typename K, typename L>
    Pair(Pair<K,L>&& other) : first{std::move(other.first)}, second{std::move(other.second)}{} 
    
    // move assignment
    template<typename K, typename L>
    Pair& operator=(Pair<K,L>&& other){
        if(&other == this) // self assingment
            return *this;
        
        first = std::move(other.first);
        second = std::move(other.second);

        return *this;
    }

    template<typename W, typename Z>
    friend std::ostream& operator<<(std::ostream& os, const Pair<W,Z>& p){
        return os << "(" << p.first << ", " << p.second << ")\n";
    }

    template<typename W, typename Z>
    friend std::istream& operator>>(std::istream& is, Pair<W,Z>& p){
        return is>>p.first>>p.second;
    }
    
    void set(const T& f, const U& s){
        first = f;
        second = s;
    }

    template<typename F, typename S>
    friend bool operator<(const Pair<F,S>& lhand, const Pair<F,S>& rhand);

    template<typename F, typename S>
    friend bool operator>(const Pair<F,S>& lhand, const Pair<F,S>& rhand);

    template<typename F, typename S>
    friend bool operator>=(const Pair<F,S>& lhand, const Pair<F,S>& rhand);

    template<typename F, typename S>
    friend bool operator<=(const Pair<F,S>& lhand, const Pair<F,S>& rhand);

    template<typename F, typename S>
    friend bool operator==(const Pair<F,S>& lhand, const Pair<F,S>& rhand);

    template<typename F, typename S>
    friend bool operator!=(const Pair<F,S>& lhand, const Pair<F,S>& rhand);

    Pair& operator+=(const Pair& rhand){
        first += rhand.first;
        second += rhand.second;
        return *this;
    }

    template<typename F, typename S>
    friend Pair<F,S> operator+(Pair<F,S>, const Pair<F,S>&);

    T first{};
    U second{};
};

template<typename F, typename S>
bool operator<(const Pair<F,S>& lhand, const Pair<F,S>& rhand){
    return (lhand.first < rhand.first) || !(rhand.first < lhand.first) && (lhand.second < rhand.second);
}

template<typename F, typename S>
bool operator>(const Pair<F,S>& lhand, const Pair<F,S>& rhand) {
    return rhand < lhand;
}

template<typename F, typename S>
bool operator>=(const Pair<F,S>& lhand, const Pair<F, S>& rhand){
    return !(lhand < rhand);
}

template<typename F, typename S>
bool operator<=(const Pair<F,S>& lhand, const Pair<F, S>& rhand){
    return !(rhand < lhand);
}

template<typename F, typename S>
bool operator==(const Pair<F,S>& lhand, const Pair<F,S> &rhand){
    return (lhand.first == rhand.first) && (lhand.second == rhand.second);
}

template<typename F, typename S>
bool operator!=(const Pair<F,S> &lhand, const Pair<F,S> &rhand){
    return !(lhand == rhand);
}

template<typename T, typename U>
Pair<T,U> operator+(Pair<T,U> lhand, const Pair<T,U>& rhand){
    return lhand+=rhand;
}

//factory function
template<typename T, typename U>
Pair<T,U> MakePair(const T& t, const U& u){
    return Pair<T,U>{t,u};
}

#endif