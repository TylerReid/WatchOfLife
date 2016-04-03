#pragma once

typedef struct Grid {
  char* grid;
  int gridStride;
  int gridSize;
} Grid;

Grid createGrid();

Grid getRandomGrid(Grid current);

void simulate(Grid* grid);
