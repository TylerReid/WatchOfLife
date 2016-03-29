#include <pebble.h>
#include "grid.h"
#include "render.h"

static Window *s_main_window;
static Layer *s_cell_layer;
static Grid s_grid;
static TextLayer *s_time_layer;

void setTime() {
  //todo figure out the max time text size. Probably 15 would be plenty
  static char timeText[50];
  clock_copy_time_string(timeText, 50);
  text_layer_set_text(s_time_layer, timeText);
}

static void handle_second_tick(struct tm* tick_time, TimeUnits units) {
  //run one step of the game of life
  simulate(s_grid);
  //the layer needs to be marked as dirty so that the layer will be re-drawn with the new grid
  layer_mark_dirty(s_cell_layer);
  //update the time once a minute
  if (tick_time->tm_sec == 0) {
    setTime();
  }
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
  //create layer for time text
  GRect textBounds = GRect(0, 144, bounds.size.w, 24);
  s_time_layer = text_layer_create(textBounds);
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorRed);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_main_window), text_layer_get_layer(s_time_layer));
  //set time initially
  setTime();
  
  //subscribe to the timer service so that the simulation will happen every second
  time_t now = time(NULL);
  struct tm *currentTime = localtime(&now);
  handle_second_tick(currentTime, SECOND_UNIT);
  tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
}

static void main_window_unload(Window * window) {
  text_layer_destroy(s_time_layer);
  layer_destroy(s_cell_layer);
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
