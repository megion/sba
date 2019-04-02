#include "utils/string-test.h"
#include "utils/wrapper-test.h"
#include "utils/ptr-test.h"

int main(int argc, char **argv) {
    test::wrapper_test();
    test::string_test();
    test::ptr_test();
    return 0;
}
