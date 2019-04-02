#pragma once

namespace sba {
namespace utils {

/**
 * Demo auto_ptr from Ctraustrup C++ book (head 14.4)
 */
template <class X>
class AutoPtr {

    // helper
    template<class Y> struct AutoPtrRef;

    X *ptr_;

public:
    AutoPtr(X *);
    AutoPtr(const AutoPtr &);

private:
};

template <class X>
template <class Y>
struct AutoPtr<X>::AutoPtrRef<Y> {
};

} // namespace utils
} // namespace sba
