#include "utils/auto-ptr-test.h"

namespace test {

void test_convert() {
    Parent x;
    sba::utils::AutoPtr<Parent> px(&x); // OK it works
    sba::utils::AutoPtr<Parent> px = &x; // TODO error. Why does not it work?

    sba::utils::AutoPtr<Child> py = px; // OK convert Child* to Parent*

    my_assert(py.get() == px.get());
}

void auto_ptr_test() {
    suite("AutoPtr");
    mytest(convert);
}

} // namespace test
