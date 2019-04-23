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

#include <iostream>

namespace sba {
namespace utils {

// helper for realization destruction copy semantic
// template <class Y>
// struct AutoPtrRef;

template <class X>
class AutoPtr {

public:
    class AutoPtrRef;
    typedef X element_type;

private:
    X *ptr_;

public:
    // throw() is nothing generate
    explicit AutoPtr(X *ptr = nullptr) throw() { ptr_ = ptr; };
    ~AutoPtr() throw() { delete ptr_; }

    // copy constructor takes not const argument
    AutoPtr(const AutoPtr &a) throw(); // copy, next a.ptr = nullptr
    //template <class Y>
    //AutoPtr(AutoPtr<Y> &a) throw(); // copy, next a.ptr = nullptr

    // copy operators
    //AutoPtr &operator=(const AutoPtr &a) throw(); // copy, next a.ptr = nullptr
    //AutoPtr &operator=(const AutoPtrRef &a) throw();
    //template <class Y>
    //AutoPtr &operator=(AutoPtr<Y> &a) throw(); // copy, next a.ptr = nullptr

    X &operator*() const throw() { return *ptr_; }
    X *operator->() const throw() { return ptr_; }

    X *get() const throw() { return ptr_; }

    /*
     * ownership transfer
     */
    X *release() throw();
    void reset(X *ptr = nullptr) throw();

    /**
     * Copy from AutoPtrRef
     *
     * Convert constructor AutoPtrRef -> AutoPtr
     * It called when:
     *
     * AutoPtrRef pref;
     * AutoPtr p = pref; // ==> AutoPtr p = AutoPtr(pref);
     */
    //AutoPtr(AutoPtrRef ref) throw();

    /**
     * Copy to AutoPtrRef
     *
     * Convert operator AutoPtr -> AutoPtrRef
     * It called when:
     *
     * AutoPtr p;
     * AutoPtrRef pref = p;
     */
    //operator AutoPtrRef() const;

    /**
     * Destuction copy from AutoPtr
     *
     * Convert AutoPtr<X> -> AutoPtr<Y>
     * It called when:
     *
     * where X is child Y(syper class). X <- Y
     *
     * X x;
     * AutoPtr<X> px = &x;
     * AutoPtr<Y> py = px; // OK convert X* to Y*
     */
    //template <class Y>
    //operator AutoPtr<Y>();

private:
};

/*
 * helper for realization destruction copy semantic
 */
template <typename X>
class AutoPtr<X>::AutoPtrRef {
    friend class AutoPtr;

private:
    AutoPtr &p_; // link to AutoPtr value

    AutoPtrRef(AutoPtr &p) : p_(p) {}

public:
    /* conversion operator AutoPtrRef to X* */
    // operator X*() const { return p_.ptr_; }
    /* ptr_ref.operator=('a') */
    // void operator=(Char c) { s_.write(i_, c); }
};

template <class X>
AutoPtr<X>::AutoPtr(const AutoPtr &a) throw() {
    std::cout<<"test: "<<a.ptr_<<std::endl;
    ptr_ = a.ptr_;
    a.ptr_ = nullptr;
}

//template <class X>
//template <class Y>
//AutoPtr<X>::AutoPtr(AutoPtr<Y> &a) throw() {
    //ptr_ = a.release();
//}

//template <class X>
//template <class Y>
//AutoPtr<X> &AutoPtr<X>::operator=(AutoPtr<Y> &a) throw() {
    //ptr_ = a.release();
    //return *this;
//}

//template <class X>
//AutoPtr<X> &AutoPtr<X>::operator=(const AutoPtr &a) throw() {
    ////AutoPtr temp = release();
    ////ptr_ = a.release();
    //return *this;
//}

//template <class X>
//AutoPtr<X> &AutoPtr<X>::operator=(const AutoPtrRef &a) throw() {
    //AutoPtr temp = release();
    //ptr_ = a.p_.release();
    //return *this;
//}


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

//template <class X>
//AutoPtr<X>::AutoPtr(AutoPtrRef ref) throw() {
    /*
     * set ptr_ form ref
     */
    //ptr_ = ref.p_.ptr_;

    /*
     * TODO: update AutoPtrRef
     * May be it is error.
     */
    //ref.p_ = *(this);
//}

//template <class X>
//AutoPtr<X>::operator AutoPtrRef() const {
    //return AutoPtrRef(ptr_);
//}

} // namespace utils
} // namespace sba
