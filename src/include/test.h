#ifndef TEST_H
#define TEST_H

#include "util.h"

#ifdef TEST

unsigned int TESTS_RUN = 0;
unsigned int TESTS_PASSED = 0;

#define ASSERT(EXPR) \
   TESTS_RUN++; \
   (EXPR && ++TESTS_PASSED) ? \
      log_yay("Assertion passed!") : \
      log_err("%s:%d: Assertion failed:\n\t%s", __FILE__, __LINE__, #EXPR);

#define TEST_REPORT \
   (TESTS_RUN == TESTS_PASSED) ? \
      log_yay("All %d tests passed!", TESTS_RUN) : \
      log_err("%d/%d tests failed.", TESTS_RUN - TESTS_PASSED, TESTS_RUN);

#else
#define ASSERT(EXPR) NULL;
#endif

#endif
