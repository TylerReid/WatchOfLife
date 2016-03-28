#pragma once

#define GRID_STRIDE 12
#define GRID_SIZE GRID_STRIDE * GRID_STRIDE

typedef struct Grid {
  int* grid;
  int gridStride;
  int gridSize;
} Grid;

Grid createGrid();

void simulate(Grid grid);
