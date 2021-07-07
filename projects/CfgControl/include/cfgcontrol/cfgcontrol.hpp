#pragma once

#include "visibility.hpp"

/**
 * @brief Инициализация логгера
 * @param logPath Полный путь для сохранения файла лога
 * Пример C:\Logs\cfgcontrol.log
 * @return Статус выполнения операции
 */
CFGCONTROL_API bool CfgControl_initLogger(const char* logPath = "",
                                          int level = 1);

/**
 * @brief Деинициализация логера. Вызывать перед закрытием основной программы
 * @return Статус выполнения операции
 */
CFGCONTROL_API bool CfgControl_deinitLogger();

/**
 * @brief Прочитать конфигурационный файл на диске
 * @param configPath Путь до файла конфигурации
 * @param metaPath Путь до файла с мета-данными
 * @param type Config type (1 - Ini, 2 - Json)
 * @return
 */
CFGCONTROL_API const char* CfgControl_readConfigDisk(const char* configPath,
                                                     const char* metaPath = "",
                                                     unsigned int type = 1);

/**
 * @brief Записать данные в конфигурационный файл на диске
 * @param configPath Путь до файла конфигурации
 * @param config Строка с данными конфигурации
 * @param metaPath Путь до файла с мета-данными
 * @param meta Строка с мета-данными
 * @return Статус выполнения операции.
 * 1 - операция выполнена,
 * 0 - неизвестная ошибка,
 * -1 - ошибка записи на диск,
 * -2 - ошибка в принятых данных
 */
CFGCONTROL_API int CfgControl_writeConfigDisk(const char* configPath,
                                              const char* config,
                                              const char* metaPath = "",
                                              const char* meta = "");