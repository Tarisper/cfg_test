#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  if (argc == 1) {
    cerr << "The path to the directory with files is not specified" << endl;
    return 0;
  }
  return 0;
}