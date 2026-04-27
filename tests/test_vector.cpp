#include <gtest/gtest.h>
#include "vector.h"
#include "rectangle_matrix.h"

// ====================== POSITIVE ======================

// создание и размер
TEST(VectorTest, CreateAndSize) {
    Vector<double> v(3);

    EXPECT_EQ(v.get_size(), 3);
}

// set / get
TEST(VectorTest, SetAndGet) {
    Vector<double> v(3);

    v.set(5.0, 1);

    EXPECT_DOUBLE_EQ(v.get(1), 5.0);
}

// operator []
TEST(VectorTest, OperatorAccess) {
    Vector<double> v(3);

    v.set(10.0, 2);

    EXPECT_DOUBLE_EQ(v[2], 10.0);
}

// сложение векторов
TEST(VectorTest, AddVectors) {
    Vector<double> a(3);
    Vector<double> b(3);

    for (int i = 0; i < 3; i++) {
        a.set(i + 1, i);     // 1 2 3
        b.set(10 + i, i);    // 10 11 12
    }

    Vector<double> res = a + b;

    EXPECT_DOUBLE_EQ(res.get(0), 11);
    EXPECT_DOUBLE_EQ(res.get(1), 13);
    EXPECT_DOUBLE_EQ(res.get(2), 15);
}

// вычитание
TEST(VectorTest, SubtractVectors) {
    Vector<double> a(3);
    Vector<double> b(3);

    for (int i = 0; i < 3; i++) {
        a.set(5 + i, i);
        b.set(1, i);
    }

    Vector<double> res = a - b;

    EXPECT_DOUBLE_EQ(res.get(0), 4);
    EXPECT_DOUBLE_EQ(res.get(1), 5);
    EXPECT_DOUBLE_EQ(res.get(2), 6);
}

// умножение на скаляр
TEST(VectorTest, MultiplyScalar) {
    Vector<double> v(3);

    v.set(1,0); v.set(2,1); v.set(3,2);

    Vector<double> res = v * 2;

    EXPECT_DOUBLE_EQ(res.get(0), 2);
    EXPECT_DOUBLE_EQ(res.get(1), 4);
    EXPECT_DOUBLE_EQ(res.get(2), 6);
}

// скалярное произведение
TEST(VectorTest, DotProduct) {
    Vector<double> a(3);
    Vector<double> b(3);

    a.set(1,0); a.set(2,1); a.set(3,2);
    b.set(4,0); b.set(5,1); b.set(6,2);

    double res = a.dot(b);

    EXPECT_DOUBLE_EQ(res, 32); // 1*4 + 2*5 + 3*6
}

// норма
TEST(VectorTest, Norm) {
    Vector<double> v(2);

    v.set(3,0);
    v.set(4,1);

    EXPECT_NEAR(v.norm(), 5.0, 1e-6);
}

// матрица * вектор
TEST(VectorTest, MatrixVectorMultiply) {
    RectangleMatrix<double> m(2,2);
    Vector<double> v(2);

    m.set(1,0,0); m.set(2,0,1);
    m.set(3,1,0); m.set(4,1,1);

    v.set(1,0); v.set(1,1);

    Vector<double> res = m * v;

    EXPECT_DOUBLE_EQ(res.get(0), 3); // 1+2
    EXPECT_DOUBLE_EQ(res.get(1), 7); // 3+4
}

// ====================== NEGATIVE ======================

// выход за границы get/set
TEST(VectorTest, OutOfRange) {
    Vector<double> v(2);

    EXPECT_THROW(v.get(-1), std::out_of_range);
    EXPECT_THROW(v.get(10), std::out_of_range);
    EXPECT_THROW(v.set(1, -1), std::out_of_range);
    EXPECT_THROW(v.set(1, 10), std::out_of_range);
}

// сложение разных размеров
TEST(VectorTest, AddDifferentSizes) {
    Vector<double> a(2);
    Vector<double> b(3);

    EXPECT_THROW(a + b, std::invalid_argument);
}

// вычитание разных размеров
TEST(VectorTest, SubDifferentSizes) {
    Vector<double> a(2);
    Vector<double> b(3);

    EXPECT_THROW(a - b, std::invalid_argument);
}

// dot product разных размеров
TEST(VectorTest, DotDifferentSizes) {
    Vector<double> a(2);
    Vector<double> b(3);

    EXPECT_THROW(a.dot(b), std::invalid_argument);
}

// matrix * vector mismatch
TEST(VectorTest, MatrixVectorMismatch) {
    RectangleMatrix<double> m(2,3);
    Vector<double> v(2);

    EXPECT_THROW(m * v, std::invalid_argument);
}

// некорректный размер
TEST(VectorTest, InvalidSize) {
    EXPECT_THROW(Vector<double>(-1), std::invalid_argument);
}