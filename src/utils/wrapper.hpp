#ifndef SBA_UTILS_WRAPPER_HPP
#define SBA_UTILS_WRAPPER_HPP

#include <exception>
#include <iostream>
#include <stdexcept>

namespace sba {
namespace utils {

template <typename T>
void swap(T *const a, T *const b);

template <typename T>
void swap(const T &a, const T &b);

template <typename T>
void swap_optimal(const T &a, const T &b);

} // namespace utils
} // namespace sba

#endif
