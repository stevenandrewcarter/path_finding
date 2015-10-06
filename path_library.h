#pragma once
#include <vector>

namespace PathLibrary {
  struct Node {
    int x, y;

    bool operator ==(const Node &b) const {
      return x == b.x && y == b.y;
    }
  };

  /**
   * Graph object describes a graph of nodes and edges. The Graph is a 2D grid.
   * Some important properties of the Graph
   *  1. The graph edges can only be defined horizontally or vertically (No edge can be diagonal)
   *  2. The origin position of the Graph is (0, 0) with the x and y values increasing into the positive plane.
   */
  class Graph {
  public:
    /**
     * Default constructor for a Graph. The Graph is defined by the width and height values provided
     * @param a_width Width of the graph (X Axis)
     * @param a_height Height of the graph (Y Axis)
     * @param a_data 2D Data set that contains the data of the graph
     */
    Graph(int a_width, int a_height, const unsigned char* a_data);
    ~Graph() {};

    int get_path(Node a_source, Node a_target);

  private:
    std::vector<Node> get_edges(int a_x, int a_y) const;

    int width_, height_;
    const unsigned char* nodes_;
  };
}

/**
 * Find the shortest path between the Start Position and the Target Position
 */
extern int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
  const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);
