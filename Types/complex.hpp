#pragma once
#include <iostream>

template<typename T>
class Complex{
        T m_real{};
        T m_imaginary{};
    public:

        Complex() = default;
        Complex(T r, T i): m_real{r}, m_imaginary{i}{}
        
        Complex(const Complex& c) : m_real{c.m_real}, m_imaginary{c.m_imaginary}{}
        Complex& operator=(const Complex& c){
            if(this != &c){
                m_real = c.m_real;
                m_imaginary = c.m_imaginary;
            }

            return *this;
        }

        Complex(Complex&& c): m_real{std::move(c.m_real)}, m_imaginary{std::move(c.m_imaginary)}{}
        Complex& operator=(Complex&& c){
            if(this != &c){
                m_real = std::move(c.m_real);
                m_imaginary = std::move(c.m_imaginary);
            }

            return *this;
        }
        ~Complex() = default;

        Complex& operator+=(const Complex& c){
            m_real += c.m_real;
            m_imaginary += c.m_imaginary;
            return *this;
        }
        
        Complex& operator-=(const Complex& c){
            m_real += c.m_real;
            m_imaginary += c.m_imaginary;
            return *this;
        }

        template<typename U>
        Complex& operator*=(const U& c){
            m_imaginary *= c;
            m_real *= c;
            return *this;
        }

        Complex& operator*=(const Complex &c){
            T realNum = m_real * c.m_real - m_imaginary * c.m_imaginary;
            m_imaginary = m_real * c.m_imaginary + m_imaginary * c.m_real;
            m_real = realNum;
            return *this;
        }

        template<typename U>
        Complex& operator/=(const U& c){
            m_imaginary /= c;
            m_real /= c;
            return *this;
        }

        Complex& operator/=(const Complex& c){
            auto c_conj = c.conjugate();
            this->mul(c_conj);
            double n = c.norm();
            n = n * n;
            if (!nearZero(n))
            {
                m_real /= n;
                m_imaginary /= n;
            }
            return *this;
        }

        void conjugate(){
            m_imaginary = -m_imaginary;
        }

        float norm() const{
            return sqrt(m_real * m_real + m_imaginary * m_imaginary);
        }

        Complex get_conjugate() const{
            auto temp = *this;
            temp.conjugate();
            return temp;
        }

        inline bool nearZero(float a){
            if (fabs(a) <= 1e-6){
                return true;
            }
            return false;
        }

        template<typename U> friend Complex<U> operator+(Complex<U> rhand, const Complex<U>& lhand);
        template<typename U> friend Complex<U> operator-(Complex<U> rhand, const Complex<U>& lhand);
        template<typename U> friend Complex<U> operator*(Complex<U> rhand, const Complex<U>& lhand);
        template<typename U> friend Complex<U> operator/(Complex<U> rhand, const Complex<U>& lhand);

        friend std::ostream& operator<<(std::ostream& os, const Complex& c){
            return os<<c.m_real << ((c.m_imaginary < 0.0) ? " - " : " + ") << std::abs(c.m_imaginary)<<"i";
        }
};

template<typename U>
Complex<U> operator+(Complex<U> rhand, const Complex<U>& lhand){
    return rhand += lhand;
}

template<typename U>
Complex<U> operator-(Complex<U> rhand, const Complex<U>& lhand){
    return rhand -= lhand;
}

template<typename U>
Complex<U> operator*(Complex<U> rhand, const Complex<U>& lhand){
    return rhand *= lhand;
}

template<typename U>
Complex<U> operator/(Complex<U> rhand, const Complex<U>& lhand){
    return rhand /= lhand;
}