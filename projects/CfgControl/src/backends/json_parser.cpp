#include "json_parser.hpp"

#include <filesystem>
#include <fstream>
#include <streambuf>

using namespace std;
namespace fs = std::filesystem;

namespace hdd {

JsonParser::JsonParser() {}

bool JsonParser::parse(const std::string& configPath,
                       const std::string& metaPath, MetaInfo& json,
                       std::string& result, bool isFile) {
  return true;
}

}  // namespace hdd