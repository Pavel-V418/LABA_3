#ifndef LABA3_MATRIX_H
#define LABA3_MATRIX_H

#include "imatrix.h"
#include "LABA_2/dynamicArray.h"
#include <cmath>

template<class T>
class RectangleMatrix : public IMatrix<T>{

public:
    RectangleMatrix();
    RectangleMatrix(int row, int column); // переименовать i j
    RectangleMatrix(T* arr, int row, int column);
    RectangleMatrix(const RectangleMatrix<T>& other);

    ~RectangleMatrix() override = default;

    const T& get(int row, int column) const override;
    int get_rows() const override;
    int get_columns() const override;

    void set(const T& value, int row, int column) override;

    RectangleMatrix<T>* add(const IMatrix<T>& other) const override; // complete
    RectangleMatrix<T>* multiply_scalar(const T& scalar) const override; // complete

    double norm() const override; // complete

    // row's operations
    virtual void swap_rows(int row1, int row2); // complete
    virtual void multiply_rows(int row, const T& scalar); // complete
    virtual void add_row(int row1, int row2, const T& scalar); // complete

private:
    DynamicArray<T> data;
    int rows; // строки
    int columns; // столбцы

    static int check_size(int row,int column);

    void check_range(int row, int column) const;
};

// constructors
template<class T>
RectangleMatrix<T>::RectangleMatrix()
    : data(0), rows(0), columns(0) {}

template<class T>
RectangleMatrix<T>::RectangleMatrix(int row, int column)
    : data(check_size(row, column)), rows(row), columns(column) {}

template<class T>
RectangleMatrix<T>::RectangleMatrix(T *arr, int row, int column)
    : data(arr, check_size(row, column)), rows(row), columns(column) {}

template<class T>
RectangleMatrix<T>::RectangleMatrix(const RectangleMatrix<T>& other)
    : data(other.data), rows(other.rows), columns(other.columns) {}

//getters
template<class T>
const T& RectangleMatrix<T>::get(int row, int column) const {
    check_range(row, column);

    return data.get(row*columns + column); // row-major order
};

template<class T>
int RectangleMatrix<T>::get_rows() const {
    return rows;
}

template<class T>
int RectangleMatrix<T>::get_columns() const {
    return columns;
}

// setter
template<class T>
void RectangleMatrix<T>::set(const T& value, int row, int column){
    check_range(row, column);

    data.set(value, row*columns + column);
}

template <class T>
double RectangleMatrix<T>::norm() const {
    double sum = 0;

    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_columns(); j++) {
            using std::abs;
            auto value = static_cast<double>(abs(this->get(i, j)));
            sum += value * value;
        }
    }

    return std::sqrt(sum);
}

template <class T>
RectangleMatrix<T>* RectangleMatrix<T>::add(const IMatrix<T>& other) const {
    if (this->get_rows() != other.get_rows() || this->get_columns() != other.get_columns())
        throw std::invalid_argument("Matrix size must match");

    auto *result = new RectangleMatrix<T>(this->get_rows(), this->get_columns());

    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_columns(); j++) {
            result->set(this->get(i, j) + other.get(i, j), i, j);
        }
    }

    return result;
}

template <class T>
RectangleMatrix<T>* RectangleMatrix<T>::multiply_scalar(const T& scalar) const {
    auto *result = new RectangleMatrix<T>(this->get_rows(), this->get_columns());

    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_columns(); j++) {
            result->set(this->get(i, j) * scalar, i, j);
        }
    }

    return result;
}

// элементарные преобразования
template<class T>
void RectangleMatrix<T>::swap_rows(int row1, int row2) {
    if (row1 == row2)
        return;

    if (row1 < 0 || row2 < 0 || row1 >= this->get_rows() || row2 >= this->get_rows())
        throw std::out_of_range("out of range");

    for (int j = 0; j < this->get_columns(); j++) {
        T value = this->get(row1, j);

        this->set(this->get(row2, j), row1, j);
        this->set(value, row2, j);
    }
}

template <class T>
void RectangleMatrix<T>::multiply_rows(int row, const T& scalar) {
    if (row < 0 || row >= this->get_rows())
        throw std::out_of_range("Matrix row index out of range");

    for (int j = 0; j < this->get_columns(); j++) {
        this->set(this->get(row, j) * scalar, row, j);
    }
}

template<class T>
void RectangleMatrix<T>::add_row(int row1, int row2, const T& scalar) {
    if (row1 < 0 || row1 >= this->get_rows() || row2 < 0 || row2 >= this->get_rows())
        throw std::out_of_range("Matrix row index out of range");

    for (int k = 0; k < this->get_columns(); k++) {
        T value = this->get(row2, k) * scalar + this->get(row1,k);

        this->set(value, row1, k);
    }
}

//private
template<class T>
int RectangleMatrix<T>::check_size(int row, int column) {
    if (row < 0 || column < 0)
        throw std::invalid_argument("Index out of range");

    return row * column;
}

template<class T>
void RectangleMatrix<T>::check_range(int row, int column) const {
    if (row >= this->get_rows() || column >= this->get_columns() || row < 0 || column < 0)
        throw std::out_of_range("index out of range");
}
#endif //LABA3_MATRIX_H
