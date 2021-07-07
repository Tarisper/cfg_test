#pragma once

#include <cfgcontrol/types.hpp>
#include <string>

namespace hdd {

bool getMetaInfo(const std::string& metaPath, MetaInfo& info,
                 bool isFile = true);

}  // namespace hdd