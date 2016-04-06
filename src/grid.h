#pragma once

typedef struct Grid {
  char* grid;
  char* tempGrid;
  int gridStride;
  int gridSize;
} Grid;

Grid createGrid();

Grid getRandomGrid(Grid current);

void simulate(Grid* grid);
