#include "utils/auto-ptr-test.h"
#include <memory>

namespace test {

static void test_convert() {
    Child* child = new Child();
    //sba::utils::AutoPtr<Child> p_child = child; // Error it doesn't work
    sba::utils::AutoPtr<Child> p_child(child); // OK it works

    /* 
     * TODO error. It doesn't work because there is not AutoPtr(const AutoPtr &a)
     */
    //sba::utils::AutoPtr<Parent> p_parent = p_child;
    
    // OK convert Child* to Parent*
    sba::utils::AutoPtr<Parent> p_parent(p_child);

    my_assert(p_parent.get() != nullptr);
    my_assert(p_child.get() == nullptr);


    sba::utils::AutoPtr<Parent> p_parent2 = p_parent;

    my_assert(p_parent2.get() != nullptr);
    my_assert(p_parent.get() == nullptr);

    // downcast
    sba::utils::AutoPtr<Child> p_child2(p_parent2);
}

static void test_std_auto_ptr() {
    Child* child = new Child();
    //sba::utils::AutoPtr<Child> p_child = child; // Error it doesn't work
    std::auto_ptr<Child> p_child(child); // OK it works

    // OK convert Child* to Parent*
    std::auto_ptr<Parent> p_parent(p_child);

    my_assert(p_parent.get() != nullptr);
    my_assert(p_child.get() == nullptr);

    std::auto_ptr<Parent> p_parent2 = p_parent;

    my_assert(p_parent2.get() != nullptr);
    my_assert(p_parent.get() == nullptr);

    //std::auto_ptr<Child> p_child2(p_parent2);
}

void auto_ptr_test() {
    suite("AutoPtr");
    mytest(convert);
    mytest(std_auto_ptr);
}

} // namespace test
