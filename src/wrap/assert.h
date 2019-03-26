#pragma once

#include <cstdlib>
//#include <iostream>
//#include <stdexcept>

#include "console-colors.h"

namespace sba {
namespace wrap {


void __my_assert(const char *expr_str, bool expr, const char *file, int line);

} // namespace wrap
} // namespace sba

#define my_assert(Expr) sba::wrap::__my_assert(#Expr, Expr, __FILE__, __LINE__)
