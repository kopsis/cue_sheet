#include <pebble.h>
#include "ride.h"
#include "cue_sheet_data.h"

static const int16_t MARGIN = 4;
static const int16_t ICON_DIMENSIONS = 40;

static Window *window;

// Global ride list from ride.c
extern ride_t ride_list[];

static void bg_update_proc(Layer *layer, GContext *ctx) {
  const GRect bounds = layer_get_bounds(layer);

  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
}

static void icon_layer_update_proc(Layer *layer, GContext *ctx) {
  cue_sheet_data_t *data = window_get_user_data(window);
  cue_sheet_view_t *view = &(data->view);
  graphics_context_set_antialiased(ctx, true);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_fill_color(ctx, GColorBlack);
  gdraw_command_image_draw(ctx, view->icon, GPoint(0, 0));
}

// SELECT button
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  Window *window = (Window *)context;
  cue_sheet_data_t* data = window_get_user_data(window);

  cue_sheet_data_next_ride(data);
  cue_sheet_view_update(window, data);
}

// UP button
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  Window *window = (Window *)context;
  cue_sheet_data_t* data = window_get_user_data(window);

  cue_sheet_data_prev_cue(data);
  cue_sheet_view_update(window, data);
}

// DOWN button
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  Window *window = (Window *)context;
  cue_sheet_data_t* data = window_get_user_data(window);

  cue_sheet_data_next_cue(data);
  cue_sheet_view_update(window, data);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

//! helper to construct the various text layers as they appear in this app
static GRect init_text_layer(Layer *parent_layer, TextLayer **text_layer, int16_t y, int16_t h, int16_t additional_right_margin, char *font_key) {
  // why "-1" (and then "+2")? because for this font we need to compensate for weird white-spacing
  const int16_t font_compensator = strcmp(font_key, FONT_KEY_LECO_38_BOLD_NUMBERS) == 0 ? 3 : 1;
  int width = layer_get_bounds(parent_layer).size.w - (2 * MARGIN) + (2 * font_compensator) - additional_right_margin;

  const GRect frame = GRect(MARGIN - font_compensator, y, width, h);

  *text_layer = text_layer_create(frame);
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "root width: %d", layer_get_bounds(parent_layer).size.w);
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "width: %d", width);
  text_layer_set_background_color(*text_layer, GColorClear);
  text_layer_set_text_color(*text_layer, PBL_IF_COLOR_ELSE(GColorBlack, GColorBlack));
  text_layer_set_font(*text_layer, fonts_get_system_font(font_key));
  layer_add_child(parent_layer, text_layer_get_layer(*text_layer));
  return frame;
}

static void window_load(Window *window) {
  cue_sheet_data_t *data = window_get_user_data(window);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  layer_set_update_proc(window_layer, bg_update_proc);

  const int16_t narrow_buffer = 5; // current whitespacing would trim 3-digit temperature otherwise
  const int16_t narrow = ICON_DIMENSIONS + 2 - narrow_buffer;

  const int16_t distance_top = 30;
  init_text_layer(window_layer, &(data->view.distance_layer), distance_top, 40, narrow, FONT_KEY_LECO_38_BOLD_NUMBERS);

  const int16_t description_top = 30 + 40 + 10;
  const int16_t description_height = bounds.size.h - description_top;
  init_text_layer(window_layer, &(data->view.description_layer), description_top, description_height, 0, FONT_KEY_GOTHIC_24_BOLD);
  
  GRect icon_rect = GRect(0, 0, ICON_DIMENSIONS, ICON_DIMENSIONS);
  GRect alignment_rect = GRect(0, distance_top, bounds.size.w - MARGIN, 10);
  grect_align(&icon_rect, &alignment_rect, GAlignTopRight, false);
  data->view.icon = NULL;
  data->view.icon_layer = layer_create(icon_rect);
  layer_set_update_proc(data->view.icon_layer, icon_layer_update_proc);
  layer_add_child(window_layer, data->view.icon_layer);
  cue_sheet_view_update(window, data);
}

static void window_unload(Window *window) {
  cue_sheet_data_t *data = window_get_user_data(window);

  text_layer_destroy(data->view.distance_layer);
  text_layer_destroy(data->view.description_layer);
  layer_destroy(data->view.icon_layer);
  if (data->view.icon != NULL) {
    gdraw_command_image_destroy(data->view.icon);
    data->view.icon = NULL;
  }
}

static void init(void) {
  cue_sheet_data_t *data = malloc(sizeof(cue_sheet_data_t));
  memset(data, 0, sizeof(cue_sheet_data_t));

  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_user_data(window, data);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  
  // Get ride and cue numbers (default to 0 if not saved)
  data->ride_number = persist_read_int(PERSIST_RIDE_NUMBER);
  data->cue_number = persist_read_int(PERSIST_CUE_NUMBER);
  data->ride_list = ride_list;
  window_stack_push(window, animated);
}

static void deinit(void) {
  void* data = window_get_user_data(window);
  free(data);
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}