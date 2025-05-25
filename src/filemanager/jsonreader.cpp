#include "jsonreader.h"
#include "command.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
std::unordered_map<std::string, Command> JsonReader::command_registry;

JsonReader::json readJsonFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("[ERROR]: Couldn't open JSON file: " + path);
    json jsonData;
    file >> jsonData;

    for (const auto &cmdJson : jsonData["commands"])
    {
        Command cmd;

        cmd.name = cmdJson["command_name"];
        cmd.description = cmdJson["description"];
        cmd.help_long = cmdJson.value("help_long", "");

        if (cmdJson.contains("aliases"))
        {
            for (const auto &alias : cmd.aliases) cmd.aliases.push_back(alias);
        }

        JsonReader::command_registry[cmd.name] = cmd;
        for (const auto &alias : cmd.aliases)
            JsonReader::command_registry[alias] = cmd;
    }
    return jsonData;
}


