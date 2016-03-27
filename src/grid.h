#pragma once

#define GRID_STRIDE 8
#define GRID_SIZE GRID_STRIDE * GRID_STRIDE

typedef struct Grid {
  int* grid;
  int gridStride;
  int gridSize;
} Grid;

void printGrid(Grid grid);

void getGridText(Grid grid, char* text);

Grid createGrid();

void simulate(Grid grid);

char* allocateText();
