#pragma once

namespace sba {
namespace utils {

/**
 * Demo auto_ptr from Ctraustrup C++ book (head 14.4)
 * Support Resource Acquisition is Initialization technic
 *
 * The auto_ptr is deprecated. Instead, use unique_ptr 
 *
 * auto_ptr have to use only pointer linked with scalar object. You must not 
 * use it for pointer linked with array (new T[length]).
 * 
 * For array use vector, for exmaple: vector<double> tmp( src.size() );
 */
template <class X>
class AutoPtr {

    // helper
    template<class Y> struct AutoPtrRef {
    };

    X *ptr_;

public:
    AutoPtr(X *);
    AutoPtr(const AutoPtr &);

private:
};

//template <class X>
//template <class Y>
//struct AutoPtr<X>::AutoPtrRef<Y> {
//};

} // namespace utils
} // namespace sba
