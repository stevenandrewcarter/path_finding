#include "path_library.h"
#include <string>
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
  int width, height, max_path_size, source_x, source_y, target_x, target_y;
  cout << "Path Finding Library" << endl;
  cout << "====================" << endl << endl;
  cout << "Graph Width: ";
  cin >> width;
  cout << "Graph Height: ";
  cin >> height;
  cout << "A " << width << " by " << height << " graph is requested." << endl;
  cout << "Please enter the first row of the graph in the format <01010>. 0 indicates an impassible location, 1 indicates a passable location" << endl;
  auto input_buffer = string{ "" };
  for (auto i = 0; i < height; ++i) {
    cout << "Row " << i + 1 << ": ";
    auto row = string{ "" };
    cin >> row;
    input_buffer += row;    
  }
  cout << "Maximum Path size: ";
  cin >> max_path_size;  
  cout << "Source X: ";
  cin >> source_x;
  cout << "Source Y: ";
  cin >> source_y;
  cout << "Target X: ";
  cin >> target_x;
  cout << "Target Y: ";
  cin >> target_y;
  // This causes a implied maximum of a graph size of 1024 (Bigger graphs are going to break)
  unsigned char pMap[1024]; 
  for (auto i = 0; i < input_buffer.size(); ++i) {
    pMap[i] = input_buffer[i];
  }
  pMap[input_buffer.size()] = '\0';
  // Also forces the max buffer to a arbitrary size :/
  int pOutBuffer[1024];
  auto path_size =  FindPath(source_x, source_y, target_x, target_y, pMap, width, height, pOutBuffer, max_path_size);
  for (auto i = 0; i < path_size; ++i) {
    cout << pOutBuffer[i] << " ";
  }
  cout << endl;
  cin.get();
}
