#ifndef LABA2_ARRAYSEQUENCE_H
#define LABA2_ARRAYSEQUENCE_H

#include "dynamicArray.h"
#include "sequence.h"

template <class T>
class ArraySequence : public Sequence<T>{

public:

    // constructors
    ArraySequence(const T *items, int count);
    ArraySequence();
    ArraySequence(const ArraySequence<T> &arraySequence);

    // destructor
    ~ArraySequence() override;

    IEnumerator<T> *get_enumerator() const override;

    // Getters
    const T& get_first() const override;
    const T& get_last() const override;
    const T& get(int index) const override;

    int get_length() const override;

protected:
    DynamicArray<T> *items;

    // Operations
    void append_internal(const T& item) override;
    void prepend_internal(const T& item) override;
    void insert_at_internal(const T& item, int index) override;
    void remove_at_internal(int index) override;
};


/*============ КОНСТРУКТОРЫ ============*/
template<class T>
ArraySequence<T>::ArraySequence(const T *items, int count) {
    this->items = new DynamicArray<T>(items, count);
}

template<class T>
ArraySequence<T>::ArraySequence(){
    items = new DynamicArray<T>(0);
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence& arraySequence) {
    items = new DynamicArray<T>(*arraySequence.items);
}

/*============ ДЕСТРУКТОР ============ */
template<class T>
ArraySequence<T>::~ArraySequence() {
    delete items;
}

/*============ Итератор ============ */
template<class T>
IEnumerator<T>* ArraySequence<T>::get_enumerator() const {
    return new typename DynamicArray<T>::ArrayEnumerator(this->items);
}

/*============ ГЕТТЕРЫ ============ */

template<class T>
const T& ArraySequence<T>::get_first() const{
    if (items->get_size() == 0)
        throw std::out_of_range("Sequence is empty");
    return items->get(0);
}

template<class T>
const T& ArraySequence<T>::get_last() const {
    if (items->get_size() == 0)
        throw std::out_of_range("Sequence is empty");
    return items->get(items->get_size() - 1);
}

template<class T>
const T& ArraySequence<T>::get(int index) const {
    if (index < 0 || index >= items->get_size())
        throw std::out_of_range("Index out of range");
    return items->get(index);
}

template<class T>
int ArraySequence<T>::get_length() const{
    return items->get_size();
}

template<class T>
void ArraySequence<T>::append_internal(const T& item) {
    int index_free = this->items->get_size();

    this->items->resize(index_free + 1);
    this->items->set(item, index_free);
}

template<class T>
void ArraySequence<T>::prepend_internal(const T& item) {
    int size = this->items->get_size();
    this->items->resize(size + 1);

    for (int i = size; i > 0; i--)
        this->items->set(this->items->get(i - 1), i);

    this->items->set(item, 0);
}

template<class T>
void ArraySequence<T>::insert_at_internal(const T& item, int index) {
    if (index < 0 || index > this->items->get_size())
        throw std::out_of_range("Index out of range");

    int size = this->items->get_size();
    this->items->resize(size + 1);

    for (int i = size; i > index; i--)
        this->items->set(this->items->get(i - 1), i);

    this->items->set(item, index);
}

template<class T>
void ArraySequence<T>::remove_at_internal(int index) {
    int size = this->items->get_size();

    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    for (int i = index; i < size - 1; i++) {
        this->items->set(this->items->get(i + 1), i);
    }

    this->items->resize(size - 1);
}
#endif //LABA2_ARRAYSEQUENCE_H