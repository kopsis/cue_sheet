#pragma once

typedef struct {
  int distance;
  char direction;
  char cue[128];
} ride_entry_t;

typedef ride_entry_t* ride_entry_ptr_t;

typedef struct {
  int max_cue;
  ride_entry_ptr_t ride;
} ride_t;
