#ifndef LABA3_TRIANGLE_MATRIX_H
#define LABA3_TRIANGLE_MATRIX_H

#include "square_matrix.h"
#include "LABA_2/dynamicArray.h"

enum class TriangleType {
    lower_triangle,
    upper_triangle
};

template<class T>
class TriangleMatrix : public IMatrix<T>{

public:
    TriangleMatrix(TriangleType type);
    TriangleMatrix(int n, TriangleType type);
    TriangleMatrix(T *items, int n, TriangleType type);
    TriangleMatrix(const TriangleMatrix<T>& other);

    ~TriangleMatrix() override = default;

    const T& get(int row, int column) const override;

    int get_rows() const override;
    int get_columns() const override;

    double norm() const override; // проверить, надо ли менять

    void set(const T& value, int row, int column) override;

    SquareMatrix<T>* add(const IMatrix<T>& other) const override;
    TriangleMatrix<T>* multiply_scalar(const T& scalar) const override;


private:
    DynamicArray<T> data; // хранит только значения в треугольнике выбранного типа
    int n; // матрица квадратная
    TriangleType type;

    static inline const T zero{}; // живет всю программу

    static int check_size(int n);
    bool check_range(int row,int column) const;

    int triangle_index(int row, int column) const; // тип треугольника
};

template<class T>
TriangleMatrix<T>::TriangleMatrix(TriangleType type)
    : data(0), n(0), type(type) {}

template<class T>
TriangleMatrix<T>::TriangleMatrix(int n, TriangleType type)
    : data(check_size(n)), n(n), type(type) {}

template<class T>
TriangleMatrix<T>::TriangleMatrix(T *items, int n, TriangleType type)
    : data(items, check_size(n)), n(n), type(type) {}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix<T> &other)
    : data(other.data), n(other.n), type(other.type) {}

// геттеры
template<class T>
const T& TriangleMatrix<T>::get(int row, int column) const {
    if (! check_range(row, column))
        throw std::out_of_range("Index out of range");

    if (type == TriangleType::upper_triangle && row > column)
        return zero;

    if (type == TriangleType::lower_triangle && column > row)
        return zero;

    return data.get(triangle_index(row, column)); // правки
}

template<class T>
int TriangleMatrix<T>::get_rows() const {
    return n;
}

template<class T>
int TriangleMatrix<T>::get_columns() const {
    return n;
}

template<class T>
void TriangleMatrix<T>::set(const T &value, int row, int column) {
    if (!check_range(row, column))
        throw std::out_of_range("Index out of range");

    if (type == TriangleType::upper_triangle && row > column)
        throw std::out_of_range("Index out of upper_triangle's range");

    if (type == TriangleType::lower_triangle && column > row)
        throw std::out_of_range("Index out of lower_triangle's range");

    data.set(value, triangle_index(row, column));
} // негативные тесты (матрицы разных типов,

template<class T>
double TriangleMatrix<T>::norm() const{
    double sum = 0;

    if (type == TriangleType::upper_triangle) {
        for (int i = 0; i < this->get_rows(); i++) {
            for (int j = i; j < this->get_rows(); j++) {
                using std::abs;
                auto value = static_cast<double>(abs(this->get(i, j)));
                sum += value * value;
            }
        } // type upper
    }
    else {
        for (int i = 0; i < this->get_rows(); i++){
            for (int j = 0; j <= i; j++) {
                using std::abs;
                auto value = static_cast<double>(abs(this->get(i, j)));
                sum += value * value;
            }
        } // type lower
    }

    return std::sqrt(sum);
}

template<class T>
SquareMatrix<T>* TriangleMatrix<T>::add(const IMatrix<T>& other) const {

    if (this->get_rows() != other.get_rows() || this->get_columns() != other.get_columns())
        throw std::invalid_argument("Matrix size must match");

    auto *result = new SquareMatrix<T>(this->get_rows());

    for (int i = 0; i < this->get_rows(); i++) {
        for (int j = 0; j < this->get_columns(); j++)
            result->set(this->get(i, j) + other.get(i, j), i, j);
    }

    return result;
}

template<class T>
TriangleMatrix<T>* TriangleMatrix<T>::multiply_scalar(const T& scalar) const {
    int size = data.get_size();

    auto* result = new TriangleMatrix<T>(*this); // копия

    for (int i = 0; i < size; i++) {
        result->data.set(this->data.get(i) * scalar, i);
    }

    return result;
}

// private functions

template<class T>
int TriangleMatrix<T>::triangle_index(int row, int column) const {
    if (type == TriangleType::lower_triangle)
        return row * (row + 1) / 2 + column;

    if (type == TriangleType::upper_triangle)
        return row * this->get_rows() - row * (row - 1) / 2 + (column - row);

    throw std::logic_error("Invalid triangle type");
}

template<class T>
int TriangleMatrix<T>::check_size(int n) {
    if (n < 0)
        throw std::invalid_argument("Matrix's size must be positive");
    return n * (n + 1) / 2;
}

template<class T>
bool TriangleMatrix<T>::check_range(int row, int column) const {
    return row >= 0 && column >= 0 && row < this->get_rows() && column < this->get_columns();
}


#endif //LABA3_TRIANGLE_MATRIX_H
