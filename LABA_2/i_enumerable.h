#ifndef LABA2_IENUMERABLE_H
#define LABA2_IENUMERABLE_H

#include "i_enumerator.h"

// дает итератор
template<class T>
class IEnumerable {

public:
    virtual ~IEnumerable() = default;

    virtual IEnumerator<T>* get_enumerator() const = 0;

};

#endif //LABA2_IENUMERABLE_H