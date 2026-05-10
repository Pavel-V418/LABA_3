#ifndef LABA3_SYSTEMS_OF_EQUATIONS_H
#define LABA3_SYSTEMS_OF_EQUATIONS_H

#include <random>
#include "square_matrix.h"
#include "vector.h"

template<class T>
class SystemOfEquations {

public:
    SystemOfEquations(const SquareMatrix<T>& A, const Vector<T>& b);

    const SquareMatrix<T>& get_matrix() const;
    const Vector<T>& get_vector_free_coef() const; // vector of free coefficients
    int get_size() const;

    void set(const SquareMatrix<T>& new_A, const Vector<T>& new_b);
    void set_vector_free_coef(const Vector<T>& new_b);
    void set_matrix(const SquareMatrix<T>& new_A);

    Vector<T> gauss_with_pivot() const;
    Vector<T> gauss_without_pivot() const;

    Vector<T> solve_lu() const;

    double residual(const Vector<T>& x) const;

    static double relative_error( const Vector<T>& approx, const Vector<T>& exact);

    static SystemOfEquations<T> random(int n, unsigned seed = 67);
    static SystemOfEquations<T> hilbert(int n);

private:
    SquareMatrix<T> A;
    Vector<T> b;
    mutable SquareMatrix<T> L;
    mutable SquareMatrix<T> U;

    mutable bool lu_ready = false;

    void lu_decomposition() const;
    Vector<T> forward_substitution(const Vector<T>& rhs) const;
    Vector<T> backward_substitution(const Vector<T>& y) const;

    static void compare_sizes(const SquareMatrix<T>& A, const Vector<T>& b);

};

template<class T>
SystemOfEquations<T>::SystemOfEquations(const SquareMatrix<T>& A, const Vector<T>& b)
    : A(A), b(b), L(A.get_size()), U(A.get_size()), lu_ready(false){
    compare_sizes(A, b);
}

template<class T>
const SquareMatrix<T>& SystemOfEquations<T>::get_matrix() const {
    return A;
}

template<class T>
const Vector<T> &SystemOfEquations<T>::get_vector_free_coef() const {
    return b;
}

template<class T>
int SystemOfEquations<T>::get_size() const {
    return A.get_size();
}

template<class T>
void SystemOfEquations<T>::set(const SquareMatrix<T>& new_A, const Vector<T>& new_b) {
    compare_sizes(new_A, new_b);

    A = new_A;
    b = new_b;

    lu_ready = false;
}

template <typename T>
void SystemOfEquations<T>::set_matrix(const SquareMatrix<T>& new_A) {
    compare_sizes(new_A, b);

    A = new_A;
    lu_ready = false;
}

template<class T>
void SystemOfEquations<T>::set_vector_free_coef(const Vector<T>& new_b){
    compare_sizes(A, new_b);

    b = new_b;
}

template<class T>
Vector<T> SystemOfEquations<T>::gauss_with_pivot() const {
    SquareMatrix<T> A_copy = A;
    Vector<T> b_copy = b;

    int n = get_size();
    using std::abs;

    // прямой ход
    for (int k = 0; k < n; k++) {
        int index_max = k;

        // поиск максимального элемента
        for (int i = k + 1; i < n; i++) {
            if (abs(A_copy.get(i, k)) > abs(A_copy.get(index_max, k))) {
                index_max = i;
            }
        }

        // swap строк
        if (index_max != k) {
            A_copy.swap_rows(k, index_max);

            T tmp = b_copy.get(k);
            b_copy.set(b_copy.get(index_max), k);
            b_copy.set(tmp, index_max);
        }

        if (abs(A_copy.get(k, k)) < 1e-18)
            throw std::runtime_error("Zero pivot encountered");

        for (int i = k + 1; i < n; i++) {
            T ratio = A_copy.get(i, k) / A_copy.get(k, k);

            for (int j = k; j < n; j++) {
                T value = A_copy.get(i, j) - ratio * A_copy.get(k, j);
                A_copy.set(value, i, j);
            }

            b_copy.set(b_copy.get(i) - ratio * b_copy.get(k), i);
        }
    }

    // обратный ход
    Vector<T> x(n);

    for (int i = n - 1; i >= 0; i--) {
        T sum = T{};

        for (int j = i + 1; j < n; j++) {
            sum += A_copy.get(i, j) * x.get(j);
        }

        if (abs(A_copy.get(i, i)) < 1e-18)
            throw std::runtime_error("Zero on diagonal");

        x.set((b_copy.get(i) - sum) / A_copy.get(i, i), i);
    }

    return x;
}

