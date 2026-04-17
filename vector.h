#ifndef LABA3_VECTOR_H
#define LABA3_VECTOR_H

#include "base_matrix.h"
#include <cmath>

template<class T>
class Vector : public BaseMatrix<T> {

public:
    Vector(int n);
    Vector(T* items, int n);
    Vector(const Vector<T>& other);

    ~Vector() override = default;

    const T& get(int i) const; // перегрузка
    int get_size() const; // перегрузка

    void set(const T& value, int i); // перегрузка

    Vector<T>* add(const IMatrix<T>& other) const override;
    Vector<T>* multiply_scalar(const T& scalar) const override;

    T dot(const Vector<T>& other) const; // не const T&, потому что переменная под полученное число создаётся внутри функции

    double norm() const override;

};

template<class T>
Vector<T>::Vector(int n)
    : BaseMatrix<T>(n, 1) {}

template<class T>
Vector<T>::Vector(T *items, int n)
    : BaseMatrix<T>(items, n, 1) {}

template<class T>
Vector<T>::Vector(const Vector<T> &other)
    : BaseMatrix<T>(other) {}

template<class T>
const T& Vector<T>::get(int i) const {
    return BaseMatrix<T>::get(i, 0);
}

template<class T>
int Vector<T>::get_size() const {
    return BaseMatrix<T>::get_rows();
}

template<class T>
void Vector<T>::set(const T& value, int i) {
    return BaseMatrix<T>::set(value, i, 0);
}

template<class T>
Vector<T>* Vector<T>::add(const IMatrix<T>& other) const {
    if (this->get_size() != other.get_rows() || other.get_columns() != 1)
        throw std::invalid_argument("Vector size mismatch");

    auto *result = new Vector<T>(other.get_rows());

    for (int i = 0; i < this->get_size(); i++)
        result->set(this->get(i) + other.get(i, 0), i);

    return result;
}

template<class T>
Vector<T>* Vector<T>::multiply_scalar(const T& scalar) const {
    auto *result = new Vector<T>(this->get_size());

    for (int i = 0; i < this->get_size(); i++)
        result->set(this->get(i) * scalar, i);

    return result;
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
    if (this->get_size() != other->get_size())
        throw std::invalid_argument("Vector size mismatch");

    T result = T(0);

    for (int i = 0; i < this->get_size(); i++)
        result += this->get(i) * other.get(i);

    return result;
}

#endif //LABA3_VECTOR_H
