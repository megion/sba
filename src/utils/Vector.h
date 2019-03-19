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
template<T> class Vector {

    T* v_;
    size_t len_;

public:
    Vector();               
    explicit Vector(size_t);

    ~Vector();

private:

};

} // namespace utils
} // namespace sba
