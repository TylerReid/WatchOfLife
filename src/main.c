#include <pebble.h>
#include "grid.h"

static Window *s_main_window;
static TextLayer *s_grid_layer;
static Layer *s_cell_layer;
static int* s_grid;

char* text;

static void handle_second_tick(struct tm* tick_time, TimeUnits units) {
  simulate(s_grid);
  getGridText(s_grid, text);
  
  text_layer_set_text(s_grid_layer, text);
}

static void main_window_load(Window *window) {
  Layer *windowLayer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(windowLayer);
  
  s_grid_layer = text_layer_create(bounds);
  text_layer_set_text_color(s_grid_layer, GColorWhite);
  text_layer_set_background_color(s_grid_layer, GColorClear);
  text_layer_set_font(s_grid_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(s_grid_layer, GTextAlignmentCenter);
  
  time_t now = time(NULL);
  struct tm *currentTime = localtime(&now);
  handle_second_tick(currentTime, SECOND_UNIT);
  
  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
  
  layer_add_child(windowLayer, text_layer_get_layer(s_grid_layer));
}

static void main_window_unload(Window * window) {
  
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  //this is where the drawing happens
  graphics_context_set_fill_color(ctx, GColorWhite);
  GRect rect = GRect(10,10,20,20);
  graphics_draw_rect(ctx, rect);
  graphics_fill_rect(ctx, rect, 0, GCornerNone);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  rect = GRect(30,10,20,20);
  graphics_draw_rect(ctx, rect);
  graphics_fill_rect(ctx, rect, 0, GCornerNone);
}

static void init() {
  s_grid = createGrid();
  text = allocateText();
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorTiffanyBlue);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
  //get the bounds of the window and create the cell layer
  GRect bounds = layer_get_bounds(window_get_root_layer(s_main_window));
  s_cell_layer = layer_create(bounds);
  //add the callback for the drawing function
  layer_set_update_proc(s_cell_layer, canvas_update_proc);
  //add to the window
  layer_add_child(window_get_root_layer(s_main_window), s_cell_layer);
}

static void deinit() {
  window_destroy(s_main_window);
  free(text);
  free(s_grid);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
