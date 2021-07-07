#include <ini.h>

#include <backends/backends.hpp>
#include <cfgcontrol/cfgcontrol.hpp>
#include <memory>

using namespace std;
using namespace hdd;

static unique_ptr<Backends> gBackends = nullptr;
void* mBackends = nullptr;

bool CfgControl_initLogger(const char* logPath, int level) { return true; }

bool CfgControl_deinitLogger() {
  if (gBackends) {
    gBackends->release(mBackends);
    gBackends.reset();
  }
  return true;
}

ConfigType getType(unsigned int type) {
  switch (type) {
    case 1:
      return ConfigType::Ini;
      break;
    case 2:
      return ConfigType::Json;
    default:
      return ConfigType::Unknown;
      break;
  }
}

const char* CfgControl_readConfigDisk(const char* configPath,
                                      const char* metaPath, unsigned int type) {
  string result = "";
  gBackends = make_unique<Backends>();
  mBackends = gBackends->create(getType(type));
  gBackends->parse(mBackends, metaPath, configPath, result, type);
  return result.c_str();
}

int CfgControl_writeConfigDisk(const char* configPath, const char* config,
                               const char* metaPath, const char* meta) {
  int result = 0;
  return result;
}