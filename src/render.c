#include <pebble.h>
#include "render.h"
#include "grid.h"

int getRectSide(GRect boundsOfWindow, Grid grid) {
  int width = boundsOfWindow.size.w / grid.gridStride;
  //int height = boundsOfWindow.size.h / grid.gridStride;
  
  return width;
}

int getNumberOfColumns(GRect boundsOfWindow, int rectSide) {
  int columns = boundsOfWindow.size.w / rectSide;
  return columns;
}

void drawGrid(Layer* layer, GContext* ctx, Grid grid) {
  GRect boundsOfLayer = layer_get_bounds(layer);
  int rectSide = getRectSide(boundsOfLayer, grid);
  int numberOfColumns = getNumberOfColumns(boundsOfLayer, rectSide);
  
  GPoint currentOriginLocation = boundsOfLayer.origin;
  
  for (int i = 0; i < grid.gridSize; i++) {
    if(grid.grid[i] == 1) {
      graphics_context_set_fill_color(ctx, GColorWhite);
    } else {
      graphics_context_set_fill_color(ctx, GColorTiffanyBlue);
    }
    
    GRect cell = GRect(currentOriginLocation.x, currentOriginLocation.y, rectSide, rectSide);
    //graphics_draw_rect(ctx, cell);
    graphics_fill_rect(ctx, cell, 8, GCornersAll);
    
    bool wrapThisIteration;
    wrapThisIteration = (i + 1) % numberOfColumns == 0;
    
    if (wrapThisIteration) {
      currentOriginLocation = GPoint(0, currentOriginLocation.y + rectSide);
    } else {
      currentOriginLocation = GPoint(currentOriginLocation.x + rectSide, currentOriginLocation.y);
    }
  }
}
