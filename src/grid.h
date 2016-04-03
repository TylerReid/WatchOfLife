#pragma once

typedef struct Grid {
  int* grid;
  int gridStride;
  int gridSize;
} Grid;

Grid createGrid();

void simulate(Grid* grid);
