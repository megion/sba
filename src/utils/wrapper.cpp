#include "wrapper.h"

namespace sba {
namespace utils {

template <class T>
bool less(T a, T b) {
    return a < b;
}

template <>
bool less<const char *>(const char *a, const char *b) {
    return std::strcmp(a, b) < 0;
}

template <typename T>
void swap(T *const a, T *const b) {
    T temp = *a; // call copy constructor
    *a = *b;     // call copy assign operator
    *b = temp;   // call copy assign operator
}

template <typename T>
void swap(const T &a, const T &b) {
    T temp = a; // call copy constructor
    a = b;      // call copy assign operator
    b = temp;   // call copy assign operator
}

template <typename T>
void swap_optimal(const T &a, const T &b) {
    T temp = a;          // call copy constructor
    a = b;               // call copy assign operator
    b = std::move(temp); // call copy replacement operator
}

void __my_assert(const char *expr_str, bool expr, const char *file, int line) {
    if (!expr) {
        std::printf("%s:%d: %s %sAssertion%s \n", file, line, expr_str,
                    RED_COLOR, RESET_COLOR);
        std::exit(EXIT_FAILURE);
    }
}

} // namespace utils
} // namespace sba
