#pragma once

typedef struct Grid {
  char* grid;
  int gridStride;
  int gridSize;
} Grid;

Grid createGrid();

void simulate(Grid* grid);
