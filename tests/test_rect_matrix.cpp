#include <gtest/gtest.h>
#include "../rectangle_matrix.h"
#include "../vector.h"

// ====================== POSITIVE ======================

// Создание и размеры
TEST(RectangleMatrixTest, CreateAndSize) {
    RectangleMatrix<double> m(3, 4);

    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_columns(), 4);
}

// set / get
TEST(RectangleMatrixTest, SetAndGet) {
    RectangleMatrix<double> m(2, 2);

    m.set(5.0, 0, 0);
    m.set(3.0, 1, 1);

    EXPECT_DOUBLE_EQ(m.get(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(m.get(1, 1), 3.0);
}

// сложение
TEST(RectangleMatrixTest, AddMatrices) {
    RectangleMatrix<double> a(2, 2);
    RectangleMatrix<double> b(2, 2);

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
TEST(RectangleMatrixTest, MultiplyScalar) {
    RectangleMatrix<double> m(2, 2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    IMatrix<double>* res = m.multiply_scalar(2);

    EXPECT_DOUBLE_EQ(res->get(0,0), 2);
    EXPECT_DOUBLE_EQ(res->get(0,1), 4);
    EXPECT_DOUBLE_EQ(res->get(1,0), 6);
    EXPECT_DOUBLE_EQ(res->get(1,1), 8);

    delete res;
}

// норма
TEST(RectangleMatrixTest, Norm) {
    RectangleMatrix<double> m(2, 2);

    m.set(1,0,0);
    m.set(2,0,1);
    m.set(3,1,0);
    m.set(4,1,1);

    // sqrt(1+4+9+16) = sqrt(30)
    EXPECT_NEAR(m.norm(), std::sqrt(30.0), 1e-6);
}

// элементарные преобразования

TEST(RectangleMatrixTest, SwapRowsBasic) {
    RectangleMatrix<double> m(2, 2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    m.swap_rows(0, 1);

    EXPECT_DOUBLE_EQ(m.get(0,0), 3);
    EXPECT_DOUBLE_EQ(m.get(0,1), 4);
    EXPECT_DOUBLE_EQ(m.get(1,0), 1);
    EXPECT_DOUBLE_EQ(m.get(1,1), 2);
}

// swap одинаковой строки (ничего не меняется)
TEST(RectangleMatrixTest, SwapRowsSameRow) {
    RectangleMatrix<double> m(2, 2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    m.swap_rows(0, 0);

    EXPECT_DOUBLE_EQ(m.get(0,0), 1);
    EXPECT_DOUBLE_EQ(m.get(1,0), 3);
}

TEST(RectangleMatrixTest, MultiplyRowBasic) {
    RectangleMatrix<double> m(2, 2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    m.multiply_rows(0, 2);

    EXPECT_DOUBLE_EQ(m.get(0,0), 2);
    EXPECT_DOUBLE_EQ(m.get(0,1), 4);

    // вторая строка не изменилась
    EXPECT_DOUBLE_EQ(m.get(1,0), 3);
    EXPECT_DOUBLE_EQ(m.get(1,1), 4);
}

// умножение на 0
TEST(RectangleMatrixTest, MultiplyRowByZero) {
    RectangleMatrix<double> m(2, 2);

    m.set(5,0,0); m.set(6,0,1);

    m.multiply_rows(0, 0);

    EXPECT_DOUBLE_EQ(m.get(0,0), 0);
    EXPECT_DOUBLE_EQ(m.get(0,1), 0);
}

TEST(RectangleMatrixTest, AddRowBasic) {
    RectangleMatrix<double> m(2, 2);

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
TEST(RectangleMatrixTest, AddRowWithZeroScalar) {
    RectangleMatrix<double> m(2, 2);

    m.set(5,0,0); m.set(6,0,1);
    m.set(7,1,0); m.set(8,1,1);

    m.add_row(0, 1, 0);

    EXPECT_DOUBLE_EQ(m.get(0,0), 5);
    EXPECT_DOUBLE_EQ(m.get(0,1), 6);
}

// ====================== NEGATIVE ======================

// выход за границы set
TEST(RectangleMatrixTest, SetOutOfRange) {
    RectangleMatrix<double> m(2, 2);

    EXPECT_THROW(m.set(5, -1, 0), std::out_of_range);
    EXPECT_THROW(m.set(5, 0, -1), std::out_of_range);
    EXPECT_THROW(m.set(5, 5, 0), std::out_of_range);
    EXPECT_THROW(m.set(5, 0, 5), std::out_of_range);
}

// выход за границы get
TEST(RectangleMatrixTest, GetOutOfRange) {
    RectangleMatrix<double> m(2, 2);

    EXPECT_THROW(m.get(-1, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, -1), std::out_of_range);
    EXPECT_THROW(m.get(5, 0), std::out_of_range);
    EXPECT_THROW(m.get(0, 5), std::out_of_range);
}

// сложение разных размеров
TEST(RectangleMatrixTest, AddDifferentSizes) {
    RectangleMatrix<double> a(2, 2);
    RectangleMatrix<double> b(3, 3);

    EXPECT_THROW(a.add(b), std::invalid_argument);
}

// некорректный размер при создании
TEST(RectangleMatrixTest, InvalidSize) {
    EXPECT_THROW(RectangleMatrix<double>(-1, 2), std::invalid_argument);
    EXPECT_THROW(RectangleMatrix<double>(2, -1), std::invalid_argument);
}

// умножение на вектор (несовпадение размеров)

TEST(RectangleMatrixTest, MatrixVectorMismatch) {
    RectangleMatrix<double> m(2, 3);
    Vector<double> v(2);

    EXPECT_THROW(m * v, std::invalid_argument);
}

// выход за границы (swap)
TEST(RectangleMatrixTest, SwapRowsOutOfRange) {
    RectangleMatrix<double> m(2, 2);

    EXPECT_THROW(m.swap_rows(-1, 0), std::out_of_range);
    EXPECT_THROW(m.swap_rows(0, 5), std::out_of_range);
}

// выход за границы (mult)
TEST(RectangleMatrixTest, MultiplyRowOutOfRange) {
    RectangleMatrix<double> m(2, 2);

    EXPECT_THROW(m.multiply_rows(-1, 2), std::out_of_range);
    EXPECT_THROW(m.multiply_rows(10, 2), std::out_of_range);
}

// выход за границы (add row)
TEST(RectangleMatrixTest, AddRowOutOfRange) {
    RectangleMatrix<double> m(2, 2);

    EXPECT_THROW(m.add_row(-1, 0, 1), std::out_of_range);
    EXPECT_THROW(m.add_row(0, 5, 1), std::out_of_range);
}