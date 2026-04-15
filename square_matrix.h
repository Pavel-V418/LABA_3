#ifndef LABA3_SQUARE_MATRIX_H
#define LABA3_SQUARE_MATRIX_H

#include <cmath>
#include "base_matrix.h"

template <class T>
class SquareMatrix : public BaseMatrix<T> {

public:
    SquareMatrix();
    SquareMatrix(int n); // добавить во входной параметр T* item или const T& item
    SquareMatrix(T* arr, int n);
    SquareMatrix(const SquareMatrix<T>& other);

    ~SquareMatrix() override = default;

    // operations
    SquareMatrix<T>* add(const IMatrix<T>& other) const override;
    SquareMatrix<T>* multiply_scalar(const T& scalar) const override;

    double norm() const;

    // row's operations
    void swap_rows(int row1, int row2);
    void multiply_rows(int i, const T& scalar);
    void add_row(int i, int i_1, const T& scalar); // i_1 - та строка, которую мы берем и прибавляем в i-ой

    // column's operations
    /*void swap_columns(int column1, int column2);
    void multiply_columns(int j, const T& scalar);
    void add_column(int i, int j, const T& scalar);*/ // нужно ли?

};

template <class T>
SquareMatrix<T>::SquareMatrix()
    : BaseMatrix<T>() {}

template <class T>
SquareMatrix<T>::SquareMatrix(int n)
    : BaseMatrix<T>(n, n) {}

template<class T>
SquareMatrix<T>::SquareMatrix(T *arr, int n)
    : BaseMatrix<T>(arr, n, n) {}

template <class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other)
    : BaseMatrix<T>(other) {}

template<class T>
SquareMatrix<T>* SquareMatrix<T>::add(const IMatrix<T>& other) const {
    int n = this->get_rows();

    if (n != other.get_columns() || n != other.get_rows())
        throw std::out_of_range("Matrix size must match");

    auto *result = new SquareMatrix<T>(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            result->set(this->get(i, j) + other.get(i, j), i, j);
    }

    return result;
}

template <class T>
SquareMatrix<T>* SquareMatrix<T>::multiply_scalar(const T& scalar) const {
    int n = this->get_rows();

    auto *result = new SquareMatrix<T>(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            result->set(this->get(i, j) * scalar, i, j);
    }

    return result;
}

template <class T>
double SquareMatrix<T>::norm() const {
    int n = this->get_rows();

    double sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto value = static_cast<double>(this->get(i, j));
            sum += value * value;
        }
    }

    return std::sqrt(sum);
}

// row's operations
template <class T>
void SquareMatrix<T>::swap_rows(int row1, int row2) {
    if (row1 == row2)
        throw std::out_of_range("row1 = row2");

    int n = this->get_rows();

    if (row1 < 0 || row2 < 0 || row1 >= n || row2 >= n)
        throw std::out_of_range("Matrix row index out of range");

    for (int j = 0; j < n; j++) {
        T temp_value = this->get(row1, j);
        this->set(this->get(row2, j), row1, j);
        this->set(temp_value, row2, j);
    }
}
template <class T>
void SquareMatrix<T>::multiply_rows(int i, const T& scalar) {
    int n = this->get_rows();

    if (i < 0 || i >= n)
        throw std::out_of_range("Matrix row index out of range");

    for (int j = 0; j < n; j++)
        this->set(this->get(i, j) * scalar, i, j);
}

template <class T>
void SquareMatrix<T>::add_row(int i, int i_1, const T& scalar) {
    int n = this->get_rows();

    if (i < 0 || i >= n || i_1 < 0 || i_1 >= n)
        throw std::out_of_range("Matrix row index out of range");

    for (int k = 0; k < n; k++) {
        T value = this->get(i_1, k) * scalar + this->get(i,k);

        this->set(value, i, k);
    }
}


#endif //LABA3_SQUARE_MATRIX_H
