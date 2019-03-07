#include "string-test.hpp"

namespace test {

void test_init_string() {
    sba::utils::String *a = new sba::utils::String("test");
    delete a;
}

void test_read_string() {
    const sba::utils::String a = "test"; // const
    char e = a[1];                       // a.operator[](1)
    my_assert(e == 'e');

    // a[2] = 'd'; // a.operator[](2) - error: a[2] is not lvalue (locator
    // value)
}

void test_change_string() {
    sba::utils::String a = "test";
    char e = a[1]; // a.operator[](1).operator char()
    my_assert(e == 'e');

    /*
     * a.operator[](2).operator=('d')
     *
     * 1) a.operator[](2) => Cref
     * 2) Cref.operator= => String::write
     */
    a[2] = 'd';
    my_assert(a[2] == 'd');
}

void test_copy_on_write_technique() {
    sba::utils::String a = "test";
    sba::utils::String b = a;
    sba::utils::String c = "other_str";
    c = a; // assign operator
    /* here a,b,c have representation linked to one value */

    my_assert(a[1] == 'e');
    my_assert(b[1] == 'e');
    my_assert(c[1] == 'e');

    // change a
    a[1] = 'd';

    my_assert(a[1] == 'd');
    my_assert(b[1] == 'e');
    my_assert(c[1] == 'e');
}

void test_shared_representation() {
    sba::utils::String a = "test";
    my_assert(a.get_request_count() == 1);
    sba::utils::String b = a;
    my_assert(a.get_request_count() == 2);
    my_assert(b.get_request_count() == 2);
    sba::utils::String c = "other_str";
    c = a; // assign operator
    /* here a,b,c have representation linked to one value */
    my_assert(a.get_request_count() == 3);
    my_assert(b.get_request_count() == 3);
    my_assert(c.get_request_count() == 3);

    // change a
    a[1] = 'd';

    my_assert(a.get_request_count() == 1);
    my_assert(b.get_request_count() == 2);
    my_assert(c.get_request_count() == 2);
}

void test_shared_representation_and_destructors() {
    sba::utils::String a = "test";

    for (size_t i = 0; i < 10; i++) {
        my_assert(a.get_request_count() == 1);
        sba::utils::String b = "other";
        my_assert(b.get_request_count() == 1);
        b = a;
        my_assert(a.get_request_count() == 2);
        my_assert(b.get_request_count() == 2);
        // before next iteration b will be deleted
    }
    my_assert(a.get_request_count() == 1);
}

void test_assign_cstring() {
    sba::utils::String a = "test";

    for (size_t i = 0; i < 10; i++) {
        my_assert(a.get_request_count() == 1);
        a = "cstring";
        my_assert(a.get_request_count() == 1);
        my_assert(a[1] == 's');
        my_assert(a.size() == 7);

        sba::utils::String b = "other_str";
        a = b;
        my_assert(a.get_request_count() == 2);
        my_assert(a.size() == 9);
        my_assert(a[1] == 't');
    }
    my_assert(a.get_request_count() == 1);
    my_assert(a.size() == 9);
    my_assert(a[1] == 't');
}

/*
 * test operator+=
 */
void test_concat_operator() {
    sba::utils::String a = "test";
    my_assert(a.get_request_count() == 1);
    // concat char*
    a += "abc";
    my_assert(a.get_request_count() == 1);
    my_assert(a.size() == 7);
    my_assert(a[4] == 'a');

    sba::utils::String b = "efg";
    // concat String
    a += b;
    my_assert(a.get_request_count() == 1);
    my_assert(b.get_request_count() == 1);

    my_assert(a.size() == 10);
    my_assert(a[9] == 'g');

    sba::utils::String c = a;
    my_assert(a.get_request_count() == 2);
    my_assert(c.get_request_count() == 2);

    a += c;
    my_assert(a.get_request_count() == 1);
    my_assert(c.get_request_count() == 1);

    my_assert(a.size() == 20);
    my_assert(a[19] == 'g');
}

void string_test() {
    suite("String");
    mytest(init_string);
    mytest(read_string);
    mytest(change_string);
    mytest(copy_on_write_technique);
    mytest(shared_representation);
    mytest(shared_representation_and_destructors);
    mytest(assign_cstring);
    mytest(concat_operator);
}

} // namespace test
