#include <iostream>

#include "rectangle_matrix.h"
#include "square_matrix.h"
#include "triangle_matrix.h"
#include "diagonal_matrix.h"
#include "sparse_matrix.h"
#include "vector.h"
#include "complex.h"

// ====================== PRINT ======================

template<typename T>
void print_matrix(const IMatrix<T>& matrix) {
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_columns(); j++) {
            std::cout << matrix.get(i, j) << " ";
        }
        std::cout << "\n";
    }
}

// ====================== CREATE MATRIX ======================

template<typename T>
IMatrix<T>* create_matrix() {
    std::cout << "\nChoose matrix type:\n";
    std::cout << "1. Rectangle\n2. Square\n3. Triangle\n4. Diagonal\n5. Sparse\n";

    int type;
    std::cin >> type;

    int n, m;

    switch (type) {
        case 1:
            std::cout << "rows cols: ";
            std::cin >> n >> m;
            return new RectangleMatrix<T>(n, m);

        case 2:
            std::cout << "size: ";
            std::cin >> n;
            return new SquareMatrix<T>(n);

        case 3: {
            std::cout << "size: ";
            std::cin >> n;
            int t;
            std::cout << "0 - lower, 1 - upper: ";
            std::cin >> t;

            return new TriangleMatrix<T>(
                n,
                t == 0 ? TriangleType::lower_triangle : TriangleType::upper_triangle
            );
        }

        case 4:
            std::cout << "size: ";
            std::cin >> n;
            return new DiagonalMatrix<T>(n);

        case 5:
            std::cout << "rows cols: ";
            std::cin >> n >> m;
            return new SparseMatrix<T>(n, m);

        default:
            throw std::invalid_argument("Invalid matrix type");
    }
}

// ====================== MATRIX MENU ======================

template<typename T>
void matrix_menu() {
    IMatrix<T>* matrix = nullptr;

    try {
        matrix = create_matrix<T>();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        return;
    }

    while (true) {
        std::cout << "\n--- MATRIX MENU ---\n";
        std::cout << "1. Set element\n";
        std::cout << "2. Get element\n";
        std::cout << "3. Print\n";
        std::cout << "4. Add matrix\n";
        std::cout << "5. Multiply by scalar\n";
        std::cout << "6. Norm\n";
        std::cout << "7. Matrix * Vector\n";
        std::cout << "0. Back\n";

        int op;
        std::cin >> op;

        if (op == 0) break;

        try {
            if (op == 1) {
                int i, j;
                T val;
                std::cout << "i j value: ";
                std::cin >> i >> j >> val;
                matrix->set(val, i, j);
            }

            else if (op == 2) {
                int i, j;
                std::cout << "i j: ";
                std::cin >> i >> j;
                std::cout << "Value = " << matrix->get(i, j) << "\n";
            }

            else if (op == 3) {
                print_matrix(*matrix);
            }

            else if (op == 4) {
                std::cout << "Create second matrix:\n";
                IMatrix<T>* other = create_matrix<T>();

                std::cout << "Enter values for second matrix:\n";
                for (int i = 0; i < other->get_rows(); i++) {
                    for (int j = 0; j < other->get_columns(); j++) {
                        T val;
                        std::cin >> val;
                        try {
                            other->set(val, i, j);
                        } catch (...) {}
                    }
                }

                IMatrix<T>* result = matrix->add(*other);

                delete matrix;
                delete other;
                matrix = result;
            }

            else if (op == 5) {
                T scalar;
                std::cout << "scalar: ";
                std::cin >> scalar;

                IMatrix<T>* result = matrix->multiply_scalar(scalar);

                delete matrix;
                matrix = result;
            }

            else if (op == 6) {
                std::cout << "Norm = " << matrix->norm() << "\n";
            }

            else if (op == 7) {
                int n = matrix->get_columns();
                Vector<T> v(n);

                std::cout << "Enter vector:\n";
                for (int i = 0; i < n; i++) {
                    T x;
                    std::cin >> x;
                    v.set(x, i);
                }

                Vector<T> res = (*matrix) * v;

                std::cout << "Result:\n";
                for (int i = 0; i < res.get_size(); i++)
                    std::cout << res[i] << " ";
                std::cout << "\n";
            }

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    delete matrix;
}

// ====================== VECTOR MENU ======================

template<typename T>
void vector_menu() {
    int n;
    std::cout << "Vector size: ";
    std::cin >> n;

    Vector<T> v1(n);
    Vector<T> v2(n);

    std::cout << "Enter first vector:\n";
    for (int i = 0; i < n; i++) {
        T x;
        std::cin >> x;
        v1.set(x, i);
    }

    std::cout << "Enter second vector:\n";
    for (int i = 0; i < n; i++) {
        T x;
        std::cin >> x;
        v2.set(x, i);
    }

    while (true) {
        std::cout << "\n--- VECTOR MENU ---\n";
        std::cout << "1. Add\n";
        std::cout << "2. Subtract\n";
        std::cout << "3. Dot product\n";
        std::cout << "4. Norm\n";
        std::cout << "0. Back\n";

        int op;
        std::cin >> op;

        if (op == 0) break;

        try {
            if (op == 1) {
                Vector<T> res = v1 + v2;
                for (int i = 0; i < res.get_size(); i++)
                    std::cout << res[i] << " ";
                std::cout << "\n";
            }

            else if (op == 2) {
                Vector<T> res = v1 - v2;
                for (int i = 0; i < res.get_size(); i++)
                    std::cout << res[i] << " ";
                std::cout << "\n";
            }

            else if (op == 3) {
                std::cout << "Dot = " << v1.dot(v2) << "\n";
            }

            else if (op == 4) {
                std::cout << "Norm = " << v1.norm() << "\n";
            }

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

// ====================== MAIN ======================

int main() {
    while (true) {
        std::cout << "\n==== MAIN MENU ====\n";
        std::cout << "1. Matrices\n";
        std::cout << "2. Vectors\n";
        std::cout << "0. Exit\n";

        int main_choice;
        std::cin >> main_choice;

        if (main_choice == 0) break;

        std::cout << "\nChoose data type:\n";
        std::cout << "1. int\n2. double\n3. complex\n";

        int type;
        std::cin >> type;

        try {
            if (main_choice == 1) {
                if (type == 1) matrix_menu<int>();
                else if (type == 2) matrix_menu<double>();
                else if (type == 3) matrix_menu<Complex>();
            }

            else if (main_choice == 2) {
                if (type == 1) vector_menu<int>();
                else if (type == 2) vector_menu<double>();
                else if (type == 3) vector_menu<Complex>();
            }

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}