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

    const T& get(int row, int column) const override;

    int get_rows() const override;
    int get_columns() const override;
    int get_size() const;

    double norm() const override;

    void set(const T& value, int row, int column) override;

    SquareMatrix<T>* add(const IMatrix<T>& other) const override;
    DiagonalMatrix<T>* multiply_scalar(const T& scalar) const override;

private:
    DynamicArray<T> data; // хранит только элементы на диагонали матрицы
    int n; // так как диагональная матрица - квадратная

    static const T zero{};

    static int check_size(int n);

    bool check_range(int row, int column) const;
};

template<class T>
DiagonalMatrix<T>::DiagonalMatrix()
    : data(0), n(0) {}

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(int n)
    : data(check_size(n)), n(n) {}

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(const T& items, int n)
    : data(items, check_size(n)), n(n) {}

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(const DiagonalMatrix<T> &other)
    :data(other.data), n(other.n) {}

template<class T>
const T& DiagonalMatrix<T>::get(int row, int column) const{
    if (!check_range(row, column))
        throw std::out_of_range("Index out of range");

    if (row != column)
        return zero;

    return data[row];
}

template<class T>
int DiagonalMatrix<T>::get_rows() const {
    return n;
}

template<class T>
int DiagonalMatrix<T>::get_columns() const {
    return n;
}

template <typename T>
int DiagonalMatrix<T>::get_size() const {
    return n;
}

template<class T>
double DiagonalMatrix<T>::norm() const {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        using std::abs;
        auto temp = static_cast<double>(abs(data[i]));
        sum += temp * temp;
    }

    return std::sqrt(sum);
}

template<class T>
void DiagonalMatrix<T>::set(const T& value, int row, int column) {
    if (!check_range(row, column))
        throw std::out_of_range("Index out of range");

    if (row != column)
        throw std::invalid_argument("i must be = j");

    data.set(value, row);
}

template<class T>
SquareMatrix<T>* DiagonalMatrix<T>::add(const IMatrix<T> &other) const {
    if (this->get_columns() != other.get_columns() || this->get_rows() != other.get_rows())
        throw std::invalid_argument("Matrix size must match");

    auto *result = new DiagonalMatrix<T>(this->get_size());

    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_columns(); j++)
            result->set(other.get(i, j) + this->get(i, j), i, j);
    }

    return result;
}

template<class T>
DiagonalMatrix<T>* DiagonalMatrix<T>::multiply_scalar(const T& scalar) const {

    auto *result = new DiagonalMatrix<T>(this->get_size());

    for (int i = 0; i < this->get_size(); i++)
        result->data.set(this->get(i) * scalar, i);

    return result;
}

//private
template<class T>
int DiagonalMatrix<T>::check_size(int n) {
    if (n < 0)
        throw std::invalid_argument("Matrix's size must be positive");

    return n;
}

template<class T>
bool DiagonalMatrix<T>::check_range(int row, int column) const {
    return row >= 0 && column >= 0 && row < this->get_rows() && column < this->get_columns();
}

#endif //LABA3_DIAGONAL_MATRIX_H
