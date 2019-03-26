#include "wrap/wrapper.h"

namespace sba {
namespace utils {

template <typename T>
void swap(T &x, T &y) {
    T temp = x; // call copy constructor
    x = y;      // call copy assign operator
    y = temp;   // call copy assign operator
}

template <class T>
bool less(T a, T b) {
    return a < b;
}

template <>
bool less<const char *>(const char *a, const char *b) {
    return std::strcmp(a, b) < 0;
}

} // namespace wrap
} // namespace sba
