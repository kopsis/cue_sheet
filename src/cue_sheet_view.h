#pragma once

#include <pebble.h>

struct cue_sheet_view_t;

typedef void (*cue_sheet_view_func_t)(struct cue_sheet_view_t* model);

typedef struct {
  TextLayer *fake_statusbar;
  Layer *horizontal_ruler_layer;
  TextLayer *distance_layer;
  TextLayer *description_layer;
  Layer *icon_layer;
  cue_sheet_view_func_t announce_changed;
  struct {
    GDrawCommandImage *draw_command;
    int32_t to_square_normalized;
  } icon;
} cue_sheet_view_t;

//! calls model's .announce_changed or does nothing if NULL
void cue_sheet_main_window_view_announce_changed(cue_sheet_view_t *model);

void cue_sheet_view_set_icon(cue_sheet_view_t *model, GDrawCommandImage *image);

//GDrawCommandImage *cue_sheet_create_icon(WeatherAppDataPoint *data_point);

void cue_sheet_view_deinit(cue_sheet_view_t *model);
