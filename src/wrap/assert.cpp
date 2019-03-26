#include "wrap/assert.h"

namespace sba {
namespace wrap {

void __my_assert(const char *expr_str, bool expr, const char *file, int line) {
    if (!expr) {
        std::printf("%s:%d: %s %sAssertion%s \n", file, line, expr_str,
                    RED_COLOR, RESET_COLOR);
        std::exit(EXIT_FAILURE);
    }
}

} // namespace wrap 
} // namespace sba
