#include <iostream>
#include "rectangle_matrix.h"
#include "square_matrix.h"
#include "triangle_matrix.h"
#include "diagonal_matrix.h"
#include "sparse_matrix.h"
#include "vector.h"
#include "complex.h"
#include "imatrix_print.h"
#include "vector_print.h"
#include "complex_print.h"


template<typename T>
T safe_input() {
    T value;

    while (true) {
        std::cin >> value;

        if (!std::cin.fail()) {
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Try again: ";
    }
}

template<typename T>
IMatrix<T>* create_matrix() {
    std::cout << "\nChoose matrix type:\n";
    std::cout << "1. Rectangle matrix\n";
    std::cout << "2. Square matrix\n";
    std::cout << "3. Triangle matrix\n";
    std::cout << "4. Diagonal matrix\n";
    std::cout << "5. Sparse matrix\n";

    int type = safe_input<int>();

    int n, m;

    switch (type) {
        case 1:
            std::cout << "rows: ";
            n = safe_input<int>();

            std::cout << "cols: ";
            m = safe_input<int>();
            return new RectangleMatrix<T>(n, m);

        case 2:
            std::cout << "size: ";
            n = safe_input<int>();

            return new SquareMatrix<T>(n);

        case 3: {
            std::cout << "size: ";
            n = safe_input<int>();

            int t;

            std::cout << "0 - lower, 1 - upper: ";
            t = safe_input<int>();

            return new TriangleMatrix<T>(
                n,
                t == 0 ? TriangleType::lower_triangle : TriangleType::upper_triangle
            );
        }

        case 4:
            std::cout << "size: ";
            n = safe_input<int>();

            return new DiagonalMatrix<T>(n);

        case 5:
            std::cout << "rows: ";
            n = safe_input<int>();

            std::cout << "cols: ";
            m = safe_input<int>();

            return new SparseMatrix<T>(n, m);

        default:
            throw std::invalid_argument("Invalid matrix type");
    }
}

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
        op = safe_input<int>();

        try {
            switch (op) {

            case 0:
                delete matrix;
                return;

            case 1: {
                int i, j;
                T val;

                std::cout << "i: ";
                i = safe_input<int>();

                std::cout << "j: ";
                j = safe_input<int>();

                std::cout << "value: ";
                val = safe_input<T>();

                matrix->set(val, i, j);

                break;
            }

            case 2: {
                int i, j;
                std::cout << "i: ";
                i = safe_input<int>();

                std::cout << "j: ";
                j = safe_input<int>();

                std::cout << "Value = " << matrix->get(i, j) << "\n";

                break;
            }

            case 3:
                print_matrix(*matrix);
                break;

            case 4: {
                std::cout << "Create second matrix:\n";
                IMatrix<T>* other = create_matrix<T>();

                std::cout << "Enter values for second matrix:\n";

                for (int i = 0; i < other->get_rows(); i++) {
                    for (int j = 0; j < other->get_columns(); j++) {
                        T val = safe_input<T>();
                        try {
                            other->set(val, i, j);
                        } catch (...) {}
                    }
                }

                IMatrix<T>* result = matrix->add(*other);

                delete matrix;
                delete other;
                matrix = result;
                break;
            }

            case 5: {
                T scalar;
                std::cout << "scalar: ";
                scalar = safe_input<T>();

                IMatrix<T>* result = matrix->multiply_scalar(scalar);

                delete matrix;
                matrix = result;
                break;
            }

            case 6:
                std::cout << "Norm = " << matrix->norm() << "\n";
                break;

            case 7: {
                int n = matrix->get_columns();
                Vector<T> v(n);

                std::cout << "Enter vector:\n";
                for (int i = 0; i < n; i++) {
                    T x = safe_input<T>();
                    v.set(x, i);
                }

                Vector<T> res = (*matrix) * v;

                std::cout << "Result:\n";
                for (int i = 0; i < res.get_size(); i++)
                    std::cout << res[i] << " ";
                std::cout << "\n";
                break;
            }

            default:
                std::cout << "Invalid option\n";
                break;
            }

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

template<typename T>
void vector_menu() {
    Vector<T>* v = nullptr;

    while (true) {
        std::cout << "\n--- VECTOR MENU ---\n";
        std::cout << "1. Create vector\n";
        std::cout << "2. Set element\n";
        std::cout << "3. Get element\n";
        std::cout << "4. Print\n";
        std::cout << "5. Add vector\n";
        std::cout << "6. Subtract vector\n";
        std::cout << "7. Dot product\n";
        std::cout << "8. Norm\n";
        std::cout << "0. Back\n";

        int op = safe_input<int>();

        try {
            switch (op) {

            case 0:
                delete v;
                return;

            case 1: {
                int n;
                std::cout << "Vector size: ";
                n = safe_input<int>();

                delete v;
                v = new Vector<T>(n);

                std::cout << "Enter elements:\n";
                for (int i = 0; i < n; i++) {
                    T x = safe_input<T>();
                    v->set(x, i);
                }
                break;
            }

            case 2: {
                if (!v) {
                    std::cout << "Create vector first\n";
                    break;
                }
                int i;
                T val;
                std::cout << "index: ";
                i = safe_input<int>();
                std::cout << "value: ";
                val = safe_input<T>();
                v->set(val, i);
                break;
            }

            case 3: {
                if (!v) {
                    std::cout << "Create vector first\n";
                    break;
                }
                int i;
                std::cout << "index: ";
                i = safe_input<int>();
                std::cout << "Value = " << v->get(i) << "\n";
                break;
            }

            case 4:
                if (!v) {
                    std::cout << "Create vector first\n";
                    break;
                }
                print_vector(*v);
                break;

            case 5: {
                if (!v) {
                    std::cout << "Create vector first\n";
                    break;
                }

                std::cout << "Enter second vector:\n";
                Vector<T> other(v->get_size());

                for (int i = 0; i < other.get_size(); i++) {
                    T x = safe_input<T>();
                    other.set(x, i);
                }

                Vector<T> res = (*v) + other;
                print_vector(res);

                break;
            }

            case 6: {
                if (!v) {
                    std::cout << "Create vector first\n";
                    break;
                }

                std::cout << "Enter second vector:\n";
                Vector<T> other(v->get_size());

                for (int i = 0; i < other.get_size(); i++) {
                    T x = safe_input<T>();
                    other.set(x, i);
                }

                Vector<T> res = (*v) - other;
                print_vector(res);

                break;
            }

            case 7: {
                if (!v) {
                    std::cout << "Create vector first\n";
                    break;
                }

                std::cout << "Enter second vector:\n";
                Vector<T> other(v->get_size());

                for (int i = 0; i < other.get_size(); i++) {
                    T x = safe_input<T>();
                    other.set(x, i);
                }

                std::cout << "Dot = " << v->dot(other) << "\n";
                break;
            }

            case 8:
                if (!v) {
                    std::cout << "Create vector first\n";
                } else {
                    std::cout << "Norm = " << v->norm() << "\n";
                }
                break;

            default:
                std::cout << "Invalid option\n";
                break;
            }

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

int main() {
    while (true) {
        std::cout << "\n==== MAIN MENU ====\n";
        std::cout << "1. Matrices\n";
        std::cout << "2. Vectors\n";
        std::cout << "0. Exit\n";

        int main_choice = safe_input<int>();

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