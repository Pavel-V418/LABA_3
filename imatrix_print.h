#ifndef LABA3_IMATRIX_PRINT_H
#define LABA3_IMATRIX_PRINT_H

#include <iostream>
#include "imatrix.h"

template<typename T>
void print_matrix(const IMatrix<T>& matrix) {
    for (int i = 0; i < matrix.get_rows(); i++) {
        for (int j = 0; j < matrix.get_columns(); j++) {
            std::cout << matrix.get(i, j) << " ";
        }
        std::cout << "\n";
    }
}


#endif //LABA3_IMATRIX_PRINT_H
