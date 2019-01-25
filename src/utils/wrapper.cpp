#include "wrapper.hpp"

namespace sba {
namespace utils {

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

} // namespace utils
} // namespace sba
