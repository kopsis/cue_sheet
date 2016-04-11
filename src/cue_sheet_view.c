#include <pebble.h>

#include "cue_sheet_view.h"
#include "cue_sheet_data.h"

void cue_sheet_view_dump_to_log(void* data) {
  cue_sheet_data_t* temp = data;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "distance_layer: 0x%08X", (unsigned int)(temp->view.distance_layer));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "description_layer: 0x%08X", (unsigned int)(temp->view.description_layer));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "icon_layer: 0x%08X", (unsigned int)(temp->view.icon_layer));
}

void cue_sheet_view_update_distance(cue_sheet_data_t* data) {
  int distance = cue_sheet_data_get_distance(data);
  snprintf(data->view.distance_text, 8, "%3d.%1d", distance/10, distance%10);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", data->view.distance_text);
  text_layer_set_text(data->view.distance_layer, data->view.distance_text);
}

void cue_sheet_view_update_description(cue_sheet_data_t* data) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", cue_sheet_data_get_description(data));
  text_layer_set_text(data->view.description_layer, cue_sheet_data_get_description(data));
}

void cue_sheet_view_set_icon(cue_sheet_view_t *view, char direction) {
  if (view->icon != NULL) {
    gdraw_command_image_destroy(view->icon);
    view->icon = NULL;
  }
  switch (direction) {
    case 'L':
      // Left
      view->icon = gdraw_command_image_create_with_resource(RESOURCE_ID_ICON_ARROW_LEFT);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "left icon: 0x%0X", (unsigned int)(view->icon));
      break;
    default:
      // Right
      view->icon = gdraw_command_image_create_with_resource(RESOURCE_ID_ICON_ARROW_RIGHT);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "right icon: 0x%0X", (unsigned int)(view->icon));
  }
}

void cue_sheet_view_update(Window* window, void* data) {
  cue_sheet_view_t* view = &((cue_sheet_data_t*)data)->view;
  
  cue_sheet_view_update_distance(data);
  cue_sheet_view_update_description(data);
  cue_sheet_view_set_icon(view, cue_sheet_data_get_direction(data));
  layer_mark_dirty(window_get_root_layer(window));
}
