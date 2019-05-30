#pragma once

#include "test.h"

namespace test {

void allocator_test();

class Arena {
public:
    virtual void *alloc(size_t) = 0;
    virtual void free(void *, size_t) = 0;
};

class Persistent : public Arena {
public:
    Persistent() : len_(0) {}

public:
    void *alloc(size_t sz) {
        len_ += sz;
        return &buff_[len_];
    };

    void free(void *b, size_t sz) {
        void *dest = b + sz;
        std::memcpy(b, dest, len_ - (b + sz - buff_));
    };

private:
    char buff_[100];
    size_t len_;
};

} // namespace test

void *operator new(size_t sz, test::Arena *a);
