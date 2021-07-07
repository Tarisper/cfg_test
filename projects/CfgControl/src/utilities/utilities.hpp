/**
 * @file utilities.hpp
 * @author Daniyar Hayitov
 * @brief Utilities
 * @version 0.2
 * @date 2021-06-22
 *
 * @copyright Copyright (c) 2021
 */
#pragma once

#ifndef WITH_DATE_TZ
#include <date/tz.h>
#endif
#ifndef WITH_FMT
#include <fmt/chrono.h>
#endif
#ifndef WITH_UUID
#include <uuid.h>
#endif

#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;
#ifndef WITH_FMT
using namespace std::chrono;
using namespace std::chrono_literals;
#endif

namespace hdd {

template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

/**
 * @brief Parse string by delimiter and convert to vector<string>
 *
 * @param str String
 * @param delim Delimeter (the default is ";")
 * @return vector<string>
 */
vector<string> StrToVectorStr(const string& str, string delim = ";") {
  vector<string> result;
  if (!str.empty()) {
    if (delim.empty()) delim = ";";
    size_t prev = 0;
    size_t next;
    size_t delta = delim.length();

    while ((next = str.find(delim, prev)) != string::npos) {
      string tmp = str.substr(prev, next - prev);
      result.push_back(tmp);
      prev = next + delta;
    }
    string tmp = str.substr(prev);
    result.push_back(tmp);
  }
  return result;
}

#ifndef WITH_DATE_TZ
/**
 * @brief Get time and date in specified format
 *
 * @param mask Date and time mask format (the default is "%d.%m.%Y %H/%M/%S", d
 * - day (dd), m - month (mm), Y - year (YYYY), H - hour, M - minuts, S -
 * seconds with milliseconds).
 *
 * @return String. Example: 18.05.2021 12/36/12.088.
 */
string getTimeStr(string mask = "%d.%m.%Y %H/%M/%S") {
  try {
    return (date::format(mask, date::make_zoned(date::current_zone(),
                                                time_point_cast<milliseconds>(
                                                    system_clock::now()))));
  } catch (...) {
  }
  return string();
}
#endif

int64_t StrToBigInt(const string& str) {
  return (str.empty()) ? 0 : atoll(str.c_str());
}

int StrToInt(const string& str) {
  return (str.empty()) ? 0 : atoi(str.c_str());
}

#ifndef WITH_UUID
string getGeneratedGuid() {
  uuids::uuid const id = uuids::uuid_system_generator{}();
  assert(!id.is_nil());
  assert(id.version() == uuids::uuid_version::random_number_based);
  assert(id.variant() == uuids::uuid_variant::rfc);
  return uuids::to_string(id);
}
#endif

}  // namespace hdd