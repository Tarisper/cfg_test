#include "parser_manager.hpp"

#include <backends/ini_parser.hpp>
#include <backends/json_parser.hpp>
#include <filesystem>

namespace hdd {

ParserManager* ParserManager::create(ConfigType type) {
  if (type == ConfigType::Ini) {
    return new IniParser();
  }
  if (type == ConfigType::Json) {
    return new JsonParser();
  }
  return nullptr;
}

FileType ParserManager::getType(const std::string& path) {
  return (!std::filesystem::exists(path)) ? FileType::String : FileType::File;
}

ParserManager::ParserManager() {}

}  // namespace hdd