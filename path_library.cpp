#include "path_library.h"
#include <assert.h>

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
  // Perform upfront sanity checks  
  assert(nStartX >= 0 && nStartX <= nMapWidth);
  assert(nStartY >= 0 && nStartY <= nMapHeight);
  assert(nTargetX >= 0 && nTargetX <= nMapWidth);
  assert(nTargetY >= 0 && nTargetY <= nMapHeight);
  assert(nOutBufferSize > 0);
  // Construct the grid as a graph
  return 0;
}

Graph::Graph(int a_width, int a_height, const unsigned char* a_data)
{
  // Perform sanity checks
  assert(a_data != nullptr);
  assert(a_width >= 1);
  assert(a_height >= 1);
  width_ = a_width;
  height_ = a_height;
  // Build the Graph from the data
}