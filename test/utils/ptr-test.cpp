#include "utils/ptr-test.h"

namespace test {

void test_convert() {
    //Shape s;
    //sba::utils::Ptr<Shape> ps = &s;

    Circle c;
    sba::utils::Ptr<Circle> pc = &c;
    sba::utils::Ptr<Shape> ps2 = pc; // OK convert Circle* to Shape*
    //sba::utils::Ptr<Circle> pc2 = ps; // should not compile

    my_assert(ps2.get() == pc.get());
}

void ptr_test() {
    suite("Ptr");
    mytest(convert);
}

} // namespace test
