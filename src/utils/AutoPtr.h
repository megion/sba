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
#pragma once

namespace sba {
namespace utils {

// helper for realization destruction copy semantic
template <class Y>
struct AutoPtrRef {};

template <class X>
class AutoPtr {

    X *ptr_;

public:
    typedef X element_type;

    // throw() is nothing generate
    explicit AutoPtr(X *ptr = nullptr) throw() { ptr_ = ptr; };
    ~AutoPtr() throw() { delete ptr_; }

    // copy constructor takes not const argument
    AutoPtr(AutoPtr &a) throw(); // copy, next a.ptr = nullptr
    template <class Y>
    AutoPtr(AutoPtr<Y> &a) throw(); // copy, next a.ptr = nullptr

    // copy operators
    AutoPtr &operator=(AutoPtr &a) throw(); // copy, next a.ptr = nullptr
    template <class Y>
    AutoPtr &operator=(AutoPtr<Y> &a) throw(); // copy, next a.ptr = nullptr

    X &operator*() const throw() { return *ptr_; }
    X *operator->() const throw() { return ptr_; }

    X *get() const throw() { return ptr_; }

    /*
     * ownership transfer
     */
    X *release() throw();
    void reset(X *ptr = nullptr) throw();

private:
};

template <class X>
AutoPtr<X>::AutoPtr(AutoPtr &a) throw() {
    ptr_ = a.ptr_;
    a.ptr_ = nullptr;
}

template <class X>
template <class Y>
AutoPtr<X>::AutoPtr(AutoPtr<Y> &a) throw() {
    ptr_ = a.ptr_;
    a.ptr_ = nullptr;
}

template <class X>
AutoPtr<X> &AutoPtr<X>::operator=(AutoPtr &a) throw() {
    ptr_ = a.ptr_;
    a.ptr_ = nullptr;
    return *this;
}

template <class X>
template <class Y>
AutoPtr<X> &AutoPtr<X>::operator=(AutoPtr<Y> &a) throw() {
    ptr_ = a.ptr_;
    a.ptr_ = nullptr;
    return *this;
}

template <class X>
X *AutoPtr<X>::release() throw() {
    X *t = ptr_;
    ptr_ = nullptr;
    return t;
}

template <class X>
void AutoPtr<X>::reset(X *ptr) throw() {
    if (ptr != ptr_) {
        delete ptr_;
        ptr_ = ptr;
    }
}

// template <class X>
// template <class Y>
// struct AutoPtr<X>::AutoPtrRef<Y> {
//};

} // namespace utils
} // namespace sba
