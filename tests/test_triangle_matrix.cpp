#include <gtest/gtest.h>
#include "triangle_matrix.h"

// ====================== POSITIVE ======================

// создание lower
TEST(TriangleMatrixTest, CreateLower) {
    TriangleMatrix<double> m(3, TriangleType::lower_triangle);

    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_columns(), 3);
}

// создание upper
TEST(TriangleMatrixTest, CreateUpper) {
    TriangleMatrix<double> m(3, TriangleType::upper_triangle);

    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_columns(), 3);
}

// set/get lower
TEST(TriangleMatrixTest, SetGetLower) {
    TriangleMatrix<double> m(3, TriangleType::lower_triangle);

    m.set(5, 2, 1);

    EXPECT_DOUBLE_EQ(m.get(2,1), 5);
}

// set/get upper
TEST(TriangleMatrixTest, SetGetUpper) {
    TriangleMatrix<double> m(3, TriangleType::upper_triangle);

    m.set(7, 1, 2);

    EXPECT_DOUBLE_EQ(m.get(1,2), 7);
}

// get вне треугольника → 0
TEST(TriangleMatrixTest, GetOutsideTriangleReturnsZero) {
    TriangleMatrix<double> lower(3, TriangleType::lower_triangle);
    TriangleMatrix<double> upper(3, TriangleType::upper_triangle);

    EXPECT_DOUBLE_EQ(lower.get(0,2), 0); // выше диагонали
    EXPECT_DOUBLE_EQ(upper.get(2,0), 0); // ниже диагонали
}

// умножение на скаляр
TEST(TriangleMatrixTest, MultiplyScalar) {
    TriangleMatrix<double> m(3, TriangleType::lower_triangle);

    m.set(2,2,0);
    m.set(3,2,1);

    auto* res = m.multiply_scalar(2);

    EXPECT_DOUBLE_EQ(res->get(2,0), 4);
    EXPECT_DOUBLE_EQ(res->get(2,1), 6);

    delete res;
}

// норма
TEST(TriangleMatrixTest, Norm) {
    TriangleMatrix<double> m(2, TriangleType::lower_triangle);

    m.set(3,0,0);
    m.set(4,1,0);
    m.set(0,1,1);

    // sqrt(9 + 16 + 0)
    EXPECT_NEAR(m.norm(), 5.0, 1e-6);
}

// сложение (результат square)
TEST(TriangleMatrixTest, AddMatrices) {
    TriangleMatrix<double> a(2, TriangleType::lower_triangle);
    TriangleMatrix<double> b(2, TriangleType::lower_triangle);

    a.set(1,0,0);
    a.set(2,1,0);

    b.set(3,0,0);
    b.set(4,1,0);

    SquareMatrix<double>* res = a.add(b);

    EXPECT_DOUBLE_EQ(res->get(0,0), 4);
    EXPECT_DOUBLE_EQ(res->get(1,0), 6);

    delete res;
}

// ====================== NEGATIVE ======================

// выход за границы
TEST(TriangleMatrixTest, OutOfRange) {
    TriangleMatrix<double> m(2, TriangleType::lower_triangle);

    EXPECT_THROW(m.get(-1,0), std::out_of_range);
    EXPECT_THROW(m.set(1, 10, 10), std::out_of_range);
}

// нарушение формы lower
TEST(TriangleMatrixTest, SetInvalidLower) {
    TriangleMatrix<double> m(3, TriangleType::lower_triangle);

    EXPECT_THROW(m.set(5, 0, 2), std::out_of_range); // выше диагонали
}

// нарушение формы upper
TEST(TriangleMatrixTest, SetInvalidUpper) {
    TriangleMatrix<double> m(3, TriangleType::upper_triangle);

    EXPECT_THROW(m.set(5, 2, 0), std::out_of_range); // ниже диагонали
}

// сложение разных размеров
TEST(TriangleMatrixTest, AddDifferentSizes) {
    TriangleMatrix<double> a(2, TriangleType::lower_triangle);
    TriangleMatrix<double> b(3, TriangleType::lower_triangle);

    EXPECT_THROW(a.add(b), std::invalid_argument);
}

// некорректный размер
TEST(TriangleMatrixTest, InvalidSize) {
    EXPECT_THROW(TriangleMatrix<double>(-1, TriangleType::lower_triangle), std::invalid_argument);
}

// элементы вне треугольника не хранятся и равны 0
TEST(TriangleMatrixTest, UpperLowerBehaviorDifference) {
    TriangleMatrix<double> lower(3, TriangleType::lower_triangle);
    TriangleMatrix<double> upper(3, TriangleType::upper_triangle);

    lower.set(5,2,0);
    upper.set(7,0,2);

    EXPECT_DOUBLE_EQ(lower.get(0,2), 0);
    EXPECT_DOUBLE_EQ(upper.get(2,0), 0);
}