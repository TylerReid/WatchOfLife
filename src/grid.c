#include <pebble.h>
#include "grid.h"

#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int numberOfNeighbors(int* grid, int cell);

void printGrid(Grid grid)
{
    for (int i = 0; i < GRID_SIZE ; i++)
    {
        printf("%d", grid.grid[i]);
        if ((i + 1) % GRID_STRIDE == 0)
        {
            printf("\n");
        }
    }
}

void getGridText(Grid grid, char* text) {
  int n = 0;
  for (int i = 0; i < grid.gridSize + grid.gridStride ; i++)
  {
      text[i] = grid.grid[n] + '0';
      if ((n + 1) % GRID_STRIDE == 0)
      {
        i++;
        text[i] = '\n';
      }
    n++;
  }
}

Grid createGrid()
{
  int grid[GRID_SIZE] = 
  {
      0,0,0,0,0,0,1,0,
      1,1,1,0,0,0,1,0,
      0,0,0,0,0,0,1,0,
      0,0,0,0,0,0,0,0,
      0,1,0,0,0,0,0,0,
      0,1,0,0,0,1,1,1,
      0,1,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,
  };
  //todo fix this crazy array copy thing once pointers are more understood
  int * gridP = (int *)malloc(GRID_SIZE * sizeof(int));
    
  for(int i = 0; i < GRID_SIZE; i++)
  {
      gridP[i] = grid[i];
  }
    
  Grid gridStruct;
  gridStruct.grid = gridP;
  gridStruct.gridStride = GRID_STRIDE;
  gridStruct.gridSize = GRID_SIZE;
  return gridStruct;
}

char* allocateText() {
  return (char*) malloc((GRID_SIZE + GRID_STRIDE) * sizeof(char));
}

void simulate(Grid grid)
{
    int temp[GRID_SIZE] = { 0 };
    
    for(int i = 0; i < GRID_SIZE; i++)
    {
        int neighborCount = numberOfNeighbors(grid.grid, i);
        if (grid.grid[i] == 1)
        {
            if (neighborCount < 2 || neighborCount > 3)
            {
                temp[i] = 0;
            }
            else
            {
                temp[i] = 1;
            }
        }
        else
        {
            if (neighborCount == 3)
            {
                temp[i] = 1;
            }
        }
    }
    
    for (int i = 0; i < GRID_SIZE; i++)
    {
        grid.grid[i] = temp[i];
    }
}

int numberOfNeighbors(int* grid, int cell)
{
    int count = 0;
    int topIndex = cell - GRID_STRIDE;
    int bottomIndex = cell + GRID_STRIDE;
    
    bool onLeftEdge = cell % GRID_STRIDE == 0;
    bool onRightEdge = cell % GRID_STRIDE == GRID_STRIDE - 1;
    bool onTopEdge = cell < GRID_STRIDE;
    bool onBottomEdge = cell + GRID_STRIDE >= GRID_STRIDE * GRID_STRIDE;
    
    if (!onTopEdge)
    {
        //top
        count += grid[topIndex];
        //top right
        if (!onRightEdge)
            count += grid[topIndex + 1];
        //top left
        if (!onLeftEdge)
            count += grid[topIndex - 1];
    }
    if (!onBottomEdge)
    {
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
