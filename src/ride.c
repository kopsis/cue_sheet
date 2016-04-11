#include <pebble.h>
#include "ride.h"

ride_entry_t spring_classic_100[] = {
  {0, 'L', "Start"},
  {15, 'R', "Turn right on some street"},
  {1025, 'L', "Have lunch"}
};

ride_t ride_list[] = {
  {2, spring_classic_100},
  {0, NULL}
};
