#pragma once

#include "test.h"

namespace test {

void allocator_test();

class Arena {
public:
    virtual void *alloc(size_t) = 0;
    virtual void free(void *, size_t) = 0;
    virtual void *get_buff() = 0;

    virtual ~Arena(){};
};

class Persistent : public Arena {
public:
    Persistent() : len_(0) {}

    ~Persistent() {}

public:
    void *alloc(size_t sz) {
        size_t l = len_;
        len_ += sz;
        return (buff_ + l);
    };

    void free(void *b, size_t sz) {
        /*
         * TODO: move data from endRemovingData to startRemovingData
         * void * destination, const void * source, size_t num
         *
         * data view:
         * 0----startRemoving---endRemoving-----len_
         *
         * after free:
         * 0---------len_
         */
        char *startRemovingData = (char *)b;
        char *endRemovingData = startRemovingData + sz;
        std::memcpy(startRemovingData, endRemovingData,
                    len_ - (endRemovingData - buff_));
        len_ -= sz;
    };

    void *get_buff() {
        return buff_;
    }

private:
    char buff_[100];
    size_t len_;
};

class AA {
public:
    ~AA() { std::cout << "AA destructor" << std::endl; }

public:
    char data_[10] = "hello";
};

} // namespace test

void *operator new(size_t sz, test::Arena *a);

template <typename T>
void print_bytes(const T &input, std::ostream &os = std::cout) {
    const char *p = reinterpret_cast<const char *>(&input);
    //os << std::hex << std::showbase;
    os << "[";
    for (size_t i = 0; i < sizeof(T); ++i) {
        os << (*(p + i)) << " ";
    }
    os << "]" << std::endl;
}
