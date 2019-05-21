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

template <class X>
class AutoPtr {

private:
    X *ptr_;

public:
    AutoPtr(X *ptr = nullptr) throw() : ptr_(ptr){};
    ~AutoPtr() throw() { delete ptr_; }

    // copy constructor takes not const argument, next a.ptr = nullptr
    AutoPtr(AutoPtr &a) throw();
    template <class Y>
    AutoPtr(AutoPtr<Y> &a) throw();

    // copy operators, next a.ptr = nullptr
    AutoPtr &operator=(AutoPtr &a) throw();
    template <class Y>
    AutoPtr &operator=(AutoPtr<Y> &a) throw();

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

template <class X>
AutoPtr<X>::AutoPtr(AutoPtr &a) throw() {
    ptr_ = a.ptr_;
    a.ptr_ = nullptr;
}

template <class X>
template <class Y>
AutoPtr<X>::AutoPtr(AutoPtr<Y> &a) throw() {
    ptr_ = a.release();

    // allow downcast
    //ptr_ = dynamic_cast<X*>(a.release());
}

template <class X>
template <class Y>
AutoPtr<X> &AutoPtr<X>::operator=(AutoPtr<Y> &a) throw() {
    AutoPtr temp = release(); // will be free automaticaly
    ptr_ = a.release();
    return *this;
}

template <class X>
AutoPtr<X> &AutoPtr<X>::operator=(AutoPtr &a) throw() {
    AutoPtr temp = release(); // will be free automaticaly
    ptr_ = a.release();
    return *this;
}

} // namespace utils
} // namespace sba