template<class T>
Vector<T> SystemOfEquations<T>::gauss_without_pivot() const {
    SquareMatrix<T> A_copy = A;
    Vector<T> b_copy = b;

    int n = get_size();
    using std::abs;

    // прямой ход
    for (int k = 0; k < n; k++) {

        if (abs(A_copy.get(k, k)) < 1e-18)
            throw std::runtime_error("Zero pivot encountered");

        for (int i = k + 1; i < n; i++) {
            T ratio = A_copy.get(i, k) / A_copy.get(k, k);

            for (int j = k; j < n; j++) {
                T value = A_copy.get(i, j) - ratio * A_copy.get(k, j);
                A_copy.set(value, i, j);
            }

            b_copy.set(b_copy.get(i) - ratio * b_copy.get(k), i);
        }
    }

    // обратный ход
    Vector<T> x(n);

    for (int i = n - 1; i >= 0; i--) {
        T sum = T{};

        for (int j = i + 1; j < n; j++) {
            sum += A_copy.get(i, j) * x.get(j);
        }

        if (abs(A_copy.get(i, i)) < 1e-18)
            throw std::runtime_error("Zero on diagonal during back substitution");

        x.set((b_copy.get(i) - sum) / A_copy.get(i, i), i);
    }

    return x;
}

template<class T>
Vector<T> SystemOfEquations<T>::solve_lu() const {
    if (!lu_ready)
        lu_decomposition();

    Vector<T> y = forward_substitution(b);

    return backward_substitution(y);
}

template <typename T>
SystemOfEquations<T> SystemOfEquations<T>::random(int n, unsigned seed){
    if (n <= 0)
        throw std::invalid_argument("Size must be positive");

    std::mt19937 gen(seed);

    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    SquareMatrix<T> A(n);
    Vector<T> b(n);

    for (int i = 0; i < n; ++i) {

        b.set(T(dist(gen)), i);

        for (int j = 0; j < n; ++j)
            A.set(T(dist(gen)), i, j);
    }

    return SystemOfEquations<T>(A, b);
}

template<class T>
SystemOfEquations<T> SystemOfEquations<T>::hilbert(int n) {
    SquareMatrix<T> H(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            H.set(T(1.0 / (i + j + 1)),i,j);

    Vector<T> x_true(n);

    for (int i = 0; i < n; i++) {
        x_true.set(T(1), i);
    }

    Vector<T> b = H * x_true;

    return SystemOfEquations<T>(H, b);
}

template<class T>
double SystemOfEquations<T>::residual(const Vector<T>& x) const{
    Vector<T> Ax = A * x;
    Vector<T> r = Ax - b;

    return r.norm();
}

template<class T>
double SystemOfEquations<T>::relative_error(const Vector<T>& approx, const Vector<T>& exact){
    Vector<T> diff = approx - exact;

    double norm_exact = exact.norm();

    if (norm_exact < 1e-18)
        return diff.norm();

    return diff.norm() / norm_exact;
}

// private function
template<class T>
void SystemOfEquations<T>::compare_sizes(const SquareMatrix<T> &A, const Vector<T> &b) {
    if (A.get_size() != b.get_size())
        throw std::invalid_argument("Sizes mismatch");
}

template<class T>
void SystemOfEquations<T>::lu_decomposition() const {

    int n = get_size();

    using std::abs;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++)
            U.set(A.get(i, j),i,j);
    }

    // единичная диагональ
    for (int i = 0; i < n; i++) {
        L.set(T(1), i, i);
    }

    // decomposition
    for (int k = 0; k < n - 1; k++) {

        if (abs(U.get(k, k)) < 1e-18)
            throw std::runtime_error("Zero pivot encountered");

        for (int i = k + 1; i < n; i++) {
            T factor =U.get(i, k) / U.get(k, k);
            L.set(factor, i, k);

            for (int j = k; j < n; j++) {
                T value =U.get(i, j) - factor * U.get(k, j);
                U.set(value, i, j);
            }
        }
    }

    lu_ready = true;
}

template<class T>
Vector<T> SystemOfEquations<T>::forward_substitution(const Vector<T>& rhs) const {
    int n = L.get_rows();
    using std::abs;

    Vector<T> y(n);

    for (int i = 0; i < n; i++) {
        T sum = T{};

        for (int j = 0; j < i; j++)
            sum += L.get(i,j) * y.get(j);

        if (abs(L.get(i,i)) < 1e-18)
            throw std::runtime_error("Zero on diagonal");

        y.set((rhs.get(i) - sum) / L.get(i,i), i);
    }

    return y;
}

template<class T>
Vector<T> SystemOfEquations<T>::backward_substitution(const Vector<T>& y) const{
    int n = U.get_rows();
    using std::abs;

    Vector<T> x(n);

    for (int i = n - 1; i >= 0; i--) {
        T sum = T{};

        for (int j = i + 1; j < n; j++)
            sum += U.get(i,j) * x.get(j);

        if (abs(U.get(i,i)) < 1e-18)
            throw std::runtime_error("Zero on diagonal");

        x.set((y.get(i) - sum) / U.get(i,i), i);
    }

    return x;
}

#endif //LABA3_SYSTEMS_OF_EQUATIONS_H
