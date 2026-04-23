#ifndef LABA3_VECTOR_H
#define LABA3_VECTOR_H

#include "LABA_2/dynamicArray.h"
#include <cmath>

template<class T>
class Vector {

public:
    Vector();
    Vector(int n);
    Vector(T* items, int n);
    Vector(const Vector<T>& other);

    ~Vector() = default;

    const T& get(int index) const;

    int get_size() const;

    void set(const T& value, int index);

    const T& operator[](int index) const;

    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    Vector<T> operator*(const T& scalar) const;
    Vector<T>& operator=(const Vector<T>& other) = default;

    T dot(const Vector<T>& other) const; // не const T&, потому что переменная под полученное число создаётся внутри функции

    double norm() const;

private:
    DynamicArray<T> data;
    int n;

    static int check_size(int n);
    void compare_sizes(const Vector<T>& other);
    void check_index(int index) const;
};

template<class T>
Vector<T>::Vector()
    : data(0), n(0) {}

template<class T>
Vector<T>::Vector(int n)
    : data(check_size(n)), n(n) {}

template<class T>
Vector<T>::Vector(T *items, int n)
    : data(items, check_size(n)), n(n) {}

template<class T>
Vector<T>::Vector(const Vector<T> &other)
    : data(other.data), n(other.n) {}

template<class T>
const T& Vector<T>::get(int index) const {
    check_index(index);

    return data.get(index);
}
template<class T>
int Vector<T>::get_size() const {
    return n;
}

template<class T>
void Vector<T>::set(const T& value, int index) {

    data.set(value, index);
}

template<class T>
double Vector<T>::norm() const {
    double sum = 0;

    for (int i = 0; i < this->get_size(); i++) {
        auto value = static_cast<double>(this->get(i));
        sum += value * value;
    }

    return std::sqrt(sum);
}

template<class T>
T Vector<T>::dot(const Vector<T>& other) const {
    compare_sizes(other);

    T result = T{};

    for (int i = 0; i < this->get_size(); i++)
        result += this->get(i) * other.get(i);

    return result;
}

// overload operators
template<class T>
const T &Vector<T>::operator[](int index) const {
    check_index(index);

    return this->get(index);
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T> &other) const {
    compare_sizes(other);

    Vector<T> result(get_size());
    for (int i = 0; i < get_size(); i++)
        result.set(this->get(i) + other.get(i), i);

    return result;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T> &other) const {
    compare_sizes(other);

    Vector<T> result(get_size());
    for (int i = 0; i < get_size(); i++)
        result.set(this->get(i) - other.get(i), i);

    return result;
}

template<class T>
Vector<T> Vector<T>::operator*(const T &scalar) const {
    Vector<T> result(get_size());

    for (int i = 0; i < this->get_size(); i++)
        result.set(this->get(i) * scalar, i);

    return result;
}

//private
template<class T>
int Vector<T>::check_size(int n) {
    if (n < 0)
        throw std::invalid_argument("Vector's size must be positive");

    return n;
}

template<class T>
void Vector<T>::check_index(int index) const {
    if (index < 0 || index >= this->get_size())
        throw std::out_of_range("Index out of range");
}

template<class T>
void Vector<T>::compare_sizes(const Vector<T>& other) {
    if (this->get_size() != other.get_size())
        throw std::invalid_argument("Vector::operator+: Dimensions mismatch");
}
#endif //LABA3_VECTOR_H
