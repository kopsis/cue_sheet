#include <pebble.h>
#include "ride.h"

ride_entry_t spring_classic_100[] = {
  {1, 'L', "17th St. W/Memphis Rd"},
  {21, 'L', "16th Ave E/Canal Rd"},
  {42, 'L', "49th St E/Experimental Farm Rd"},
  {52, 'R', "US-19 N"},
  {70, 'L', "73rd St W/Terra Ceia Rd"},
  {84, 'R', "63rd St W/Bayshore Dr"},
  {92, 'S', "Rest Stop #1"},
  {114, 'R', "72nd St W/Terra Ceia Rd"},
  {123, 'L', "Bayshore Rd/Old U.S. 41 S"},
  {126, 'L', "79th St E"},
  {129, 'R', "Slight right onto Bishop Harbor Rd"},
  {158, 'L', "36th Ave E/Bud Rhoden Rd"},
  {173, 'R', "Buckeye Rd"},
  {206, 'R', "Carter Rd"},
  {225, 'R', "97th St E/Moccasin Wallow Rd"},
  {253, 'L', "36th ave E/Ellenton Gillette Rd"},
  {270, 'L', "69th St E"},
  {276, 'L', "Rest Stop #2"},
  {303, 'L', "Erie Rd"},
  {337, 'R', "US-301 S"},
  {344, 'L', "Rutland Rd"},
  {455, 'S', "Rest Stop #3"},
  {455, 'R', "Turn right on State Rte 64 W"},
  {457, 'L', "Cr 675/Waterbury Rd"},
  {512, 'L', "SR70/Oneca Myakka City Rd"},
  {537, 'R', "Verna Rd"},
  {562, 'L', "Historic Florida 780E/Singletary Rd"},
  {600, 'L', "SR70/Oneca Myakka City Rd"},
  {635, 'R', "Verna Bethany Rd"},
  {685, 'L', "State Rte 64 W"},
  {705, 'S', "Rest Stop #4"},
  {736, 'R', "Dam Rd"},
  {771, 'R', "Sharp right turn onto Rye Rd E"},
  {824, 'L', "Golf Course Rd"},
  {843, 'S', "Rest Stop #5"},
  {859, 'L', "Fort Hamer Rd"},
  {865, 'R', "Old Tampa Rd"},
  {920, 'L', "69th St E"},
  {947, 'L', "Rest Stop #6"},
  {952, 'L', "36th Ave E/Ellenton Gillete Rd"},
  {965, 'R', "49th St E/Experimental Rd"},
  {977, 'L', "16th Ave. E/Canal Rd"},
  {997, 'R', "17th St E"},
  {1018, 'R', "14th Ave W"}
};

ride_t ride_list[] = {
  {43, spring_classic_100},
  {0, NULL}
};
