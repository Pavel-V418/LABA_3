#include <gtest/gtest.h>
#include "sparse_matrix.h"

// ====================== POSITIVE ======================

// создание
TEST(SparseMatrixTest, CreateAndSize) {
    SparseMatrix<double> m(3, 4);

    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_columns(), 4);
}

// неустановленные элементы = 0
TEST(SparseMatrixTest, GetUnsetElementReturnsZero) {
    SparseMatrix<double> m(3, 3);

    EXPECT_DOUBLE_EQ(m.get(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(m.get(1, 2), 0.0);
    EXPECT_DOUBLE_EQ(m.get(2, 1), 0.0);
}

// set/get
TEST(SparseMatrixTest, SetAndGetElement) {
    SparseMatrix<double> m(3, 3);

    m.set(5.5, 1, 2);

    EXPECT_DOUBLE_EQ(m.get(1, 2), 5.5);
    EXPECT_DOUBLE_EQ(m.get(0, 0), 0.0);
}

// обновление существующего элемента
TEST(SparseMatrixTest, UpdateExistingElement) {
    SparseMatrix<double> m(3, 3);

    m.set(5.5, 1, 2);
    m.set(7.25, 1, 2);

    EXPECT_DOUBLE_EQ(m.get(1, 2), 7.25);
}

// удаление элемента через установку 0
TEST(SparseMatrixTest, SetZeroRemovesElementSemantics) {
    SparseMatrix<double> m(3, 3);

    m.set(5.5, 1, 2);
    EXPECT_DOUBLE_EQ(m.get(1, 2), 5.5);

    m.set(0.0, 1, 2);
    EXPECT_DOUBLE_EQ(m.get(1, 2), 0.0);
}

// сложение
TEST(SparseMatrixTest, AddMatrices) {
    SparseMatrix<double> a(2, 2);
    SparseMatrix<double> b(2, 2);

    a.set(1.0, 0, 0);
    a.set(2.0, 0, 1);
    a.set(3.0, 1, 0);

    b.set(4.0, 0, 0);
    b.set(5.0, 1, 1);

    SparseMatrix<double>* res = a.add(b);

    EXPECT_DOUBLE_EQ(res->get(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(res->get(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(res->get(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(res->get(1, 1), 5.0);

    delete res;
}

// умножение на скаляр
TEST(SparseMatrixTest, MultiplyScalar) {
    SparseMatrix<double> m(2, 2);

    m.set(1.0, 0, 0);
    m.set(-2.0, 0, 1);
    m.set(3.0, 1, 0);

    SparseMatrix<double>* res = m.multiply_scalar(2.0);

    EXPECT_DOUBLE_EQ(res->get(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(res->get(0, 1), -4.0);
    EXPECT_DOUBLE_EQ(res->get(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(res->get(1, 1), 0.0);

    delete res;
}

// умножение на 0 (должна получиться нулевая матрица)
TEST(SparseMatrixTest, MultiplyScalarByZero) {
    SparseMatrix<double> m(2, 2);

    m.set(1.0, 0, 0);
    m.set(2.0, 1, 1);

    SparseMatrix<double>* res = m.multiply_scalar(0.0);

    EXPECT_DOUBLE_EQ(res->get(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(res->get(1, 1), 0.0);
    EXPECT_DOUBLE_EQ(res->get(0, 1), 0.0);

    delete res;
}

// норма
TEST(SparseMatrixTest, Norm) {
    SparseMatrix<double> m(2, 2);

    m.set(3.0, 0, 0);
    m.set(4.0, 1, 1);

    EXPECT_NEAR(m.norm(), 5.0, 1e-6); // sqrt(3^2 + 4^2)
}

// ====================== NEGATIVE ======================

// выход за границы при get
TEST(SparseMatrixTest, OutOfRangeGet) {
    SparseMatrix<double> m(2, 2);

    EXPECT_THROW(m.get(-1, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, -1), std::out_of_range);
    EXPECT_THROW(m.get(2, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, 2), std::out_of_range);
}

// выход за границы при set
TEST(SparseMatrixTest, OutOfRangeSet) {
    SparseMatrix<double> m(2, 2);

    EXPECT_THROW(m.set(1.0, -1, 0), std::out_of_range);
    EXPECT_THROW(m.set(1.0, 0, -1), std::out_of_range);
    EXPECT_THROW(m.set(1.0, 2, 0), std::out_of_range);
    EXPECT_THROW(m.set(1.0, 0, 2), std::out_of_range);
}

// сложение матриц разного размера
TEST(SparseMatrixTest, AddDifferentSizes) {
    SparseMatrix<double> a(2, 2);
    SparseMatrix<double> b(3, 3);

    EXPECT_THROW(a.add(b), std::invalid_argument);
}

// некорректный размер
TEST(SparseMatrixTest, InvalidSize) {
    EXPECT_THROW(SparseMatrix<double>(-1, 2), std::out_of_range);
    EXPECT_THROW(SparseMatrix<double>(2, -1), std::out_of_range);
}