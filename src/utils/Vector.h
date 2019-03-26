#pragma once

#include <iostream>
//#include <cstdio>
#include <cstring>

namespace sba {
namespace utils {

/**
 * Example of Vector from Ctraustrup C++ book (head 13.5)
 *
 * Demo template specialization
 */
template <class T>
class Vector {

    T *v_;
    size_t len_;

public:
    Vector();
    explicit Vector(size_t);

    ~Vector();

    T &elem(size_t i) { return v_[i]; }
    T &operator[](size_t i);

    size_t size() const { return len_; }

    void swap(Vector &);

private:
};

/*
 * Vector specialization for all vector of pointers. It full specalization used
 * as: Vector<void*> vpv;
 *
 * the first syntax 'template <>' - it is specialization
 * the second <void *> - this specialization for all Vector where 'T' is void*
 */
template <>
class Vector<void *> {
    void **p_;

public:
    Vector();
    explicit Vector(size_t);

    void *&elem(size_t i) { return p_[i]; }
    void *&operator[](size_t i);
};

/*
 * It is 'partial specialization'
 * Use for any vector of pointers and only vector pointers.
 * If user define class specialization then compilator doesn't generate
 * class definition for this specialization.
 *
 * '<T *>' it is mean that this specialization use for each Vector template
 * parameter is T*. For examples:
 * Vector<Shape*> vps; // T - Shape
 * Vector<int**> vppi; // T - int*
 */
template <class T>
class Vector<T *> : private Vector<void *> {
public:
    typedef Vector<void *> Base;

    Vector() : Base() {}
    explicit Vector(size_t i) : Base(i) {}

    T *&elem(size_t i) { return reinterpret_cast<T *&>(Base::elem(i)); }
    T *&operator[](size_t i) {
        return reinterpret_cast<T *&>(Base::operator[](i));
    }
};

/*
 * swap specialization for Vector<T>
 */
template <class T>
void swap(Vector<T> &, Vector<T> &);

/*
 * sort
 */
template <class T>
void sort(Vector<T> &);

} // namespace utils
} // namespace sba
