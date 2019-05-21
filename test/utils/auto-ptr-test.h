#pragma once

#include "test.h"
#include "utils/AutoPtr.h"

namespace test {

void auto_ptr_test();

class Parent {
public:
    virtual void foo(){};
};

class Child : public Parent {};

} // namespace test
