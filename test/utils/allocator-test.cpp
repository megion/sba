#include "utils/allocator-test.h"
#include <memory>

void *operator new(size_t sz, test::Arena *a) {
    std::cout << "overloaded new operator" << std::endl;
    return a->alloc(sz);
}

namespace test {

static void test_allocate_memory() {
    Arena *persistent = new Persistent();
    char *d1 = (char *)persistent->alloc(2);
    d1[0] = 'a';
    d1[1] = 'b';

    char *d2 = (char *)persistent->alloc(3);
    d2[0] = 'c';
    d2[1] = 'd';
    d2[2] = 'f';

    char *d3 = (char *)persistent->alloc(2);
    d3[0] = 'g';
    d3[1] = 'h';

    my_assert(d1[0] == 'a');
    my_assert(d1[1] == 'b');

    my_assert(d2[0] == 'c');
    my_assert(d2[1] == 'd');
    my_assert(d2[2] == 'f');

    my_assert(d3[0] == 'g');
    my_assert(d3[1] == 'h');

    persistent->free(d2, 3);

    /*
     * TODO: update pointers, but it is hack.
     */
    d3 = d3 - 3;

    my_assert(d1[0] == 'a');
    my_assert(d1[1] == 'b');
    my_assert(d3[0] == 'g');
    my_assert(d3[1] == 'h');

    delete persistent;
}

static void test_overloaded_new_operator() {
    Arena *persistent = new Persistent();

    AA* p = new (Persistent)AA();

    p->~AA();

    delete persistent;
}

void allocator_test() {
    suite("Allocator");
    mytest(allocate_memory);
}

} // namespace test
