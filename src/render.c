#include <pebble.h>
#include "render.h"
#include "grid.h"

int getRectSide(GRect boundsOfWindow, Grid grid) {
  //the side of our rectangle will be the number of times the stride fits in the width
  int width = (boundsOfWindow.size.w + (grid.gridStride - 1))/ grid.gridStride;
  return width;
}

void drawGrid(Layer* layer, GContext* ctx, Grid grid) {
  GRect boundsOfLayer = layer_get_bounds(layer);
  int cellSideLength = getRectSide(boundsOfLayer, grid);
  //start drawing from the top left, which is the origin
  GPoint currentOriginLocation = boundsOfLayer.origin;
  //loop through all of the grid cells and draw either a live cell or a dead one
  for (int i = 0; i < grid.gridSize; i++) {
    //if the cell is 1, it is alive so draw white, else draw teal
    if(grid.grid[i] == 1) {
      graphics_context_set_fill_color(ctx, GColorWhite);
    } else {
      graphics_context_set_fill_color(ctx, GColorTiffanyBlue);
    }
    //create cell to draw at the current location
    GRect cell = GRect(currentOriginLocation.x, currentOriginLocation.y, cellSideLength, cellSideLength);
    //fill with rounded edges
    graphics_fill_rect(ctx, cell, 8, GCornersAll);
    //if we are at the end of the row, we need to wrap to the next one
    bool wrapThisIteration;
    wrapThisIteration = (i + 1) % grid.gridStride == 0;
    
    if (wrapThisIteration) {
      currentOriginLocation = GPoint(0, currentOriginLocation.y + cellSideLength);
    } else {
      currentOriginLocation = GPoint(currentOriginLocation.x + cellSideLength, currentOriginLocation.y);
    }
  }
}
