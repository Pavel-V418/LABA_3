#ifndef LABA3_RECTANGLE_MATRIX_H
#define LABA3_RECTANGLE_MATRIX_H

#include <cmath>
#include "base_matrix.h"

template <class T>
class RectangleMatrix : public BaseMatrix<T> {

public:
    RectangleMatrix();
    RectangleMatrix(int rows, int columns);
    RectangleMatrix(T *arr, int rows, int columns);
    RectangleMatrix(const RectangleMatrix<T>& other);

    RectangleMatrix<T>* add(const IMatrix<T>& other) const override;
    RectangleMatrix<T>* multiply_scalar(const T& scalar) const override;

    double norm() const;

    // row's operations
    void swap_rows(int row1, int row2);
    void multiply_rows(int i, const T& scalar);
    void add_row(int i, int i_1, const T& scalar);

};

template <class T>
RectangleMatrix<T>::RectangleMatrix()
    : BaseMatrix<T>() {}

template <class T>
RectangleMatrix<T>::RectangleMatrix(int rows, int columns)
    : BaseMatrix<T>(rows, columns) {}

template<class T>
RectangleMatrix<T>::RectangleMatrix(T *arr, int rows, int columns)
    : BaseMatrix<T>(arr, rows, columns) {}

template <class T>
RectangleMatrix<T>::RectangleMatrix(const RectangleMatrix<T>& other)
    : BaseMatrix<T>(other) {}

template <class T>
RectangleMatrix<T>* RectangleMatrix<T>::add(const IMatrix<T>& other) const {
    int rows = this->get_rows();
    int columns = this->get_columns();

    if (rows != other.get_rows() || columns != other.get_columns())
        throw std::out_of_range("Matrix size must match");

    auto *result = new RectangleMatrix<T>(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result->set(this->get(i, j) + other.get(i, j), i, j);
        }
    }

    return result;
}

template <class T>
RectangleMatrix<T>* RectangleMatrix<T>::multiply_scalar(const T& scalar) const {
    int rows = this->get_rows();
    int columns = this->get_columns();

    auto *result = new RectangleMatrix<T>(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result->set(this->get(i, j) * scalar, i, j);
        }
    }

    return result;
}

template <class T>
double RectangleMatrix<T>::norm() const {
    int rows = this->get_rows();
    int columns = this->get_columns();

    double sum = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double value = static_cast<double>(this->get(i, j));
            sum += value * value;
        }
    }

    return std::sqrt(sum);
}

template<class T>
void RectangleMatrix<T>::swap_rows(int row1, int row2) {
    int rows = this->get_rows();
    int columns = this->get_columns();

    if (row1 == row2)
        return;

    if (row1 < 0 || row2 < 0 || row1 >= rows || row2 >= rows)
        throw std::out_of_range("out of range");

    for (int j = 0; j < columns; j++) {
        T value = this->get(row1, j);

        this->set(this->get(row2, j), row1, j);
        this->set(value, row2, j);
    }
}

template <class T>
void RectangleMatrix<T>::multiply_rows(int i, const T& scalar) {
    int rows = this->get_rows();
    int columns = this->get_columns();

    if (i < 0 || i >= rows)
        throw std::out_of_range("Matrix row index out of range");

    for (int j = 0; j < columns; j++) {
        this->set(this->get(i, j) * scalar, i, j);
    }
}

template<class T>
void RectangleMatrix<T>::add_row(int i, int i_1, const T& scalar) {
    int rows = this->get_rows();
    int columns = this->get_columns();

    if (i < 0 || i >= rows || i_1 < 0 || i_1 >= rows)
        throw std::out_of_range("Matrix row index out of range");

    for (int k = 0; k < columns; k++) {
        T value = this->get(i_1, k) * scalar + this->get(i,k);

        this->set(value, i, k);
    }
}

#endif //LABA3_RECTANGLE_MATRIX_H
