#ifndef TEST_H
#define TEST_H

#include "../../src/include/util.h"

extern unsigned int TESTS_RUN;
extern unsigned int TESTS_PASSED;

#define ASSERT(EXPR) \
   TESTS_RUN++; \
   (EXPR && ++TESTS_PASSED) ? \
      log_inf("%s:%d: Assertion passed!", __FILE__, __LINE__) : \
      log_err("%s:%d: Assertion failed:\n\t%s", __FILE__, __LINE__, #EXPR);

#define TEST_REPORT \
   (TESTS_RUN == TESTS_PASSED) ? \
      log_yay("%s: All %d tests passed!", __FILE__, TESTS_RUN) : \
      log_err("%d/%d tests failed.", TESTS_RUN - TESTS_PASSED, TESTS_RUN);

#endif
