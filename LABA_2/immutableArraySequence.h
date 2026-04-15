#ifndef LABA2_IMMUTABLEARRAYSEQUENCE_H
#define LABA2_IMMUTABLEARRAYSEQUENCE_H

#include "arraySequence.h"

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {

public:

    ImmutableArraySequence(const T *items, int count);
    ImmutableArraySequence();
    ImmutableArraySequence(const ImmutableArraySequence<T> &other);

    Sequence<T>* instance() override;
    Sequence<T>* create_empty_sequence() const override;
};

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const T *items, int count)
    : ArraySequence<T>(items, count){}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence()
    : ArraySequence<T>() {}

template<class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T> &other)
    : ArraySequence<T>(other) {}

template<class T>
Sequence<T>* ImmutableArraySequence<T>::instance() {
    return new ImmutableArraySequence<T>(*this);
}

template<class T>
Sequence<T>* ImmutableArraySequence<T>::create_empty_sequence() const {
    return new ImmutableArraySequence<T>();
}
#endif //LABA2_IMMUTABLEARRAYSEQUENCE_H