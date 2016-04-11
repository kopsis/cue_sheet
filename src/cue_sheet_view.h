#pragma once

#include <pebble.h>

typedef struct {
  TextLayer *fake_statusbar;
  Layer *horizontal_ruler_layer;
  TextLayer *distance_layer;
  TextLayer *description_layer;
  Layer *icon_layer;
  GDrawCommandImage *icon;
  char distance_text[8];
} cue_sheet_view_t;

void cue_sheet_view_dump_to_log(void* data);

void cue_sheet_view_set_icon(cue_sheet_view_t *view, char direction);

void cue_sheet_view_deinit(cue_sheet_view_t *model);

void cue_sheet_view_update(Window* window, void* data);
