#include "path_library.h"
#include <iostream>

int main(int argc, char* argv[]) {
  unsigned char pMap[] = { 
    1, 1, 1, 1, 
    0, 1, 0, 1, 
    0, 1, 1, 1 };  
  // unsigned char pMap[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
  int pOutBuffer[7];
  auto path_size =  FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12); // FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
  for (auto i = 0; i < path_size; ++i) {
    std::cout << pOutBuffer[i] << " ";
  }
  std::cout << std::endl;  
  std::cin.get();
}
