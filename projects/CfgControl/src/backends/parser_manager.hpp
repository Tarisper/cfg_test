#pragma once
#include <cfgcontrol/types.hpp>
#include <string>

namespace hdd {

class ParserManager {
 public:
  virtual ~ParserManager() = default;
  static ParserManager* create(ConfigType type);
  /**
   * @brief Распарсить ini-файл
   * @param configPath Ссылка до файла с конфигом или строка с содержимым
   * файла
   * @param metaPath Ссылка до файла с мета-данными или строка с содержимым
   * файла
   * @param info Указатель на структуру с данными файла с мета-данными
   * @param result Распарсенная строка, если нет ошибок
   * @param isFile = true, если metaPath это ссылка на файл. false, если
   * metaPath это строка с содержимым файла
   * @return Статус выполнения операции (true/false)
   */
  virtual bool parse(const std::string& configPath, const std::string& metaPath,
                     MetaInfo& info, std::string& result,
                     bool isFile = true) = 0;

  FileType getType(const std::string& path);

 protected:
  explicit ParserManager();
};

}  // namespace hdd