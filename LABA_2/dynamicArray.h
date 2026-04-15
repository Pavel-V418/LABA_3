#ifndef LABA2_DYNAMICARRAY_H
#define LABA2_DYNAMICARRAY_H

#include <stdexcept>
#include "i_enumerator.h"

template <class T>
class DynamicArray {
private:
    T *data;
    int size;
    int capacity;

public:
    // constuctors - способы создания массива
    DynamicArray(const T *items, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& dynamicArray);

    // destructor
    ~DynamicArray();

    // Decomposition
    const T& get(int index) const;
    int get_size() const;

    // operations
    void set(const T& value, int index);
    void resize(int newSize);

    // итератор
    class ArrayEnumerator : public IEnumerator<T> {

    public:
        ArrayEnumerator(const DynamicArray<T> *arr)
            : array(arr), index(0) {}

        bool has_more_elements() override{ // has more elemen
            return index < array->get_size();
        }

        const T& next() override{
            if (!has_more_elements())
                throw std::out_of_range("ArrayEnumerator::Next");

            return array->get(index++); // вернуть текущий элемент и передвинуться на следующий
        }

    private:
        const DynamicArray<T> *array;
        int index;
    };

};

template<class T>
DynamicArray<T>::DynamicArray(const T *items, int count) {
    if (count < 0)
        throw std::invalid_argument("Size cannot be negative");

    this->size = count;

    if (count > 0)
        capacity = count;
    else
        capacity = 1;

    data = new T[capacity];

    for (int i = 0; i < size; i++)
        data[i] = items[i];
}

template<class T>
DynamicArray<T>::DynamicArray(int size) {
    if (size < 0)
        throw std::invalid_argument("Size cannot be negative");

    this->size = size;

    if (size > 0)
        capacity = size;
    else
        capacity = 1;

    data = new T[capacity];
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {
    this->size = dynamicArray.size;
    capacity = dynamicArray.capacity;

    data = new T[capacity];

    for (int i = 0; i < size; i++)
        data[i] = dynamicArray.data[i];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
const T& DynamicArray<T>::get(int index) const{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index] ; // поместить в итератор
}

template<class T>
int DynamicArray<T>::get_size() const{
    return size;
}

template<class T>
void DynamicArray<T>::set(const T& value, int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    data[index] = value;
}

template<class T>
void DynamicArray<T>::resize(int newSize) {
    if (newSize < 0)
        throw std::invalid_argument("Size cannot be negative");

    if (newSize <= capacity) {
        size = newSize;
        return;
    }

    int newCapacity = capacity;

    while (newCapacity < newSize)
        newCapacity *= 2;

    T* newData = new T[newCapacity];

    for (int i = 0; i < size; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    size = newSize;
}

#endif //LABA2_DYNAMICARRAY_H