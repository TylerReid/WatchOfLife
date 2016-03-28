#include <pebble.h>
#include "grid.h"

#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int numberOfNeighbors(int* grid, int cell);

Grid createGrid() {
  //inital condition of game grid
  int grid[GRID_SIZE] = 
  {
    0,0,0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,0,0,0,0,
    1,1,0,1,0,0,0,0,1,0,0,0,
    1,1,0,1,0,0,1,0,1,0,0,0,
    0,0,0,1,0,0,1,0,1,0,1,1,
    0,0,0,1,0,1,0,0,1,0,1,1,
    0,0,0,0,1,1,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,0,0,0,0,0,0,
    0,0,0,0,1,1,0,0,0,0,0,0,
  };
  //allocate heap space for array, and copy the initial data to the heap location
  int * gridP = (int *)malloc(GRID_SIZE * sizeof(int));
  memcpy(gridP, &grid, GRID_SIZE * sizeof(int));
  
  Grid gridStruct;
  gridStruct.grid = gridP;
  gridStruct.gridStride = GRID_STRIDE;
  gridStruct.gridSize = GRID_SIZE;
  return gridStruct;
}


/*
  1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
  2. Any live cell with two or three live neighbours lives on to the next generation.
  3. Any live cell with more than three live neighbours dies, as if by over-population.
  4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void simulate(Grid grid)
{
  int temp[GRID_SIZE] = { 0 };
  
  for(int i = 0; i < GRID_SIZE; i++) {
      int neighborCount = numberOfNeighbors(grid.grid, i);
    
      if (grid.grid[i] == 1) {  
        //rule 1 & 3
        if (neighborCount < 2 || neighborCount > 3) {
              temp[i] = 0;
          } else {
              //rule 2
              temp[i] = 1;
          }
      } else {
          //rule 4
          if (neighborCount == 3) {
              temp[i] = 1;
          }
      }
  }
  memcpy(grid.grid, &temp, grid.gridSize * sizeof(int));
}

int numberOfNeighbors(int* grid, int cell) {
  //the game of life is in a 2-D grid, but the data structure is linear
  //this means we need to do some manipulation to get the right values
  int count = 0;
  //the index into grid for the cell directly above
  int topIndex = cell - GRID_STRIDE;
  //the index for the cell below
  int bottomIndex = cell + GRID_STRIDE;
  //if the cell is on an edge, then we shouldn't look up neighbors in that direction
  //doing so with the same logic will get meaningless data.
  bool onLeftEdge = cell % GRID_STRIDE == 0;
  bool onRightEdge = cell % GRID_STRIDE == GRID_STRIDE - 1;
  bool onTopEdge = cell < GRID_STRIDE;
  bool onBottomEdge = cell + GRID_STRIDE >= GRID_STRIDE * GRID_STRIDE;
    
  if (!onTopEdge) {
      //top
      count += grid[topIndex];
      //top right
      if (!onRightEdge)
          count += grid[topIndex + 1];
      //top left
      if (!onLeftEdge)
          count += grid[topIndex - 1];
  }
  if (!onBottomEdge) {
      //bottom
      count += grid[bottomIndex];
      //bottom right
      if (!onRightEdge)
          count += grid[bottomIndex + 1];
      //bottom left
      if (!onLeftEdge)
          count += grid[bottomIndex - 1];
  }
  if (!onRightEdge)
      count += grid[cell + 1];
  if (!onLeftEdge)
      count += grid[cell - 1];
    
  return count;
}
