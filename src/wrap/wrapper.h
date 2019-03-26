#pragma once

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace sba {
namespace wrap {

/*
 * swap T&
 */
template <typename T>
void swap(T &x, T &y);

/*
 * less
 */
template <class T>
bool less(T a, T b);
/*
 * specialization for less function
 */
template <>
bool less<const char *>(const char *a, const char *b);

} // namespace wrap
} // namespace sba
