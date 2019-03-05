#pragma once

#include <iostream>

#include <cassert>
#include <cstdio>

#include "console-colors.hpp"
#include "utils/wrapper.hpp"

/*
 * Test the given `fn`.
 */
#define mytest(fn)                                                             \
    std::printf("    " GREEN_COLOR "✓ %s" RESET_COLOR "\n", #fn);              \
    test_##fn();

/*
 * Test suite title.
 */
#define suite(title) std::printf("\n  " CYAN_COLOR "%s" RESET_COLOR "\n", title)

#define assert_range(val, middle, offset)                                      \
    my_assert((middle - offset < val) && (val < middle + offset));

namespace test {

/**
 * call constructor/destrutor reflection helper
 */
class reflection_helper {
public:
    size_t default_constructor_call_count;
    size_t copy_constructor_call_count;
    size_t move_constructor_call_count;

    size_t copy_operator_call_count;
    size_t move_operator_call_count;

    size_t destructor_call_count;
    size_t clear_resources_call_count;

    reflection_helper()
        : default_constructor_call_count(0)
        , copy_constructor_call_count(0)
        , move_constructor_call_count(0)
        , copy_operator_call_count(0)
        , move_operator_call_count(0)
        , destructor_call_count(0)
        , clear_resources_call_count(0) {}

    reflection_helper(const reflection_helper &) {}

    reflection_helper &
    operator=(const reflection_helper &) = delete; // assign operator
    reflection_helper &
    operator=(reflection_helper &&) = delete; // replacement operator

    void reset() {
        default_constructor_call_count = 0;
        copy_constructor_call_count = 0;
        move_constructor_call_count = 0;
        copy_operator_call_count = 0;
        move_operator_call_count = 0;
        destructor_call_count = 0;
        clear_resources_call_count = 0;
    }
};

/*
 * TODO: implement first call initalization like:
 * reflection_helper &get_demo_array_rh() {
 *     static reflection_helper rh;
 *     return rh;
 }
 */
//reflection_helper &get_demo_array_rh();

/**
 * demo array
 */
template <typename T>
class demo_array {
public:
    static reflection_helper call_info;

    demo_array() : len_(3) {
        values_ = new T[len_];
        demo_array::call_info.default_constructor_call_count++;
    }

    ~demo_array() {
        demo_array::call_info.destructor_call_count++;
        if (values_) {
            delete[] values_;
            values_ = nullptr;
            len_ = 0;
            demo_array::call_info.clear_resources_call_count++;
        }
    }

    demo_array(demo_array &&v) : values_(v.values_), len_(v.len_) {
        v.values_ = nullptr;
        v.len_ = 0;
        demo_array::call_info.move_constructor_call_count++;
    }

    demo_array(const demo_array &v) : len_(v.len_) {
        values_ = new T[len_];
        for (size_t i = 0; i < len_; i++) {
            values_[i] = v.values_[i]; // copy object
        }
        demo_array::call_info.copy_constructor_call_count++;
    }

    demo_array &operator=(const demo_array &other) {
        if (values_) {
            delete[] values_;
            values_ = nullptr;
        }
        len_ = other.len_;
        values_ = new T[len_];
        for (size_t i = 0; i < len_; i++) {
            values_[i] = other.values_[i]; // copy object
        }
        demo_array::call_info.copy_operator_call_count++;
        return *this;
    }

    demo_array &operator=(demo_array &&other) {
        values_ = other.values_;
        len_ = other.len_;
        other.values_ = nullptr;
        other.len_ = 0;
        demo_array::call_info.move_operator_call_count++;
        return *this;
    }

    T *values() const { return values_; }

private:
    T *values_;
    size_t len_;
};

class FooA {
public:
    static reflection_helper call_info;

    FooA() : val_a_(0) { std::cout << "call FooA constuctor" << std::endl; }

    FooA(int val_a) : val_a_(val_a) {}

    ~FooA() {
        FooA::call_info.destructor_call_count++;
        val_a_ = (0);
        std::cout << "call FooA destructor" << std::endl;
    }

    FooA(FooA &&v) : val_a_(v.val_a_) {
        v.val_a_ = 0;
        FooA::call_info.move_constructor_call_count++;
    }

    FooA(const FooA &v) : val_a_(v.val_a_) {
        FooA::call_info.copy_constructor_call_count++;
    }

    FooA &operator=(const FooA &other) {
        val_a_ = other.val_a_;
        FooA::call_info.copy_operator_call_count++;
        return *this;
    }

    FooA &operator=(FooA &&other) {
        val_a_ = other.val_a_;
        other.val_a_ = 0;
        FooA::call_info.move_operator_call_count++;
        return *this;
    }

    void some_foo_func() {
        std::cout << "call FooA some_foo_func" << std::endl;
    }

private:
    int val_a_;
};

class FooB : public FooA {
public:
    static reflection_helper call_info;

    FooB() : val_a_(0) {
        std::cout << "call FooB constuctor" << std::endl;
        arr_b = new double[1000000000];
    }

    FooB(int val_a) : val_a_(val_a) {}

    ~FooB() {
        FooB::call_info.destructor_call_count++;
        val_a_ = (0);
        delete arr_b;
        arr_b = nullptr;
        std::cout << "call FooB destructor" << std::endl;
    }

    FooB(FooB &&v) : val_a_(v.val_a_), arr_b(v.arr_b) {
        v.val_a_ = 0;
        v.arr_b = nullptr;
        FooA::call_info.move_constructor_call_count++;
    }

    FooB(const FooB &v) : val_a_(v.val_a_) {
        FooA::call_info.copy_constructor_call_count++;
    }

    FooB &operator=(const FooB &other) {
        val_a_ = other.val_a_;
        FooA::call_info.copy_operator_call_count++;
        return *this;
    }

    FooB &operator=(FooB &&other) {
        val_a_ = other.val_a_;
        other.val_a_ = 0;
        FooA::call_info.move_operator_call_count++;
        return *this;
    }

    void some_foo_func() {
        std::cout << "call FooB some_foo_func" << std::endl;
    }

private:
    int val_a_;
    double *arr_b;
};
} // namespace test
