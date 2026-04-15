#ifndef LABA2_LISTSEQUENCE_H
#define LABA2_LISTSEQUENCE_H

#include "linkedList.h"
#include "sequence.h"

template <class T>
class ListSequence : public Sequence<T> {

public:

    // constructors
    ListSequence(const T *items, int count);
    ListSequence();
    ListSequence(const ListSequence<T>& listSequence);

    // destructors
    ~ListSequence() override;

    IEnumerator<T>* get_enumerator() const override;
    //
    const T& get_first() const override;
    const T& get_last() const override;
    const T& get(int index) const override;

    int get_length() const override;

protected:
    LinkedList<T> *items;

    void append_internal(const T& item) override;
    void prepend_internal(const T& item) override;
    void insert_at_internal(const T& item, int index) override;
    void remove_at_internal(int index) override;

};

// constructors
template <class T>
ListSequence<T>::ListSequence(const T *items, int count) {
    this->items = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence() {
    items = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& listSequence) {
    items = new LinkedList<T>(*listSequence.items);
}

// destructors
template <class T>
ListSequence<T>::~ListSequence() {
    delete items;
}

template<class T>
IEnumerator<T> *ListSequence<T>::get_enumerator() const {
    return new typename LinkedList<T>::ListEnumerator(this->items->get_head());
}

template<class T>
const T& ListSequence<T>::get_first() const {
    return items->get_first();
}

template<class T>
const T& ListSequence<T>::get_last() const {
    return items->get_last();
}

template<class T>
const T& ListSequence<T>::get(int index) const {
    return items->get(index);
}

template<class T>
int ListSequence<T>::get_length() const {
    return items->get_length();
}

template<class T>
void ListSequence<T>::append_internal(const T &item) {
    this->items->append(item);
}

template<class T>
void ListSequence<T>::prepend_internal(const T &item) {
    this->items->prepend(item);
}

template<class T>
void ListSequence<T>::insert_at_internal(const T& item, int index) {
    this->items->insert_at(item, index);
}

template<class T>
void ListSequence<T>::remove_at_internal(int index) {

    if (index < 0 || index >= get_length())
        throw std::out_of_range("Index out of range");

    this->items->remove_at(index);
}
#endif //LABA2_LISTSEQUENCE_H