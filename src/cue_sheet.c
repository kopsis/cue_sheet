#include <pebble.h>
#include "ride.h"

#define PERSIST_RIDE_NUMBER 1
#define PERSIST_CUE_NUMBER 2

static Window *window;
static TextLayer *text_layer;

// Indices into ride global data structures. These are synced to 
// persistent storage.
static int ride_number;
static int cue_number;

// Pointer to currently selected ride
static ride_entry_ptr_t current_ride;

// Global ride list from ride.c
extern ride_t ride_list[];

// Display the current cue sheet item
static void update_cue(void) {
  text_layer_set_text(text_layer, current_ride[PERSIST_CUE_NUMBER].cue);
  persist_write_int(PERSIST_CUE_NUMBER, cue_number);
}

// SELECT button
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  ride_number++;
  if (ride_list[ride_number].max_cue == 0) {
    ride_number = 0;
  }
  persist_write_int(PERSIST_RIDE_NUMBER, ride_number);
  current_ride = ride_list[ride_number].ride;
  update_cue();
}

// UP button
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (cue_number > 0) {
    cue_number--;
    update_cue();
  }
}

// DOWN button
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (cue_number <= ride_list[ride_number].max_cue) {
    cue_number++;
    update_cue();
  }
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

  const GRect frame = GRect(MARGIN - font_compensator, y, layer_get_bounds(parent_layer).size.w - 2 * MARGIN + 2 * font_compensator - additional_right_margin, h);

  *text_layer = text_layer_create(frame);
  text_layer_set_background_color(*text_layer, GColorClear);
  text_layer_set_text_color(*text_layer, PBL_IF_COLOR_ELSE(GColorWhite, GColorBlack));
  text_layer_set_font(*text_layer, fonts_get_system_font(font_key));
  layer_add_child(parent_layer, text_layer_get_layer(*text_layer));
  return frame;
}

static void window_load(Window *window) {
  cue_sheet_data_t *data = window_get_user_data(window);
  data->view_model.announce_changed = view_model_changed;

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
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
  data->current_ride = ride_list[ride_number].ride;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}