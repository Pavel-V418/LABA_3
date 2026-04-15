#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H

#include "i_enumerable.h"
#include <stdexcept>
#include <ostream>
#include "option.h"

template <class T>
class Sequence : public IEnumerable<T>{

public:

    // деструкторы
    virtual ~Sequence() = default;

    virtual IEnumerator<T>* get_enumerator() const = 0;

    virtual Sequence<T>* instance() = 0;
    virtual Sequence<T>* create_empty_sequence() const = 0;

    // геттеры
    virtual const T& get_first() const = 0; // =0 - ее обязаны реализовать наследники
    virtual const T& get_last() const = 0;
    virtual const T& get(int index) const = 0;

    virtual int get_length() const = 0;

    // Options Try-functions
    Option<T> try_get_first() const;
    Option<T> try_get_last() const;
    Option<T> try_get(int index) const;

    // main functions
    Sequence<T>* append(const T& item);
    Sequence<T>* prepend(const T& item);
    Sequence<T>* insert_at(const T& item, int index);
    Sequence<T>* remove_at(int index);

    Sequence<T>* get_sub_sequence(int startIndex, int endIndex);
    Sequence<T>* concat(const Sequence<T> &list);

    // Map-Reduse functions
    Sequence<T>* map(T(*func)(const T&));
    Sequence<T>* where(bool(*pred)(const T&));
    T reduce(T(*func)(const T&, const T&), const T& init_value);

    // operators overload
    const T& operator[](int index) const;
    bool operator==(const Sequence<T> &other) const;
    Sequence<T>* operator+(const Sequence<T> &other) const;

protected:

    // internal functions
    virtual void append_internal(const T& item) = 0;
    virtual void prepend_internal(const T& item) = 0;
    virtual void insert_at_internal(const T& item, int index) = 0;
    virtual void remove_at_internal(int index) = 0;

};

template<class T>
Sequence<T>* Sequence<T>::append(const T &item) {
    Sequence<T> *inst = instance();
    inst->append_internal(item);

    return inst;
}

template<class T>
Sequence<T>* Sequence<T>::prepend(const T& item) {
    Sequence<T> *inst = instance();
    inst->prepend_internal(item);

    return inst;
}

template<class T>
Sequence<T>* Sequence<T>::insert_at(const T& item, int index) {
    Sequence<T> *inst = instance();
    inst->insert_at_internal(item, index);

    return inst;
}

template<class T>
Sequence<T>* Sequence<T>::remove_at(int index) {

    if (index < 0 || index >= get_length())
        throw std::out_of_range("Index out of range");

    Sequence<T>* inst = instance();
    inst->remove_at_internal(index);

    return inst;
}

template<class T>
Sequence<T>* Sequence<T>::concat(const Sequence<T> &list) {

    Sequence<T> *concat = this->create_empty_sequence();

    auto it1 = this->get_enumerator();

    while (it1->has_more_elements())
        concat->append_internal(it1->next());

    delete it1;

    auto it2 = list.get_enumerator();

    while (it2->has_more_elements())
        concat->append_internal(it2->next());

    delete it2;

    return concat;
}

template<class T>
Sequence<T>* Sequence<T>::get_sub_sequence(int startIndex, int endIndex) {
    int length = this->get_length();

    if (startIndex < 0 || startIndex >= length || endIndex < 0 || endIndex >= length || startIndex > endIndex)
        throw std::out_of_range("Index out of range");

    Sequence<T> *subSequence = this->create_empty_sequence();

    auto it = this->get_enumerator();
    int index = 0;

    while (it->has_more_elements()) {
        const T& value = it->next();

        if (index >= startIndex && index <= endIndex)
            subSequence->append_internal(value);

        index++;
    }

    delete it;
    return subSequence;
}

template<class T>
Sequence<T>* Sequence<T>::map(T (*func)(const T&)) {
    Sequence<T> *result = this->create_empty_sequence();

    auto it = this->get_enumerator();
    while (it->has_more_elements())
        result->append_internal(func(it->next()));

    delete it;
    return result;
}

template<class T>
Sequence<T>* Sequence<T>::where(bool (*pred)(const T&)) {
    Sequence<T> *result = this->create_empty_sequence();

    auto it = this->get_enumerator();

    while (it->has_more_elements()) {
        const T& value = it->next();
        if (pred(value))
            result->append_internal(value);
    }

    delete it;
    return result;
}

template<class T>
T Sequence<T>::reduce(T (*func)(const T&, const T&), const T& init_value) {
    T value = init_value;

    auto it = this->get_enumerator();

    while (it->has_more_elements())
        value = func(value, it->next());

    delete it;
    return value;
}

template<class T>
const T& Sequence<T>::operator[](int index) const {
    return this->get(index);
}

template<class T>
bool Sequence<T>::operator==(const Sequence<T> &other) const { // нужен ли?
    if (this->get_length() != other.get_length())
        return false;

    if (this == &other) // проверка на то, указатель на одинаковые ли объекты
        return true;

    auto it1 = this->get_enumerator();
    auto it2 = other.get_enumerator();

    while (it1->has_more_elements() && it2->has_more_elements()) {
        if (it1->next() != it2->next()) {
            delete it1;
            delete it2;

            return false;
        }
    }

    delete it1;
    delete it2;

    return true;
}

template<class T>
Sequence<T> *Sequence<T>::operator+(const Sequence<T> &other) const{
    return this->concat(other);
}

template<class T>
std::ostream& operator<<(std::ostream &os, const Sequence<T> &seq) { // 1 параметр - ссылка куда мы пишем
    auto it = seq.get_enumerator();

    os << "[";

    while (it->has_more_elements()) {
        os << it->next();

        if (it->has_more_elements())
            os << ", ";
    }

    os << "]";

    delete it;
    return os;
}

// option's functions
template<class T>
Option<T> Sequence<T>::try_get_first() const{
    if (this->get_length() == 0)
        return Option<T>(); // = false, те sequence пустой

    return Option<T>(this->get_first()); // вернется Option, внутри которого has_value = true, value_ - найденный элемент
}

template<class T>
Option<T> Sequence<T>::try_get_last() const{
    if (this->get_length() == 0)
        return Option<T>();

    return Option<T>(this->get_last());
}

template<class T>
Option<T> Sequence<T>::try_get(int index) const{
    if (index > this->get_length() || index < 0)
        return Option<T>();

    return Option<T>(this->get(index));
}


#endif //LABA2_SEQUENCE_H