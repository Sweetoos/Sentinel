#ifndef JSON_READER
#define JSON_READER

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include "command.h"

namespace JsonReader
{
using json = nlohmann::json;
extern std::unordered_map<std::string, Command> command_registry;
json readJsonFile(const std::string &path);
}  // namespace JsonReader

#endif  // !JSON_READER
