#pragma once
#include <cfgcontrol/types.hpp>
#include <string>
#include <vector>

#include "parser_manager.hpp"

namespace hdd {

class IniParser final : public ParserManager {
 public:
  explicit IniParser();
  ~IniParser() override;
  bool parse(const std::string& configPath, const std::string& metaPath,
             MetaInfo& info, std::string& result, bool isFile = true) override;

 private:
  bool checkConfigFile(const std::string& configPath, bool isFile = true);
  bool findParam(std::string parent, std::string name,
                 std::vector<Param>& params, std::vector<Param>::iterator& it);
  std::string getKey(const std::string& section,
                                const std::string& name);
  void getParams(Param& param, const std::string& parent,
                 const std::string& name, size_t ord);
  void clearParams(MetaInfo& param);
  std::string getValue(const std::string& type, const std::string& parent,
                       const std::string& name,
                       const std::string& defaultValue);
  MetaInfo info;
};

}  // namespace hdd
