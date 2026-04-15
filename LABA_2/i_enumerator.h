#ifndef LABA2_IENUMERATE_H
#define LABA2_IENUMERATE_H

// обходить элементы последовательности, не зная как она устроена внутри
template<class T>
class IEnumerator {

public:
    virtual ~IEnumerator() = default;

    // проверяет, есть ли еще элементы
    virtual bool has_more_elements() = 0;

    // возращает текущий элемент и идёт дальше
    virtual const T& next() = 0;

};

#endif //LABA2_IENUMERATE_H