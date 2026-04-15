#ifndef LABA3_IMATRIX_H
#define LABA3_IMATRIX_H

template<class T>
class IMatrix {

public:
    virtual ~IMatrix() = default;

    virtual const T& get(int i, int j) const = 0;

    virtual int get_rows() const = 0;
    virtual int get_columns() const = 0;

    virtual double norm() const = 0;

    virtual void set(const T& value, int i, int j) = 0;

    virtual IMatrix<T>* add(const IMatrix<T>& other) const = 0;
    virtual IMatrix<T>* multiply_scalar(const T& scalar) const = 0;

};

#endif //LABA3_IMATRIX_H
