#ifndef LABA3_SPARSE_MATRIX_H
#define LABA3_SPARSE_MATRIX_H

#include <complex>

#include "imatrix.h"
#include "LABA_2/dynamicArray.h"

template<typename T>
struct Element {
    int row;
    int column;
    T value;
};

// большинство элементов равны 0, но мы их хранить не будем
template<class T>
class SparseMatrix : public IMatrix<T>{

public:
    SparseMatrix();
    SparseMatrix(int i, int j);
    SparseMatrix(T *items, int i, int j);
    SparseMatrix(const SparseMatrix& other);

    ~SparseMatrix() override = default;

    const T& get(int i, int j) const override;

    int get_rows() const override;
    int get_columns() const override;

    double norm() const override;

    void set(const T& value, int i, int j) override;

    SparseMatrix* add(const IMatrix<T>& other) const override;
    SparseMatrix* multiply_scalar(const T& scalar) const override;

private:
    DynamicArray<Element<T>> data; // храним всё, кроме нулей
    int rows;
    int columns;

};

template<class T>
SparseMatrix<T>::SparseMatrix()
    : data(0)
{
    rows = 0;
    columns = 0;
}

template<class T>
SparseMatrix<T>::SparseMatrix(int i, int j)
    : data(i * j)
{
    rows = i;
    columns = j;
}

template<class T>
SparseMatrix<T>::SparseMatrix(T *items, int i, int j)
    : data(items)
{
    rows = i;
    columns = j;
}

template<class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix &other)
    : data(other.data)
{
    rows = other.rows;
    columns = other.columns;
}

template<class T>
const T &SparseMatrix<T>::get(int i, int j) const {
    if (i < 0 || j < 0 || i >= this->get_rows() || j >= this->get_columns())
        throw std::out_of_range("Index out of range");

    for (int k = 0; k < data.get_size(); k++) {

        if (data.get(k).row == i && data.get(k).column == j)
            return data.get(k).value;
    }

    return T(0); // если не нашли элемент, то это 0
}

template<class T>
int SparseMatrix<T>::get_rows() const {
    return rows;
}

template<class T>
int SparseMatrix<T>::get_columns() const {
    return columns;
}

template<class T>
double SparseMatrix<T>::norm() const {
    double sum = 0;

    for (int k = 0; k < data.get_size(); k++) {
        auto value = static_cast<double>(data.get(k).value);

        sum += value * value;
    }

    return std::sqrt(sum);
}

template<class T>
void SparseMatrix<T>::set(const T& value, int i, int j)
{
    if (i < 0 || j < 0 ||
        i >= this->get_rows() ||
        j >= this->get_columns())
        throw std::out_of_range("index out of range");

    for (int k = 0; k < data.get_size(); k++)
    {
        if (data.get(k).row == i &&
            data.get(k).col == j)
        {
            // если value = 0 , то удалаяем элемент из матрицы
            if (value == T(0))
            {
                data.remove(k);
            }
            else
            {
                data.get(k).value = value;
            }
            return;
        }
    }

    // если не найден
    if (value != T(0))
    {
        Element<T> element;
        element.row = i;
        element.col = j;
        element.value = value;

        int size = data.get_size();
        data.resize(size + 1);
        data.set(element, size);
    }
}
#endif //LABA3_SPARSE_MATRIX_H
