#include "vex.h"

/*---------------------------------------------------------------------------
  Competition

    -Definition of Competiton provided by Vex Coding Studio

---------------------------------------------------------------------------*/

competition Competition = competition();

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
