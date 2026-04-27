#ifndef LABA3_COMPLEX_H
#define LABA3_COMPLEX_H

#include <stdexcept>
#include <cmath>

class Complex {

public:
    Complex(double r = 0, double i = 0)
        : re(r), im(i) {}

    double real() const {
        return re;
    }

    double imag() const {
        return im;
    }

    Complex operator+(const Complex& other) const {
        return Complex(re + other.re, im + other.im);
    }

    Complex operator-(const Complex &other) const {
        return Complex(re - other.re, im - other.im);
    }

    Complex operator*(const Complex &other) const {
        return Complex(re * other.re - im * other.im, re * other.im + im * other.re);
    }

    Complex operator/(const Complex& other) const {
        double denom = other.re * other.re + other.im * other.im; // знаменатель

        if (std::abs(denom) < 1e-12)
            throw std::runtime_error("Division by zero");

        double new_re = (re * other.re + im * other.im) / denom;
        double new_im = (im * other.re - re * other.im) / denom;

        return Complex(new_re, new_im);
    }

    bool operator==(const Complex& other) const {
        static constexpr double EPS = 1e-9;

        return std::abs(re - other.re) < EPS &&
               std::abs(im - other.im) < EPS;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    double norm_sqr() const {
        return re * re + im * im;
    }

    double abs() const {
        return std::sqrt(norm_sqr());
    }

    Complex& operator+=(const Complex& other) {
        re += other.re;
        im += other.im;
        return *this;
    }

private:
    double re;
    double im;

};

inline double abs(const Complex& c) { // глобальная abs
    return c.abs();
}

#endif //LABA3_COMPLEX_H
