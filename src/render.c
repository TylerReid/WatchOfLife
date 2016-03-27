#include <pebble.h>
#include "render.h"
#include "grid.h"

int numberOfRectForGridSize(GRect boundsOfWindow) {
  int width = boundsOfWindow.size.w / GRID_STRIDE;
  int height = boundsOfWindow.size.h / GRID_STRIDE;
  
  return width * height;
}

void drawGrid(Layer* layer, GContext* ctx, Grid grid) {
  GRect boundsOfLayer = layer_get_bounds(layer);
  int numberOfRects = numberOfRectForGridSize(boundsOfLayer);
  
  
  
  graphics_context_set_fill_color(ctx, GColorWhite);
  GRect rect = GRect(10,10,20,20);
  graphics_draw_rect(ctx, rect);
  graphics_fill_rect(ctx, rect, 0, GCornerNone);
  
  graphics_context_set_fill_color(ctx, GColorBlack);
  rect = GRect(30,10,20,20);
  graphics_draw_rect(ctx, rect);
  graphics_fill_rect(ctx, rect, 0, GCornerNone);
}
