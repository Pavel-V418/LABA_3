#ifndef LABA2_IMMUTABLELISTSEQUENCE_H
#define LABA2_IMMUTABLELISTSEQUENCE_H

#include "listSequence.h"

template<class T>
class ImmutableListSequence : public  ListSequence<T>{

public:
    ImmutableListSequence(const T *items, int count);
    ImmutableListSequence();
    ImmutableListSequence(const ImmutableListSequence &other);

    Sequence<T>* instance() override;
    Sequence<T>* create_empty_sequence() const override;

};

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(const T *items, int count)
    : ListSequence<T>(items, count) {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence()
    : ListSequence<T>() {}

template<class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence &other)
    : ListSequence<T>(other) {}

template<class T>
Sequence<T>* ImmutableListSequence<T>::instance() {
    return new ImmutableListSequence<T>(*this);
}

template<class T>
Sequence<T> *ImmutableListSequence<T>::create_empty_sequence() const {
    return new ImmutableListSequence<T>();
}

#endif //LABA2_IMMUTABLELISTSEQUENCE_H