#ifndef TEST_TEST_H_
#define TEST_TEST_H_

#include <stdio.h>
#include <assert.h>

#include "utils/console_colors.h"

/*
 * Test the given `fn`.
 */
#define mytest(fn) \
  printf("    " GREEN_COLOR "✓ %s" RESET_COLOR "\n", #fn); \
  test_##fn();

/*
 * Test suite title.
 */
#define suite(title) \
  printf("\n  " CYAN_COLOR "%s" RESET_COLOR "\n", title)

#define assert_range(val, middle, offset) \
  assert( (middle-offset < val) && (val < middle+offset));

namespace test {
	namespace common {
		
	}
}

#endif /* TEST_TEST_H_ */
