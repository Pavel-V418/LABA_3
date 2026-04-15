#ifndef LABA3_MATRIX_H
#define LABA3_MATRIX_H

#include "imatrix.h"
#include "LABA_2/dynamicArray.h"

template<class T>
class BaseMatrix : public IMatrix<T>{

protected:
    DynamicArray<T> data;
    int rows; // строки
    int columns; // столбцы

public:
    BaseMatrix();
    BaseMatrix(int i, int j);
    BaseMatrix(T* arr, int rows, int columns);
    BaseMatrix(const BaseMatrix<T>& other);

    ~BaseMatrix() override = default;

    const T& get(int i, int j) const override;
    int get_rows() const override;
    int get_columns() const override;

    void set(const T& value, int i, int j) override;
};

// constructors
template<class T>
BaseMatrix<T>::BaseMatrix()
    : data(0)
{
    rows = 0;
    columns = 0;
}

template<class T>
BaseMatrix<T>::BaseMatrix(int i, int j)
    : data(i * j)
{
    if (i <= 0 || j <= 0)
        throw std::invalid_argument("Matrix size must be > 0");

    rows = i;
    columns = j;
}

template<class T>
BaseMatrix<T>::BaseMatrix(T *arr, int rows, int columns)
    : data(rows * columns)
{
    if (rows < 0 || columns < 0)
        throw std::out_of_range("Index out of range");

    this->rows = rows;
    this->columns = columns;

    for (int i = 0; i < rows * columns; i++)
        data.set(arr[i], i);
}

template<class T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix<T>& other)
    : data(other.data)
{
    rows = other.rows;
    columns = other.columns;
}

//getters
template<class T>
const T& BaseMatrix<T>::get(int i, int j) const {
    if (i >= rows || j >= columns || i < 0 || j < 0)
        throw std::out_of_range("index out of range");

    return data.get(i*columns + j); // row-major order
};

template<class T>
int BaseMatrix<T>::get_rows() const {
    return rows;
}

template<class T>
int BaseMatrix<T>::get_columns() const {
    return columns;
}

// setter
template<class T>
void BaseMatrix<T>::set(const T& value, int i, int j){
    if (i >=rows || j >=columns || i < 0 || j < 0)
        throw std::out_of_range("index out of range");

    data.set(value, i*columns + j);
}

#endif //LABA3_MATRIX_H
