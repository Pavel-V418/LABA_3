#ifndef LABA2_MUTABLELISTSEQUENCE_H
#define LABA2_MUTABLELISTSEQUENCE_H

#include "listSequence.h"

template<class T>
class MutableListSequence : public ListSequence<T> {

public:

    MutableListSequence(const T *items, int count);
    MutableListSequence();
    MutableListSequence(const MutableListSequence &other);

    Sequence<T>* instance() override;
    Sequence<T>* create_empty_sequence() const override;
};

template<class T>
MutableListSequence<T>::MutableListSequence(const T *items, int count)
    : ListSequence<T>(items, count) {}

template<class T>
MutableListSequence<T>::MutableListSequence()
    : ListSequence<T>() {}

template<class T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence &other)
    : ListSequence<T>(other) {}

template<class T>
Sequence<T>* MutableListSequence<T>::instance() {
    return this;
}

template<class T>
Sequence<T>* MutableListSequence<T>::create_empty_sequence() const{
    return new MutableListSequence<T>();
}

#endif //LABA2_MUTABLELISTSEQUENCE_H