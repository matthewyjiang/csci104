#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char** argv) {
  int num_iterations = 1;

  if (argc == 2) {
    num_iterations = std::stoi(argv[1]);
  }

  for (int i = 0; i < num_iterations; ++i) {
    std::cout << "Hello, world! (" << i << ")" << std::endl;
  }
}