#include <gtest/gtest.h>
#include "diagonal_matrix.h"

// ====================== POSITIVE ======================

// создание
TEST(DiagonalMatrixTest, CreateAndSize) {
    DiagonalMatrix<double> m(3);

    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_columns(), 3);
}

// set / get диагонали
TEST(DiagonalMatrixTest, SetGetDiagonal) {
    DiagonalMatrix<double> m(3);

    m.set(5, 1, 1);

    EXPECT_DOUBLE_EQ(m.get(1,1), 5);
}

// вне диагонали → 0
TEST(DiagonalMatrixTest, GetOutsideDiagonalIsZero) {
    DiagonalMatrix<double> m(3);

    m.set(7, 1, 1);

    EXPECT_DOUBLE_EQ(m.get(0,1), 0);
    EXPECT_DOUBLE_EQ(m.get(2,1), 0);
}

// умножение на скаляр
TEST(DiagonalMatrixTest, MultiplyScalar) {
    DiagonalMatrix<double> m(3);

    m.set(2,0,0);
    m.set(3,1,1);

    auto* res = m.multiply_scalar(2);

    EXPECT_DOUBLE_EQ(res->get(0,0), 4);
    EXPECT_DOUBLE_EQ(res->get(1,1), 6);

    delete res;
}

// норма
TEST(DiagonalMatrixTest, Norm) {
    DiagonalMatrix<double> m(2);

    m.set(3,0,0);
    m.set(4,1,1);

    EXPECT_NEAR(m.norm(), 5.0, 1e-6); // sqrt(9+16)
}

// сложение → SquareMatrix
TEST(DiagonalMatrixTest, AddMatrices) {
    DiagonalMatrix<double> a(2);
    DiagonalMatrix<double> b(2);

    a.set(1,0,0);
    b.set(2,0,0);

    SquareMatrix<double>* res = a.add(b);

    EXPECT_DOUBLE_EQ(res->get(0,0), 3);
    EXPECT_DOUBLE_EQ(res->get(1,1), 0);

    delete res;
}

// ====================== NEGATIVE ======================

// выход за границы
TEST(DiagonalMatrixTest, OutOfRange) {
    DiagonalMatrix<double> m(2);

    EXPECT_THROW(m.get(-1,0), std::out_of_range);
    EXPECT_THROW(m.set(1,10,10), std::out_of_range);
}

// попытка записать вне диагонали
TEST(DiagonalMatrixTest, SetOutsideDiagonal) {
    DiagonalMatrix<double> m(3);

    EXPECT_THROW(m.set(5, 0, 1), std::invalid_argument);
}

// сложение разных размеров
TEST(DiagonalMatrixTest, AddDifferentSizes) {
    DiagonalMatrix<double> a(2);
    DiagonalMatrix<double> b(3);

    EXPECT_THROW(a.add(b), std::invalid_argument);
}

// некорректный размер
TEST(DiagonalMatrixTest, InvalidSize) {
    EXPECT_THROW(DiagonalMatrix<double>(-1), std::invalid_argument);
}

// не хранит элементы вне диагонали
TEST(DiagonalMatrixTest, DiagonalOnlyStorageBehavior) {
    DiagonalMatrix<double> m(3);

    m.set(5,1,1);

    EXPECT_DOUBLE_EQ(m.get(1,1), 5);
    EXPECT_DOUBLE_EQ(m.get(1,2), 0);
    EXPECT_DOUBLE_EQ(m.get(2,1), 0);
}