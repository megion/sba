#include "wrapper-test.h"

namespace test {

reflection_helper FooA::call_info = reflection_helper();
reflection_helper FooB::call_info = reflection_helper();

void test_swap() {
    FooA *a = new FooB();
    a->some_foo_func();

    FooB *b = new FooB();
    b->some_foo_func();

    delete a;
    delete b;
    // sba::utils::swap();
    // std::assert(childIndex == 3);
}

void wrapper_test() {
    suite("wrapper");
    mytest(swap);
}

//}
//}
} // namespace test
