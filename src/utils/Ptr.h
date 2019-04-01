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
    Ptr(T*);
    Ptr(const Ptr&);

    /* convert Ptr<T> to Ptr<2> */
    template<class T2> operator Ptr<T2>();

private:
};


} // namespace utils
} // namespace sba
