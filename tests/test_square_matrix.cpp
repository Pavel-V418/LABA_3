#include <gtest/gtest.h>
#include "square_matrix.h"

// ====================== POSITIVE ======================

// создание
TEST(SquareMatrixTest, CreateAndSize) {
    SquareMatrix<double> m(3);

    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_columns(), 3);
}

// set / get
TEST(SquareMatrixTest, SetAndGet) {
    SquareMatrix<double> m(2);

    m.set(5, 0, 0);
    m.set(7, 1, 1);

    EXPECT_DOUBLE_EQ(m.get(0,0), 5);
    EXPECT_DOUBLE_EQ(m.get(1,1), 7);
}

// сложение
TEST(SquareMatrixTest, AddMatrices) {
    SquareMatrix<double> a(2);
    SquareMatrix<double> b(2);

    a.set(1,0,0); a.set(2,0,1);
    a.set(3,1,0); a.set(4,1,1);

    b.set(5,0,0); b.set(6,0,1);
    b.set(7,1,0); b.set(8,1,1);

    IMatrix<double>* res = a.add(b);

    EXPECT_DOUBLE_EQ(res->get(0,0), 6);
    EXPECT_DOUBLE_EQ(res->get(0,1), 8);
    EXPECT_DOUBLE_EQ(res->get(1,0), 10);
    EXPECT_DOUBLE_EQ(res->get(1,1), 12);

    delete res;
}

// умножение на скаляр
TEST(SquareMatrixTest, MultiplyScalar) {
    SquareMatrix<double> m(2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    IMatrix<double>* res = m.multiply_scalar(3);

    EXPECT_DOUBLE_EQ(res->get(0,0), 3);
    EXPECT_DOUBLE_EQ(res->get(0,1), 6);
    EXPECT_DOUBLE_EQ(res->get(1,0), 9);
    EXPECT_DOUBLE_EQ(res->get(1,1), 12);

    delete res;
}

// норма
TEST(SquareMatrixTest, Norm) {
    SquareMatrix<double> m(2);

    m.set(1,0,0);
    m.set(2,0,1);
    m.set(3,1,0);
    m.set(4,1,1);

    EXPECT_NEAR(m.norm(), std::sqrt(30.0), 1e-6);
}

TEST(SquareMatrixTest, SwapRowsBasic) {
    SquareMatrix<double> m(2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    m.swap_rows(0, 1);

    EXPECT_DOUBLE_EQ(m.get(0,0), 3);
    EXPECT_DOUBLE_EQ(m.get(0,1), 4);
    EXPECT_DOUBLE_EQ(m.get(1,0), 1);
    EXPECT_DOUBLE_EQ(m.get(1,1), 2);
}

// swap одинаковой строки
TEST(SquareMatrixTest, SwapRowsSameRow) {
    SquareMatrix<double> m(2);

    m.set(5,0,0); m.set(6,0,1);
    m.set(7,1,0); m.set(8,1,1);

    m.swap_rows(1, 1);

    EXPECT_DOUBLE_EQ(m.get(1,0), 7);
    EXPECT_DOUBLE_EQ(m.get(1,1), 8);
}

TEST(SquareMatrixTest, MultiplyRowBasic) {
    SquareMatrix<double> m(2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    m.multiply_rows(0, 3);

    EXPECT_DOUBLE_EQ(m.get(0,0), 3);
    EXPECT_DOUBLE_EQ(m.get(0,1), 6);

    // другая строка не меняется
    EXPECT_DOUBLE_EQ(m.get(1,0), 3);
    EXPECT_DOUBLE_EQ(m.get(1,1), 4);
}

// умножение на 0
TEST(SquareMatrixTest, MultiplyRowByZero) {
    SquareMatrix<double> m(2);

    m.set(5,0,0); m.set(6,0,1);

    m.multiply_rows(0, 0);

    EXPECT_DOUBLE_EQ(m.get(0,0), 0);
    EXPECT_DOUBLE_EQ(m.get(0,1), 0);
}

TEST(SquareMatrixTest, AddRowBasic) {
    SquareMatrix<double> m(2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    // row0 = row0 + 2 * row1
    m.add_row(0, 1, 2);

    EXPECT_DOUBLE_EQ(m.get(0,0), 1 + 2*3);
    EXPECT_DOUBLE_EQ(m.get(0,1), 2 + 2*4);

    // row1 не меняется
    EXPECT_DOUBLE_EQ(m.get(1,0), 3);
    EXPECT_DOUBLE_EQ(m.get(1,1), 4);
}

// scalar = 0 → строка не меняется
TEST(SquareMatrixTest, AddRowWithZeroScalar) {
    SquareMatrix<double> m(2);

    m.set(5,0,0); m.set(6,0,1);
    m.set(7,1,0); m.set(8,1,1);

    m.add_row(0, 1, 0);

    EXPECT_DOUBLE_EQ(m.get(0,0), 5);
    EXPECT_DOUBLE_EQ(m.get(0,1), 6);
}

// row1 == row2 (сам на себя)
TEST(SquareMatrixTest, AddRowSelf) {
    SquareMatrix<double> m(2);

    m.set(2,0,0); m.set(3,0,1);

    m.add_row(0, 0, 2); // row = row + 2*row = 3*row

    EXPECT_DOUBLE_EQ(m.get(0,0), 6);
    EXPECT_DOUBLE_EQ(m.get(0,1), 9);
}

// ====================== NEGATIVE ======================

// выход за границы set
TEST(SquareMatrixTest, SetOutOfRange) {
    SquareMatrix<double> m(2);

    EXPECT_THROW(m.set(5, -1, 0), std::out_of_range);
    EXPECT_THROW(m.set(5, 0, -1), std::out_of_range);
    EXPECT_THROW(m.set(5, 5, 0), std::out_of_range);
}

// выход за границы get
TEST(SquareMatrixTest, GetOutOfRange) {
    SquareMatrix<double> m(2);

    EXPECT_THROW(m.get(-1, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, -1), std::out_of_range);
    EXPECT_THROW(m.get(10, 10), std::out_of_range);
}

// сложение разных размеров
TEST(SquareMatrixTest, AddDifferentSizes) {
    SquareMatrix<double> a(2);
    SquareMatrix<double> b(3);

    EXPECT_THROW(a.add(b), std::invalid_argument);
}

// некорректный размер
TEST(SquareMatrixTest, InvalidSize) {
    EXPECT_THROW(SquareMatrix<double>(-1), std::invalid_argument);
}

// выход за границы (swap)
TEST(SquareMatrixTest, SwapRowsOutOfRange) {
    SquareMatrix<double> m(2);

    EXPECT_THROW(m.swap_rows(-1, 0), std::out_of_range);
    EXPECT_THROW(m.swap_rows(0, 5), std::out_of_range);
}

// выход за границы
TEST(SquareMatrixTest, MultiplyRowOutOfRange) {
    SquareMatrix<double> m(2);

    EXPECT_THROW(m.multiply_rows(-1, 2), std::out_of_range);
    EXPECT_THROW(m.multiply_rows(10, 2), std::out_of_range);
}

// выход за границы
TEST(SquareMatrixTest, AddRowOutOfRange) {
    SquareMatrix<double> m(2);

    EXPECT_THROW(m.add_row(-1, 0, 1), std::out_of_range);
    EXPECT_THROW(m.add_row(0, 5, 1), std::out_of_range);
}
