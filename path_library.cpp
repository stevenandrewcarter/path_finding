#include "path_library.h"
#include <assert.h>
#include <functional>
#include <memory>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

namespace std {
  /**
   * Defines a hash function for storing the Nodes in the unordered maps
   * C2906
   */
  template <>
  struct hash<PathLibrary::Node> {
    size_t operator()(const PathLibrary::Node& location) const {
      return location.x * 1812433253 + location.y;
    }
  };
}

namespace PathLibrary {
  /**
   * Priority Queue wrapper around the std::priority_queue class, reverses the order from std::lesser to std::greater
   */
  template<typename T>
  struct PriorityQueue {
    bool empty() {
      return elements.empty();
    }

    void put(int priority, T item) {
      elements.emplace(priority, item);
    }

    T get() {
      T best_item = elements.top().second;
      elements.pop();
      return best_item;
    }

  private:
    typedef pair<int, T> PriorityQueueElement;
    priority_queue<PriorityQueueElement, vector<PriorityQueueElement>, greater<PriorityQueueElement>> elements;
  };

  Graph::Graph(int a_width, int a_height, const unsigned char* a_data) {
    assert(a_data != nullptr);
    assert(a_width >= 1);
    assert(a_height >= 1);
    width_ = a_width;
    height_ = a_height;
    nodes_ = a_data;
  }

  void Graph::draw() {
    for (auto y = 0; y < height_; ++y) {
      for (auto x = 0; x < width_; ++x) {
        cout << (get_node(x, y).value == 1 ? "." : "#");
      }
      cout << endl;
    }
  }

  int Graph::get_path(Node a_source, Node a_target, int* pOutBuffer, const int nOutBufferSize) {
    // Queue of possible search locations    
    PriorityQueue<Node> queue;
    // Start with the current source location
    queue.put(0, a_source);
    // Map indicates the best path from a given node to another node
    unordered_map<Node, Node> came_from;
    // Keep a tally of the cost for each node in the search
    unordered_map<Node, int> cost_so_far;
    auto found = false;

    while (!queue.empty()) {
      auto current = queue.get();
      cout << "Checking Current " << current.x << " " << current.y << endl;
      if (current == a_target) {
        found = true;
        break;
      }

      for (auto next : get_neighbours(current)) {
        cout << "+- Checking neighbour " << next.x << " " << next.y << endl;
        auto new_cost = cost_so_far[current] + cost(current, next);
        // Check if this node has been seen before or if the new cost is better than the existing one
        // NB: For the current implementation of the search and layout of the grid, this only really prevents the search from searching nodes again.
        if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
          cost_so_far[next] = new_cost;
          auto priority = new_cost + int(calculate_heuristic(next, a_target));
          cout << " +- New Cost " << new_cost << " : Priority " << priority << endl;
          queue.put(priority, next);
          came_from[next] = current;
        }
      }
    }
    if (found) {
      // Populate the path (The path is found by starting at the target and stepping back through the come_from set
      // till it is at the source location.
      vector<Node> solution_path;
      auto current = a_target;
      solution_path.push_back(current);
      while (current != a_source) {
        current = came_from[current];
        if (current != a_source) solution_path.push_back(current);
      }
      reverse(solution_path.begin(), solution_path.end());
      // Just in case the buffer cannot actually hold the path positions
      if (nOutBufferSize >= solution_path.size()) {
        for (auto path_position = 0; path_position < solution_path.size(); ++path_position) {
          pOutBuffer[path_position] = get_map_position(solution_path[path_position]);
        }
      }
      return int(solution_path.size());
    }
    // No Path was found
    return -1;
  }

  vector<Node> Graph::get_neighbours(Node a_node) const {
    assert(a_node.x >= 0 && a_node.x < width_);
    assert(a_node.y >= 0 && a_node.y < height_);
    vector<Node> neighbours;
    if (a_node.value != '0') {
      // Passible location, check the cardinal neighbours
      if (a_node.x - 1 > 0 && get_node(a_node.x - 1, a_node.y).value != 0) 
        neighbours.push_back(get_node(a_node.x - 1, a_node.y));
      if (a_node.x + 1 < width_ && get_node(a_node.x + 1, a_node.y).value != 0) 
        neighbours.push_back(get_node(a_node.x + 1, a_node.y));
      if (a_node.y - 1 > 0 && get_node(a_node.x, a_node.y - 1).value != 0) 
        neighbours.push_back(get_node(a_node.x, a_node.y - 1));
      if (a_node.y + 1 < height_ && get_node(a_node.x, a_node.y + 1).value != 0) 
        neighbours.push_back(get_node(a_node.x, a_node.y + 1));
    }
    return neighbours;
  }

  Node Graph::get_node(int x, int y) const {
    return Node{ x, y, int(nodes_[width_ * y + x]) };
  }

  int Graph::get_map_position(Node node) const {
    return width_ * node.y + node.x;
  }

  int Graph::calculate_heuristic(Node a_source, Node a_target) {
    return abs(a_target.x - a_source.x) - abs(a_target.y - a_source.y);
  }

  int Graph::cost(Node /*a_source*/, Node /*a_target*/) {
    // Cost is uniform in the current search, but if different costs are required here is where to implement that calculation
    return 1;
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
  auto graph = make_unique<PathLibrary::Graph>(nMapWidth, nMapHeight, pMap);
  graph->draw();
  PathLibrary::Node source{ nStartX, nStartY, 1 };
  PathLibrary::Node target{ nTargetX, nTargetY, 1 };
  return graph->get_path(source, target, pOutBuffer, nOutBufferSize);        
}