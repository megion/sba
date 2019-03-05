#include "string-test.hpp"

namespace test {

void test_init_string() {
    sba::utils::String *a = new sba::utils::String("test");
    delete a;
}

void test_read_string() {
    const sba::utils::String a = "test"; // const
    char e = a[1]; // a.operator[i]
    my_assert(e == 'i');
}

void string_test() {
    suite("init_string");
    mytest(init_string);

    suite("read_string");
    mytest(read_string);
}

} // namespace test
