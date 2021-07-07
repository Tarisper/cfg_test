#include "backends/backends.hpp"

#include <memory>
#include <utilities/utilities.hpp>

using namespace std;

namespace hdd {

Backends::Backends() {}

void* Backends::create(ConfigType type) {
  ParserManager* parser = ParserManager::create(type);
  if (!parser) return nullptr;
  mManager.emplace_back(parser);
  return static_cast<void*>(parser);
}

bool Backends::release(const void* manager) {
  if (!manager) return false;
  const auto& it = find(mManager.begin(), mManager.end(), manager);
  if (it != mManager.end()) {
    ParserManager* parser = static_cast<ParserManager*>(*it);
    delete parser;
    parser = nullptr;
    mManager.erase(it);
  }
  return true;
}

bool Backends::parse(void* manager, const std::string& metaPath,
                     const std::string& configPath, string& result,
                     bool isFile) {
  if (!manager) return false;
  ParserManager* parser = static_cast<ParserManager*>(manager);
  if (!parser) return false;
  MetaInfo info;
  return parser->parse(
      configPath, metaPath, info, result,
      (parser->getType(configPath) == FileType::File) ? true : false);
}

Backends::~Backends() {
  if (!mManager.empty()) {
    auto _v = mManager;
    for (auto v : _v) release(v);
  }
}

}  // namespace hdd