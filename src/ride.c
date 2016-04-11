#include <pebble.h>
#include "ride.h"

ride_entry_t spring_classic_100[] = {
  {0.0, 'L', "Start"},
  {1.0, 'R', "Go Back"}
};

ride_t ride_list[] = {
  {1, spring_classic_100},
  {0, NULL}
};
