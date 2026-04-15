#ifndef LABA3_DIAGONAL_MATRIX_H
#define LABA3_DIAGONAL_MATRIX_H

#include "LABA_2/dynamicArray.h"
#include <cmath>
#include "square_matrix.h"

template <class T>
class DiagonalMatrix : public IMatrix<T>{

public:
    DiagonalMatrix();
    DiagonalMatrix(int n);
    DiagonalMatrix(const T& items, int n);
    DiagonalMatrix(const DiagonalMatrix<T>& other);

    ~DiagonalMatrix() override = default;

    const T& get(int i, int j) const override;

    int get_rows() const override;
    int get_columns() const override;

    double norm() const override;

    void set(const T& value, int i, int j) override;

    SquareMatrix<T>* add(const IMatrix<T>& other) const override;
    DiagonalMatrix<T>* multiply_scalar(const T& scalar) const override;

private:
    DynamicArray<T> data; // хранит только элементы на диагонали матрицы
    int n; // так как диагональная матрица - квадратная
};

template<class T>
DiagonalMatrix<T>::DiagonalMatrix()
    : data(0) { n = 0;}

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(int n)
    : data(n) { this->n = n; }

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(const T& items, int n)
    : data(items, n) { this->n = n;} // недописал

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(const DiagonalMatrix<T> &other)
    :data(other.data) { this->n = other.n; }

template<class T>
const T& DiagonalMatrix<T>::get(int i, int j) const{
    if (i != j)
        throw std::invalid_argument("i must be = j");
    return data[i];
}

template<class T>
int DiagonalMatrix<T>::get_rows() const {
    return n;
}

template<class T>
int DiagonalMatrix<T>::get_columns() const {
    return n;
}

template<class T>
double DiagonalMatrix<T>::norm() const {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += data[i] * data[i];

    return std::sqrt(sum);
}

template<class T>
void DiagonalMatrix<T>::set(const T& value, int i, int j) {
    if (i != j)
        throw std::invalid_argument("i must be = j");

    data.set(value, i);
}

template<class T>
SquareMatrix<T>* DiagonalMatrix<T>::add(const IMatrix<T> &other) const {
    if (this->get_columns() != other.get_columns() || this->get_rows() != other.get_rows())
        throw std::invalid_argument("Matrix size must match");

    auto *result = new DiagonalMatrix<T>(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            result->set(other.get(i, j) + this->get(i, j), i, j);
    }

    return result;
}

template<class T>
DiagonalMatrix<T>* DiagonalMatrix<T>::multiply_scalar(const T& scalar) const {

    auto *result = new DiagonalMatrix<T>(n);

    for (int i = 0; i < n; i++)
        result->data.set(this->get(i) * scalar, i);

    return result;
}

#endif //LABA3_DIAGONAL_MATRIX_H
