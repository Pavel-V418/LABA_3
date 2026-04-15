#ifndef LABA2_OPTION_H
#define LABA2_OPTION_H

#include <stdexcept>

template <class T>
class Option {

public:
    Option() : has_value_(false) {}
    Option(const T& val) : has_value_(true), value_(val) {}

    bool has_more_elements() const { return has_value_; } // проверяет есть ли значение
    const T& get_value() const {
        if (!has_value_)
            throw std::runtime_error("Option value is required");

        return value_;
    }

private:
    bool has_value_;
    T value_; // не const , так как это хранилище
};

#endif //LABA2_OPTION_H