#pragma once

#define GRID_STRIDE 8
#define GRID_SIZE GRID_STRIDE * GRID_STRIDE

typedef struct Grid {
  int* grid;
  int gridStride;
  int gridSize;
} Grid;

void printGrid(int grid[]);

void getGridText(int* grid, char* text);

int* createGrid();

void simulate(int * grid);

char* allocateText();
