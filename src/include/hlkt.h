#ifndef HLKT_H
#define HLKT_H

#include <time.h>

#include "util.h"

static int hlkt_run     = 0;     /* number of tests run */
static int hlkt_failed  = 0;     /* number of tests that have failed */

#define HLKT_HIDE(stuff) do { stuff } while (0)

#define HLKT_LOG() HLKT_HIDE(                                  \
   if ((hlkt_run > 0) && (hlkt_failed > 0)) {                  \
      log_war("HLKT: %d/%d tests failed", hlkt_failed, hlkt_run);    \
   } else {                                                    \
      log_inf("HLKT: all %d tests passed", hlkt_run);                \
   }                                                           \
)

#define HLKT_ASS(pred) HLKT_HIDE(                                                \
   hlkt_run ++;                                                                  \
   if (! pred) {                                                                 \
      hlkt_failed ++;                                                            \
      log_err("HLKT: test [%s] failed: %s:%s:%d", #pred, __FILE__, __func__, __LINE__);\
   }                                                                             \
)

#endif
