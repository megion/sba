#include "string-test.hpp"

namespace test {

void test_string_init() {
    sba::utils::String *a = new sba::utils::String("test");
    delete a;
}

void string_test() {
    suite("string_init");
    mytest(string_init);
}

} // namespace test
