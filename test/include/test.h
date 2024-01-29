#ifndef TEST_H
#define TEST_H

#include "../../src/include/util.h"

/* 
   This is probably how it's supposed to work. In what other cases would you
   need `extern`?
*/
extern unsigned int TESTS_RUN;
extern unsigned int TESTS_PASSED;

#define TEST_INIT unsigned int TESTS_RUN = 0, TESTS_PASSED = 0;

#ifndef __func__
#define __func__ ""
#endif

#define ASSERT(EXPR) \
   TESTS_RUN++; \
   (EXPR && ++TESTS_PASSED) ? \
      log_inf("%s:%s:%d: Assertion passed!", __FILE__, __func__, __LINE__) : \
      log_err("%s:%s:%d: Assertion failed:\n\t%s", __FILE__, __func__, __LINE__, #EXPR);

#define TEST_REPORT \
   (TESTS_RUN == TESTS_PASSED) ? \
      log_yay("%s: All %d tests passed!", __FILE__, TESTS_RUN) : \
      log_err("%d/%d tests failed.", TESTS_RUN - TESTS_PASSED, TESTS_RUN);

#endif
