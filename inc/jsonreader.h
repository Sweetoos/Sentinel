#ifndef JSON_READER
#define JSON_READER

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

struct ParsedCommand
{
    std::string command;
    std::vector<std::string> flags;
    std::unordered_map<std::string, std::string> options;
    std::vector<std::string> args;
};

struct Flag {
    std::string short_form;
    std::string long_form;
    std::string description;
};

struct Option {
    std::string short_form;
    std::string long_form;
    std::string description;
    std::string arg_name;
    bool required;
};

struct Argument {
    std::string name;
    std::string description;
    bool required;
    bool variadic;
};

struct Command {
    std::string name;
    std::vector<std::string> aliases;
    std::string description;
    std::string help_long;
    std::vector<Flag> flags;
    std::vector<Option> options;
    std::vector<Argument> args;
    std::string handler;
};

namespace JsonReader
{
using json = nlohmann::json;
extern std::unordered_map<std::string, Command> command_registry;
json readJsonFile(const std::string &path);
}  // namespace JsonReader

#endif  // !JSON_READER
