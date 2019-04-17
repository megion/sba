#include "utils/string-test.h"
#include "utils/wrapper-test.h"
#include "utils/ptr-test.h"
#include "utils/auto-ptr-test.h"

int main(int argc, char **argv) {
    test::wrapper_test();
    test::string_test();
    test::ptr_test();
    test::auto_ptr_test();
    return 0;
}
