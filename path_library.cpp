#include "path_library.h"
#include <assert.h>
#include <memory>

namespace PathLibrary {
  Graph::Graph(int a_width, int a_height, const unsigned char* a_data) {
    assert(a_data != nullptr);
    assert(a_width >= 1);
    assert(a_height >= 1);
    width_ = a_width;
    height_ = a_height;
    nodes_ = a_data;
  }

  int Graph::get_path(Node a_source, Node a_target) {
    // Check simple case first
    if (a_source == a_target)
      return 0;
    // Perform the search instead then
    return 0;
  }

  std::vector<Node> Graph::get_edges(int a_x, int a_y) const {
    assert(a_x >= 0 && a_x < width_);
    assert(a_y >= 0 && a_y < height_);
    std::vector<Node> edges;
    auto current_node = nodes_[a_x * a_y];
    if (current_node != '0') {
      // Passible location, check the cardinal neighbours
      if (a_x > 0 && nodes_[a_x - 1 * a_y] != '0') edges.push_back({ a_x - 1, a_y });
      if (a_x < width_ && nodes_[a_x + 1 * a_y] != '0') edges.push_back({ a_x + 1, a_y });
      if (a_y > 0 && nodes_[a_x * a_y - 1] != '0') edges.push_back({ a_x, a_y - 1 });
      if (a_y < height_ && nodes_[a_x * a_y + 1] != '0') edges.push_back({ a_x, a_y + 1 });
    }
    return edges;
  }
}

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {
  // Perform upfront sanity checks  
  assert(nStartX >= 0 && nStartX <= nMapWidth);
  assert(nStartY >= 0 && nStartY <= nMapHeight);
  assert(nTargetX >= 0 && nTargetX <= nMapWidth);
  assert(nTargetY >= 0 && nTargetY <= nMapHeight);
  assert(nOutBufferSize > 0);
  // Construct the grid as a graph
  auto graph = std::make_unique<PathLibrary::Graph>(nMapWidth, nMapHeight, pMap);
  return graph->get_path({ nStartX, nStartY }, { nTargetX, nTargetY });
}