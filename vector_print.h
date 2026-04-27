#ifndef LABA3_VECTOR_PRINT_H
#define LABA3_VECTOR_PRINT_H

#include <iostream>
#include "vector.h"

template<typename T>
void print_vector(const Vector<T>& vector) {
    std::cout << "[";
    for (int i = 0; i < vector.get_size(); i++)
        std::cout << vector.get(i) << " ";

    std::cout << "]\n";
}


#endif //LABA3_VECTOR_PRINT_H
