#pragma once
#include <vector>

namespace PathLibrary {
  struct Node {
    int x, y;
    char value;

    Node() = default;

    Node(int a_x, int a_y, char a_value) {
      x = a_x;
      y = a_y;
      value = a_value;
    }

    Node(const Node &obj) {
      x = obj.x;
      y = obj.y;
      value = obj.value;
    }

    bool operator ==(const Node &b) const {
      return x == b.x && y == b.y;
    }

    bool operator !=(const Node &b) const {
      return x != b.x || y != b.y;
    }

    bool operator <(const Node &b) const {
      return b.x < x && b.y < y;
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

    /**
     * Draw the graph as ascii characters
     */
    void draw();
    
    /**
     * Calculates the shortest path between source and target destinations using A* search
     * @param a_source Source Node to start search from
     * @param a_target Target Node to find path to
     * @param oOutBuffer Will contain the path steps from the source to the target (Related to the original map)
     * @param nOutBufferSize Size of the OutBuffer
     * @return The size of the path if found, else -1 if no path is available
     */
    int get_path(Node a_source, Node a_target, int* pOutBuffer, const int nOutBufferSize);    

  private:
    /**
     * Get the neighbours of the given nodes (Only considers the cardinal neighbours)     
     *  .N.  Basically it will only get the neighbour above, below and to the left and
     *  W*E  right. 
     *  .S.
     * If a neighbour is not available it will not be included as a neighbour.
     */
    std::vector<Node> get_neighbours(Node a_node) const;

    /**
     * Retrieve the node from the map for the given coordinates
     */
    Node get_node(int x, int y) const;

    /**
     * Retrieve the map position for the given node
     */
    int get_map_position(Node node) const;

    /**
     * Heuristic will be calculated as the unsquared distance between the given nodes
     */
    int calculate_heuristic(Node a_source, Node a_target);

    /**
    * Calculate the cost between the current node and the target node
    */
    int cost(Node a_source, Node a_target);

    int width_, height_;
    const unsigned char* nodes_;
  };
}

/**
 * Find the shortest path between the Start Position and the Target Position
 */
extern int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
  const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);
