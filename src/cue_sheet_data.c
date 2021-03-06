#include <pebble.h>
#include "cue_sheet_data.h"

int cue_sheet_data_get_distance(cue_sheet_data_t* data) {
  return (data->ride_list[data->ride_number].ride[data->cue_number].distance);
}

char* cue_sheet_data_get_description(cue_sheet_data_t* data) {
  return (data->ride_list[data->ride_number].ride[data->cue_number].cue);
}

char cue_sheet_data_get_direction(cue_sheet_data_t* data) {
  return (data->ride_list[data->ride_number].ride[data->cue_number].direction);
}

void cue_sheet_data_next_cue(cue_sheet_data_t* data) {
  int max_cue = data->ride_list[data->ride_number].max_cue;
  if (data->cue_number < max_cue) {
    data->cue_number++;
  }
  persist_write_int(PERSIST_CUE_NUMBER, data->cue_number);
}

void cue_sheet_data_prev_cue(cue_sheet_data_t* data) {
  if (data->cue_number > 0) {
    data->cue_number--;
  }
  persist_write_int(PERSIST_CUE_NUMBER, data->cue_number);
}

void cue_sheet_data_next_ride(cue_sheet_data_t* data) {
  data->ride_number++;
  if (data->ride_list[data->ride_number].max_cue == 0) {
    data->ride_number = 0;
  }
  persist_write_int(PERSIST_RIDE_NUMBER, data->ride_number);
}

void cue_sheet_data_init(cue_sheet_data_t* data) {
  data->ride_number = persist_read_int(PERSIST_RIDE_NUMBER);
  data->cue_number = persist_read_int(PERSIST_CUE_NUMBER);
}
