#include <utils/Vector.h>
#include <wrap/wrapper.h>

namespace sba {
namespace utils {

template <class T>
void Vector<T>::swap(Vector<T> &a) {
    // swap vector representation
    wrap::swap(v_, a.v_);     // swap pointers
    wrap::swap(len_, a.len_); // swap length
}

template <class T>
void swap(Vector<T> &a, Vector<T> &b) {
    a.swap(b);
}

/**
 * Shell sort
 */
template <class T>
void sort(Vector<T> &v) {
    const size_t n = v.size();

    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < n; i++) {
            for (size_t j = i - gap; j >= 0; j -= gap) {
                if (wrap::less(v[j + gap], v[j])) {
                    wrap::swap(v[j], v[j + gap]);
                } else {
                    break;
                }
            }
        }
    }
}

} // namespace utils
} // namespace sba
