# Библиотека для парсинга конфигурационных файлов
## Сборка 
1. При необходимости активируйте среду Python, содержащую исполняемый файл Conan.
2. Запустить скрипт build_ninja.sh для Linux или build_v142_x64.cmd для Windows для создания и компиляции проекта Visual Studio 2019.

## Требования
* [CMake](https://cmake.org/download/) >= 3.18
* [Conan](https://conan.io/downloads.html)
* VS 2019 (Community, Workload NativeDesktop, vcredist140, WinDbg)

_Опционально:_
* [Ninja](https://github.com/ninja-build/ninja/releases)
* [vswhere](https://github.com/microsoft/vswhere/releases)

## Зависимости
Проект содержит следующие типы зависимостей, которые могут обновляются:
- Зависимости Conan.
- Зависимости CMake FetchContent.

## Состав
Проект содержит следующие модули в виде монорепозитория:

### Проекты
- **CfgControl** - библиотека парсинга.
- **CfgTest** - исполняемый файл примера.

### Среда решения
- **cmake** - модули и помощники CMake.
- **scripts** - скрипты сборки и утилиты.

## Описание структуры meta-файла
### Пример:
```json
{
  "params": [
    {
      "DefineAlias": "Capture",
      "ParamType": "Parent",
      "DescriptionShort": "Секция Capture",
      "DescriptionFull": "Секция с параметрами захвата изображения",
      "ParentParam": "",
      "DefaultValue": "",
      "MinValue": "",
      "MaxValue": "",
      "AllowedValues": [],
      "IsForDevelopers": false,
      "Ord": 1
    },
    {
      "DefineAlias": "delay_ms",
      "ParamType": "Integer",
      "DescriptionShort": "Задержка, мс",
      "DescriptionFull": "Задержка между фазой 1 и фазой 2 в миллисекундах",
      "ParentParam": "Capture",
      "DefaultValue": "100",
      "MinValue": "0",
      "MaxValue": null,
      "AllowedValues": [],
      "IsForDevelopers": false,
      "Ord": 1
    }
  ]
}
```

Пояснения:
* "DefineAlias" - название параметра как в конфиге;
* "ParamType" - тип значения параметра (см. ниже варианты);
* "DescriptionShort" - краткое описание параметра;
* "DescriptionFull" - полное описание параметра;
* "ParentParam" - полное имя параметра, являющегося родительским для данного.;
* "DefaultValue" - значение по-умолчанию для параметра;
* "MinValue" - минимальное допустимое значение параметра;
* "MaxValue" - максимальное допустимое значение параметра;
* "AllowedValues" - массив допустимых значений параметра (используется если не заданы MinValue/MaxValue);
* "IsForDevelopers" - является ли параметр доступным для редактирования только разработчикам;
* "Ord" - порядковый номер параметра внутри своей секции, для визуализации.

### Варианты значений ParamType:

| ParamType | Description |
| --------- | :-------: |
| String |  Строка |
| Int |  Целое |
| Float | Дробное |
| Bool | Булево |
| Parent | Родительский |

## Структура сформированного JSON-файла или строки с данными файла конфигурации
Результатом работы библиотеки является сформированный итоговый файл или строка с данными конфигурации в формате JSON.
Формат JSON-файла или строки совпадает со структурой meta-файла за исключением того, что в каждую секцию, описывающую параметр, добавляется параметр Value типа String.

Пример:
```json
{
  "params": [
    {
      "DefineAlias": "Capture",
      "ParamType": "Parent",
      "DescriptionShort": "Секция Capture",
      "DescriptionFull": "Секция с параметрами захвата изображения",
      "ParentParam": "",
      "DefaultValue": "",
      "MinValue": "",
      "MaxValue": "",
      "AllowedValues": [],
      "IsForDevelopers": false,
      "Ord": 1,
      "Value": ""
    },
    {
      "DefineAlias": "delay_ms",
      "ParamType": "Integer",
      "DescriptionShort": "Задержка, мс",
      "DescriptionFull": "Задержка между фазой 1 и фазой 2 в миллисекундах",
      "ParentParam": "Capture",
      "DefaultValue": "100",
      "MinValue": "0",
      "MaxValue": null,
      "AllowedValues": [],
      "IsForDevelopers": false,
      "Ord": 1,
      "Value": "15"
    }
  ]
}
```