#ifndef LABA3_TRIANGLE_MATRIX_H
#define LABA3_TRIANGLE_MATRIX_H

#include "square_matrix.h"
#include "LABA_2/dynamicArray.h"
// тоже квадратная матрица
enum class TriangleType {
    lower_triangle,
    upper_triangle
};

template<class T>
class TriangleMatrix : public IMatrix<T>{

public:
    TriangleMatrix(TriangleType type);
    TriangleMatrix(int n, TriangleType type);
    TriangleMatrix(T *items, int n, TriangleType type);
    TriangleMatrix(const TriangleMatrix<T>& other);

    ~TriangleMatrix() override = default;

    const T& get(int i, int j) const override;

    int get_rows() const override;
    int get_columns() const override;

    double norm() const override;

    void set(const T& value, int i, int j) override;

    SquareMatrix<T>* add(const IMatrix<T>& other) const override;
    TriangleMatrix<T>* multiply_scalar(const T& scalar) const override;


private:
    DynamicArray<T> triangle_data; // хранит только значения в треугольнике выбранного типа
    int n; // матрица квадратная
    TriangleType type;
};

template<class T>
TriangleMatrix<T>::TriangleMatrix(TriangleType type)
    : triangle_data(0)
{
    n = 0;
    this->type = type;
}

template<class T>
TriangleMatrix<T>::TriangleMatrix(int n, TriangleType type)
    : triangle_data(n)
{
    this->n = n;
    this->type = type;
}

template<class T>
TriangleMatrix<T>::TriangleMatrix(T *items, int n, TriangleType type)
    : triangle_data(items)
{
    this->n = n;
    this->type = type;
}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T> &other)
    : triangle_data(other.data)
{
    n = other.n;
    type = other.type;
}

// геттеры
template<class T>
const T& TriangleMatrix<T>::get(int i, int j) const {
    if (i < 0 || j < 0 || i >= this->get_rows() || j >= this->get_columns())
        throw std::out_of_range("Index out of range");

    if (type == TriangleType::upper_triangle && i > j)
        return T(0);

    if (type == TriangleType::lower_triangle && j > i)
        return T(0);

    return BaseMatrix<T>::get(i, j);
}

template<class T>
int TriangleMatrix<T>::get_rows() const {
    return n;
}

template<class T>
int TriangleMatrix<T>::get_columns() const {
    return n;
}

template<class T>
void TriangleMatrix<T>::set(const T &value, int i, int j) {
    if (i < 0 || j < 0 || i >= this->get_rows() || j >= this->get_columns())
        throw std::out_of_range("Index out of range");

    if (type == TriangleType::upper_triangle && i > j)
        throw std::out_of_range("Index out of upper_triangle's range");

    if (type == TriangleType::lower_triangle && j > i)
        throw std::out_of_range("Index out of lower_triangle's range");

    BaseMatrix<T>::set(value, i, j);
}

template<class T>
double TriangleMatrix<T>::norm() const{
    double sum = 0;

    for (int i = 0; i < this->get_rows(); i++) {

        if (type == TriangleType::upper_triangle) {
            for (int j = i; j < this->get_rows(); j++) {
                T value = static_cast<double>(this->get(i, j));
                sum += value * value;
            }
        } // type upper

        else {
            for (int j = 0; j <= i; j++) {
                T value = static_cast<double>(this->get(i, j));
                sum += value * value;
            }
        } // type lower
    }

    return std::sqrt(sum);
}

template<class T>
SquareMatrix<T>* TriangleMatrix<T>::add(const IMatrix<T>& other) const {

    if (this->get_rows() != other.get_rows() || this->get_columns() != other.get_columns())
        throw std::invalid_argument("Matrix size must match");

    auto *result = new SquareMatrix<T>(this->get_rows());

    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_columns(); j++)
            result->set(this->get(i, j) + other.get(i, j), i, j);
    }

    return result;
}

template<class T>
TriangleMatrix<T>* TriangleMatrix<T>::multiply_scalar(const T& scalar) const {
    auto *result = new TriangleMatrix<T>(this->get_rows(), this->type);

    for (int i = 0; i < this->get_rows(); i++) {

        if (this->type == TriangleType::upper_triangle) {
            for (int j = i; j < this->get_columns(); j++)
                result->set(this->get(i, j) * scalar, i, j);
        }

        else {
            for (int j = 0; j <= i; j++)
                result->set(this->get(i, j) * scalar, i, j);
        }
    }
    return result;
}


#endif //LABA3_TRIANGLE_MATRIX_H
