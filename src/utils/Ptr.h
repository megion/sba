#pragma once

namespace sba {
namespace utils {

/**
 * Demo template conversion from Ctraustrup C++ book (head 13.6)
 */
template <class T>
class Ptr {

    T *p_;

public:
    Ptr(T *);
    Ptr(const Ptr &);

    /* convert Ptr<T> to Ptr<2> */
    template <class T2>
    operator Ptr<T2>();

    T *get() const { return p_; }

private:
};

template <class T>
Ptr<T>::Ptr(T *p) : p_(p) {}

template <class T>
Ptr<T>::Ptr(const Ptr &p) : p_(p.p_) {}

template <class T>
template <class T2>
Ptr<T>::operator Ptr<T2>() {
    return Ptr<T2>(p_);
}

} // namespace utils
} // namespace sba
