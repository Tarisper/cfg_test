#include "get_meta_info.hpp"

#include <backends/parser_manager.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

namespace hdd {

bool checkParamType(string name) {
  auto it = find_if(begin(ParamType), end(ParamType),
                    [=](string const& f) { return (f == name); });
  return (it == ParamType.end()) ? false : true;
}

bool getInfo(json& j, MetaInfo& info) {
  if (!j) return false;
  for (size_t i = 0; i < j["params"].size(); i++) {
    if (j["params"][i]["DefineAlias"].get<string>() == "") return false;
    Param mi = {};
    for (size_t ii = 0; ii < j["params"][i]["AllowedValues"].size(); ii++)
      mi.AllowedValues.push_back(
          j["params"][i]["AllowedValues"][ii].get<string>());
    mi.DefaultValue = j["params"][i]["DefaultValue"].get<string>();
    mi.DefineAlias = j["params"][i]["DefineAlias"].get<string>();
    mi.DescriptionFull = j["params"][i]["DescriptionFull"].get<string>();
    mi.DescriptionShort = j["params"][i]["DescriptionShort"].get<string>();
    mi.IsForDevelopers = j["params"][i]["IsForDevelopers"].get<bool>();
    mi.MaxValue = j["params"][i]["MaxValue"].get<string>();
    mi.MinValue = j["params"][i]["MinValue"].get<string>();
    mi.Ord = j["params"][i]["Ord"].get<int>();
    string type = j["params"][i]["ParamType"].get<string>();
    if (!checkParamType(type))
      return false;
    else
      mi.ParamType = type;
    mi.ParentParam = j["params"][i]["ParentParam"].get<string>();
    info.params.push_back(mi);
  }
  return true;
}

bool getMetaInfo(const string& metaPath, MetaInfo& info, bool isFile) {
  if (isFile) {
    if (!fs::exists(metaPath))
      return false;
    else {
      try {
        std::ifstream in(metaPath);
        std::string source, content;
        if (in.is_open()) {
          while (getline(in, source)) {
            content = content + source;
          }
        }
        in.close();
        json j = json::parse(content);
        return getInfo(j, info);
      } catch (const json::exception& e) {
        return false;
      }
    }
  } else {
    try {
      json j = json::parse(metaPath);
      return getInfo(j, info);
    } catch (const json::exception& e) {
      return false;
    }
    return true;
  }
}

}  // namespace hdd