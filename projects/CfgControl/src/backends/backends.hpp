#pragma once

#include <backends/parser_manager.hpp>
#include <vector>

namespace hdd {

class Backends {
 public:
  Backends();
  ~Backends();
  void* create(ConfigType type);
  bool release(const void* manager);
  bool parse(void* manager, const std::string& metaPath,
             const std::string& configPath, std::string& result,
             bool isFile = true);

 private:
  std::vector<ParserManager*> mManager;
};

}  // namespace hdd
