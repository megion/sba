#include "utils/allocator-test.h"
#include <memory>

void* operator new(size_t sz, test::Arena* a) {
    return a->alloc(sz);
}

namespace test {

static void test_allocate_memory() {

    //my_assert(p_parent.get() == nullptr);
}

void allocator_test() {
    suite("Allocator");
    mytest(allocate_memory);
}

} // namespace test
