#include <pebble.h>

#include "cue_sheet_view.h"
#include "cue_sheet_data.h"

void cue_sheet_view_update_distance(cue_sheet_data_t* data) {
  char buff[16];
  snprintf(buff, 16, "%3.1f", cue_sheet_data_get_distance(data));
  text_layer_set_text(data->view.distance_layer, buff);
}

void cue_sheet_view_update_description(cue_sheet_data_t* data) {
  text_layer_set_text(data->view.description_layer, cue_sheet_data_get_description(data));
}

void cue_sheet_view_set_icon(cue_sheet_view_t *view, char direction) {
  switch (direction) {
    case 'L':
      // Left
      view->icon = gdraw_command_image_create_with_resource(RESOURCE_ID_ICON_ARROW_LEFT);
    default:
      // Right
      view->icon = gdraw_command_image_create_with_resource(RESOURCE_ID_ICON_ARROW_RIGHT);
  }
}

void cue_sheet_view_update_icon(cue_sheet_data_t* data) {
  
}

void cue_sheet_view_update(Window* window, void* data) {
  cue_sheet_view_t* view = &((cue_sheet_data_t*)data)->view;
  
  cue_sheet_view_update_distance(data);
  cue_sheet_view_update_description(data);
  cue_sheet_view_set_icon(view, cue_sheet_data_get_direction(data));
  cue_sheet_view_update_icon(data);
  layer_mark_dirty(window_get_root_layer(window));
}
