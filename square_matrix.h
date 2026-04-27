#ifndef LABA3_SQUARE_MATRIX_H
#define LABA3_SQUARE_MATRIX_H

#include <cmath>
#include "rectangle_matrix.h"

template <class T>
class SquareMatrix : public RectangleMatrix<T> {

public:
    SquareMatrix();
    SquareMatrix(int n);
    SquareMatrix(T* arr, int n);
    SquareMatrix(const SquareMatrix<T>& other);

    ~SquareMatrix() override = default;

    // operations
    SquareMatrix<T>* add(const IMatrix<T>& other) const override;
    SquareMatrix<T>* multiply_scalar(const T& scalar) const override;

    double norm() const override;

    // row's operations
    void swap_rows(int row1, int row2) override;
    void multiply_rows(int row, const T& scalar) override;
    void add_row(int row1, int row2, const T& scalar) override;
};

template <class T>
SquareMatrix<T>::SquareMatrix()
    : RectangleMatrix<T>() {}

template <class T>
SquareMatrix<T>::SquareMatrix(int n)
    : RectangleMatrix<T>(n, n) {}

template<class T>
SquareMatrix<T>::SquareMatrix(T *arr, int n)
    : RectangleMatrix<T>(arr, n, n) {}

template <class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other)
    : RectangleMatrix<T>(other) {}

template<class T>
SquareMatrix<T>* SquareMatrix<T>::add(const IMatrix<T>& other) const {
    int n = this->get_rows();

    if (n != other.get_columns() || n != other.get_rows())
        throw std::invalid_argument("Matrix size must match");

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
            using std::abs;
            auto value = static_cast<double>(abs(this->get(i, j)));
            sum += value * value;
        }
    }

    return std::sqrt(sum);
}

// row's operations
template <class T>
void SquareMatrix<T>::swap_rows(int row1, int row2) {
    if (row1 == row2)
        return;

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
void SquareMatrix<T>::multiply_rows(int row, const T& scalar) {
    if (row < 0 || row >= this->get_rows())
        throw std::out_of_range("Matrix row index out of range");

    for (int j = 0; j < this->get_rows(); j++)
        this->set(this->get(row, j) * scalar, row, j);
}

template <class T>
void SquareMatrix<T>::add_row(int row1, int row2, const T& scalar) {
    int n = this->get_rows();

    if (row1 < 0 || row1 >= n || row2 < 0 || row2 >= n)
        throw std::out_of_range("Matrix row index out of range");

    for (int k = 0; k < n; k++) {
        T value = this->get(row2, k) * scalar + this->get(row1,k);

        this->set(value, row1, k);
    }
}


#endif //LABA3_SQUARE_MATRIX_H
