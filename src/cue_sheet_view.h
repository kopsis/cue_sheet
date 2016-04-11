#pragma once

#include <pebble.h>

typedef struct {
  TextLayer *fake_statusbar;
  Layer *horizontal_ruler_layer;
  TextLayer *distance_layer;
  TextLayer *description_layer;
  Layer *icon_layer;
  GDrawCommandImage *icon;
} cue_sheet_view_t;

//! calls model's .announce_changed or does nothing if NULL
void cue_sheet_main_window_view_announce_changed(cue_sheet_view_t *model);

void cue_sheet_view_set_icon(cue_sheet_view_t *view, char direction);

void cue_sheet_view_deinit(cue_sheet_view_t *model);

void cue_sheet_view_update(Window* window, void* data);
