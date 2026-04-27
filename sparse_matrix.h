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

    int compare(int i, int j) const {
        if (row < i) return -1;
        if (row > i) return 1;

        if (column < j) return -1;
        if (column > j) return 1;

        return 0; // равны
    }
};

// большинство элементов равны 0, но мы их хранить не будем
template<class T>
class SparseMatrix : public IMatrix<T>{

public:
    SparseMatrix();
    SparseMatrix(int row, int column);
    SparseMatrix(T *items, int row, int column, int count);
    SparseMatrix(const SparseMatrix& other);

    ~SparseMatrix() override = default;

    const T& get(int row, int column) const override;

    int get_rows() const override;
    int get_columns() const override;

    double norm() const override;

    void set(const T& value, int row, int column) override;

    SparseMatrix<T>* add(const IMatrix<T>& other) const override;
    SparseMatrix<T>* multiply_scalar(const T& scalar) const override;

private:
    DynamicArray<Element<T>> data; // храним всё, кроме нулей
    int rows;
    int columns;

    int bin_search(int row, int column) const; // бинарный поиск элемента (i,j)
    int lower_bound(int row, int column) const; // поиск нижней границы для вставки элемента

    static int check_size(int row, int column);
    void check_range(int row, int column) const;

    static inline const T zero{};
};
// добавить проверку(см гитхаб)
template<class T>
SparseMatrix<T>::SparseMatrix()
    : data(0), rows(0), columns(0) {}

template<class T>
SparseMatrix<T>::SparseMatrix(int row, int column)
    : data(0), rows(row), columns(column)
{
    check_size(row, column);
}

template<class T>
SparseMatrix<T>::SparseMatrix(T *items, int row, int column, int count)
: data(items, count), rows(row), columns(column)
{
    check_size(row, column);
}

template<class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix &other)
    : data(other.data), rows(other.rows), columns(other.columns) {}

template<class T>
const T& SparseMatrix<T>::get(int row, int column) const {
    check_range(row, column);

    for (int k = 0; k < data.get_size(); k++) {

        if (data.get(k).row == row && data.get(k).column == column)
            return data.get(k).value;
    }

    return zero; // если не нашли элемент, то это 0
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
        using std::abs;
        auto value = static_cast<double>(abs(data.get(k).value));
        sum += value * value;
    }

    return std::sqrt(sum);
}

template<class T>
void SparseMatrix<T>::set(const T& value, int row, int column){
    check_range(row, column);

    int index = bin_search(row, column);

    // элемент найден
    if (index != -1) {
        if (value == zero){
            data.remove_at(index);
        }

        else{
            data.set(Element<T>{row, column, value}, index);
        }
        return;
    }

    // элемент НЕ найден
    if (value == zero)
        return;

    int pos = lower_bound(row, column);

    data.resize(data.get_size() + 1);

    // сдвиг элементов вправо
    for (int k = data.get_size() - 1; k > pos; k--){
        data.set(data.get(k - 1), k);
    }

    data.set(Element<T>{row, column, value}, pos);
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

    if (scalar == zero)
        return result;

    for (int k = 0; k < data.get_size(); k++) {
        const Element<T>& element = data.get(k);

        result->set(element.value * scalar, element.row, element.column);
    }

    return result;
}

// private function
template<class T>
int SparseMatrix<T>::bin_search(int row, int column) const {
    int left = 0;
    int right = data.get_size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        const Element<T>& element = data.get(mid);

        if (element.compare(row, column) == 0)
            return mid;

        if (element.compare(row, column) < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

template<class T>
int SparseMatrix<T>::lower_bound(int row, int column) const {
    int left = 0;
    int right = data.get_size();

    while (left < right)
    {
        int mid = (left + right) / 2;

        const Element<T>& element = data.get(mid);

        if (element.compare(row,column) < 0)
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}

template<class T>
int SparseMatrix<T>::check_size(int row, int column) {
    if (row < 0 || column < 0)
        throw std::out_of_range("index out of range");

    return row * column;
}

template<class T>
void SparseMatrix<T>::check_range(int row, int column) const {
    if (row < 0 || column < 0 || row >= this->get_rows() || column >= this->get_columns())
        throw std::out_of_range("Index out of range");
}
#endif //LABA3_SPARSE_MATRIX_H
