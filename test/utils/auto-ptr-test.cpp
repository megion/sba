#include "utils/auto-ptr-test.h"

namespace test {

static void test_convert() {
    Child* child = new Child();
    sba::utils::AutoPtr<Child> p_child = child; // OK it works
    //sba::utils::AutoPtr<Child> p_child(child); // OK it works

    /* 
     * TODO error. It doesn't work because there is not AutoPtr(const AutoPtr &a)
     * AutoPtr<Parent> px = &x => 
     * const AutoPtr<Parent> temp(&x); 
     * AutoPtr<Parent> px(&x); // there is not
     */
    //sba::utils::AutoPtr<Parent> p_parent = p_child;
    
    // OK convert Child* to Parent*
    //sba::utils::AutoPtr<Parent> p_parent(p_child);

    //my_assert(py.get() == px.get());
}

void auto_ptr_test() {
    suite("AutoPtr");
    mytest(convert);
}

} // namespace test
