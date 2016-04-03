#include <pebble.h>
#include <stdlib.h>
#include "grid.h"

int numberOfNeighbors(Grid grid, int cell);

Grid createGrid() {
  int gridStride = 12;
  int gridSize = gridStride * gridStride;
  
  //inital condition of game grid
  char grid[] = 
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
  char* gridP = (char *)malloc(gridSize * sizeof(char));
  memcpy(gridP, &grid, gridSize * sizeof(char));
  
  Grid gridStruct;
  gridStruct.grid = gridP;
  gridStruct.gridStride = gridStride;
  gridStruct.gridSize = gridSize;
  return gridStruct;
}


/*
  1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
  2. Any live cell with two or three live neighbours lives on to the next generation.
  3. Any live cell with more than three live neighbours dies, as if by over-population.
  4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void simulate(Grid* grid)
{
  char* temp = (char*)malloc(grid->gridSize * sizeof(char));
  
  for(int i = 0; i < grid->gridSize; i++) {
      int neighborCount = numberOfNeighbors(*grid, i);
    
      if (grid->grid[i] == 1) {  
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
          } else {
            temp[i] = 0;
          }
      }
  }
  free(grid->grid);
  grid->grid = temp;
}

int numberOfNeighbors(Grid grid, int cell) {
  //the game of life is in a 2-D grid, but the data structure is linear
  //this means we need to do some manipulation to get the right values
  int count = 0;
  //the index into grid for the cell directly above
  int topIndex = cell - grid.gridStride;
  //the index for the cell below
  int bottomIndex = cell + grid.gridStride;
  //if the cell is on an edge, then we shouldn't look up neighbors in that direction
  //doing so with the same logic will get meaningless data.
  bool onLeftEdge = cell % grid.gridStride == 0;
  bool onRightEdge = cell % grid.gridStride == grid.gridStride - 1;
  bool onTopEdge = cell < grid.gridStride;
  bool onBottomEdge = cell + grid.gridStride >= grid.gridStride * grid.gridStride;
    
  if (!onTopEdge) {
      //top
      count += grid.grid[topIndex];
      //top right
      if (!onRightEdge)
          count += grid.grid[topIndex + 1];
      //top left
      if (!onLeftEdge)
          count += grid.grid[topIndex - 1];
  }
  if (!onBottomEdge) {
      //bottom
      count += grid.grid[bottomIndex];
      //bottom right
      if (!onRightEdge)
          count += grid.grid[bottomIndex + 1];
      //bottom left
      if (!onLeftEdge)
          count += grid.grid[bottomIndex - 1];
  }
  if (!onRightEdge)
      count += grid.grid[cell + 1];
  if (!onLeftEdge)
      count += grid.grid[cell - 1];
    
  return count;
}
