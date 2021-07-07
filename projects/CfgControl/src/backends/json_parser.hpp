#pragma once
#include <cfgcontrol/types.hpp>
#include <string>
#include <vector>

#include "parser_manager.hpp"

namespace hdd {

class JsonParser final : public ParserManager {
 public:
  explicit JsonParser();
  ~JsonParser() override = default;

  /**
   * @brief Распарсить json-файл
   * @param configPath Ссылка до файла с конфигом или строка с содержимым
   * файла
   * @param metaPath Ссылка до файла с мета-данными или строка с содержимым
   * файла
   * @param json Указатель на структуру с данными файла с мета-данными
   * @param result Распарсенная строка, если нет ошибок
   * @param isFile = true, если metaPath это ссылка на файл. false, если
   * metaPath это строка с содержимым файла
   * @return Статус выполнения операции
   */
  bool parse(const std::string& configPath, const std::string& metaPath,
             MetaInfo& json, std::string& result, bool isFile = true) override;

 private:
  std::string m_loggerName = "";
};

}  // namespace hdd