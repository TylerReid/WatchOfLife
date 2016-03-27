#include <pebble.h>
#include "grid.h"
#include "render.h"

static Window *s_main_window;
static Layer *s_cell_layer;
static Grid s_grid;

static void handle_second_tick(struct tm* tick_time, TimeUnits units) {
  simulate(s_grid);
  layer_mark_dirty(s_cell_layer);
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  //this is where the drawing happens
  drawGrid(layer, ctx, s_grid);
}

static void main_window_load(Window *window) {
  //get the bounds of the window and create the cell layer
  GRect bounds = layer_get_bounds(window_get_root_layer(s_main_window));
  s_cell_layer = layer_create(bounds);
  //add the callback for the drawing function
  layer_set_update_proc(s_cell_layer, canvas_update_proc);
  //add to the window
  layer_add_child(window_get_root_layer(s_main_window), s_cell_layer);
  
  time_t now = time(NULL);
  struct tm *currentTime = localtime(&now);
  handle_second_tick(currentTime, SECOND_UNIT);
  
  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
}

static void main_window_unload(Window * window) {
  
}

static void init() {
  s_grid = createGrid();
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
  free(s_grid.grid);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
