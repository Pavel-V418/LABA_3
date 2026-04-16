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

    SparseMatrix<T>* add(const IMatrix<T>& other) const override;
    SparseMatrix<T>* multiply_scalar(const T& scalar) const override;

private:
    DynamicArray<Element<T>> data; // храним всё, кроме нулей
    int rows;
    int columns;

    int bin_search(int i, int j) const; // бинарный поиск элемента (i,j)
    int lower_bound(int i, int j) const; // поиск нижней границы для вставки элемента

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
void SparseMatrix<T>::set(const T& value, int i, int j){
    if (i < 0 || j < 0 || i >= this->get_rows() || j >= this->get_columns())
        throw std::out_of_range("index");

    int index = bin_search(i, j);

    // элемент найден
    if (index != -1) {
        if (value == T(0)){
            data.remove_at(index);
        }

        else{
            data.set(Element<T>{i, j, value}, index);
        }
        return;
    }

    // элемент НЕ найден
    if (value == T(0))
        return;

    int pos = lower_bound(i, j);

    data.resize(data.get_size() + 1);

    // сдвиг элементов вправо
    for (int k = data.get_size() - 1; k > pos; k--){
        data.set(data.get(k - 1), k);
    }

    data.set(Element<T>{i, j, value}, pos);
}

template<class T>
SparseMatrix<T>* SparseMatrix<T>::add(const IMatrix<T>& other) const {
    if (this->get_rows() != other.get_rows() || this->get_columns() != other.get_columns())
        throw std::invalid_argument("add: sizes must match");

    auto* result = new SparseMatrix<T>(this->get_rows(), this->get_columns());

    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_columns(); j++) {
            result->set(this->get(i, j) + other.get(i, j), i, j);
        }
    }

    return result;
}

template<class T>
SparseMatrix<T>* SparseMatrix<T>::multiply_scalar(const T& scalar) const {
    auto *result = new SparseMatrix<T>(this->get_rows(), this->get_columns());

    if (scalar == T(0))
        return result;

    for (int k = 0; k < data.get_size(); k++) {
        const Element<T>& e = data.get(k);

        result->set(e.value * scalar, e.i, e.j);
    }

    return result;
}

// private function
template<class T>
int SparseMatrix<T>::bin_search(int i, int j) const {
    int left = 0;
    int right = data.get_size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        const Element<T>& e = data.get(mid);

        if (e.i == i && e.j == j)
            return mid;

        if (e.i < i || (e.i == i && e.j < j))
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

template<class T>
int SparseMatrix<T>::lower_bound(int i, int j) const {
    int left = 0;
    int right = data.get_size();

    while (left < right)
    {
        int mid = (left + right) / 2;

        const Element<T>& e = data.get(mid);

        if (e.i < i || (e.i == i && e.j < j))
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}
#endif //LABA3_SPARSE_MATRIX_H
