#pragma once

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cstring>

#include "console-colors.h"

namespace sba {
namespace utils {


template <class T>
bool less(T a, T b);

/*
 * specialization for less function
 */
template <>
bool less<const char *>(const char *a, const char *b);

template <typename T>
void swap(T *const a, T *const b);

template <typename T>
void swap(const T &a, const T &b);

template <typename T>
void swap_optimal(const T &a, const T &b);

void __my_assert(const char *expr_str, bool expr, const char *file, int line);

} // namespace utils
} // namespace sba

#define my_assert(Expr) sba::utils::__my_assert(#Expr, Expr, __FILE__, __LINE__)
