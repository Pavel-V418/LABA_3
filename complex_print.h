#ifndef LABA3_COMPLEX_PRINT_H
#define LABA3_COMPLEX_PRINT_H

#include <iostream>
#include "complex.h"

inline std::istream& operator>>(std::istream& in, Complex& c) {
    double re, im;
    in >> re >> im;
    c = Complex(re, im);
    return in;
}

inline std::ostream& operator<<(std::ostream& out, const Complex& c) {
    out << c.real();
    if (c.imag() >= 0) out << "+";
    out << c.imag() << "i";
    return out;
}

#endif //LABA3_COMPLEX_PRINT_H
