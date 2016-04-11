#pragma once

#include <pebble.h>
#include "ride.h"
#include "cue_sheet_view.h"

#define PERSIST_CUE_NUMBER 1
#define PERSIST_RIDE_NUMBER 2

typedef struct {
  int ride_number;
  int cue_number;
  ride_t *ride_list;
  cue_sheet_view_t view;
} cue_sheet_data_t;

int cue_sheet_data_get_distance(cue_sheet_data_t* data);
char* cue_sheet_data_get_description(cue_sheet_data_t* data);
char cue_sheet_data_get_direction(cue_sheet_data_t* data);
void cue_sheet_data_next_cue(cue_sheet_data_t* data);
void cue_sheet_data_prev_cue(cue_sheet_data_t* data);
void cue_sheet_data_next_ride(cue_sheet_data_t* data);
void cue_sheet_data_init(cue_sheet_data_t* data);
