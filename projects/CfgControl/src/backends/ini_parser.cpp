#include "ini_parser.hpp"

#include <backends/get_meta_info/get_meta_info.hpp>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>

#include "utilities/INIReader/INIReader.h"

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

static unique_ptr<INIReader> ini = nullptr;

namespace hdd {

IniParser::IniParser() {}

IniParser::~IniParser() {
  if (ini) ini.reset();
}

bool IniParser::checkConfigFile(const std::string& configPath, bool isFile) {
  if (configPath.empty()) return false;
  if (isFile) {
    if (!fs::exists(configPath))
      return false;
    else {
      INIReader reader(configPath);
      if (reader.ParseError() != 0) return false;
      return true;
    }
  } else {
    INIReader reader(configPath.c_str(), sizeof(configPath.c_str()));
    if (reader.ParseError() != 0) return false;
    return true;
  }
}

bool IniParser::findParam(string parent, string name, vector<Param>& params,
                          vector<Param>::iterator& it) {
  it = find_if(begin(params), end(params), [=](Param const& f) {
    return (f.ParentParam == parent && f.DefineAlias == name);
  });
  return (it == params.end()) ? false : true;
}

string IniParser::getKey(const string& section, const string& name) {
  string key = section + "=" + name;
  // Convert to lower case to make section/name lookups case-insensitive
  std::transform(key.begin(), key.end(), key.begin(), ::tolower);
  return ini->_values.find(key)->second;
}

void IniParser::getParams(Param& param, const string& parent,
                          const string& name, size_t ord) {
  param.DefineAlias = name;
  param.ParentParam = parent;
  param.ParamType = ParamType[defaultType];  // Default type
  param.Value = getKey(parent, name);
  param.Ord = ord;
}

void IniParser::clearParams(MetaInfo& param) {
  param.configPath = "";
  param.isFile = false;
  param.metaPath = "";
  param.params.clear();
}

string IniParser::getValue(const string& type, const string& parent,
                           const string& name, const string& defaultValue) {
  if (type == "String") return ini->Get(parent, name, defaultValue.c_str());
  if (type == "Int")
    to_string(ini->GetInteger(parent, name, atoi(defaultValue.c_str())));
  if (type == "Float")
    to_string(ini->GetReal(parent, name, atof(defaultValue.c_str())));
  if (type == "Bool")
    to_string(ini->GetBoolean(parent, name, (bool)(defaultValue.c_str())));
  // TODO Вывод ошибки "Неизвестный тип параметра"
  return "";
}

bool IniParser::parse(const std::string& configPath,
                      const std::string& metaPath, MetaInfo& info,
                      std::string& result, bool isFile) {
  if (!checkConfigFile(configPath)) return false;
  clearParams(info);
  if (!metaPath.empty()) {
    if (!getMetaInfo(metaPath, info, isFile)) return false;
    if (!info.params.size() == 0) return false;
  }
  if (isFile)
    ini = make_unique<INIReader>(configPath);
  else
    ini =
        make_unique<INIReader>(configPath.c_str(), sizeof(configPath.c_str()));
  for (auto v : info.params)
    v.Value =
        getValue(v.ParamType, v.ParentParam, v.DefineAlias, v.DefaultValue);
  size_t ord = 0;
  for (auto m : ini->_values) {
    vector<Param>::iterator it;
    if (findParam(m.first, m.second, info.params, it)) {
      if (it != info.params.end()) {
        it->Value = getKey(m.first, m.second);
      }
    } else {
      Param param = {};
      getParams(param, m.first, m.second, ord);
      info.params.push_back(param);
    }
    ord++;
  }
}

}  // namespace hdd
