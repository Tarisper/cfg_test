/**
 * @file types.hpp.
 * @brief Intermodular types.
 * @author Khayitov D. D. (c).
 * @date 2021.
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace hdd {

/**
 * @brief Структура с данными параметра
 */
struct Param {
  /**
   * @brief Название параметра как в конфиге
   */
  std::string DefineAlias = "";
  /**
   * @brief Тип значения параметра (String, Int, Float, Bool, Parent)
   */
  std::string ParamType = "";
  /**
   * @brief Полное описание параметра
   */
  std::string DescriptionShort = "";
  /**
   * @brief Короткое описание параметра
   */
  std::string DescriptionFull = "";
  /**
   * @brief Полное имя параметра, являющегося родительским для данного
   */
  std::string ParentParam = "";
  /**
   * @brief Значение по-умолчанию для параметра
   */
  std::string DefaultValue = "";
  /**
   * @brief Минимальное допустимое значение параметра
   */
  std::string MinValue = "";
  /**
   * @brief Максимальное допустимое значение параметра
   */
  std::string MaxValue = "";
  /**
   * @brief Массив допустимых значений параметра (используется если не заданы
   * MinValue/MaxValue)
   */
  std::vector<std::string> AllowedValues;
  /**
   * @brief Является ли параметр доступным для редактирования только
   * разработчикам
   */
  bool IsForDevelopers;
  /**
   * @brief Порядковый номер параметра внутри своей секции, для визуализации
   */
  size_t Ord = 0;
  std::string Value;
};

enum class ConfigType { Unknown = 0, Ini, Json };

enum class FileType { Unknown = 0, File, String };

typedef struct {
  std::string configPath = "";
  std::string metaPath = "";
  bool isFile = false;
  std::vector<Param> params;
} MetaInfo;

static const std::vector<std::string> ParamType = {"String", "Int", "Float",
                                                   "Bool", "Parent"};

const size_t defaultType = 0;

}  // namespace hdd
