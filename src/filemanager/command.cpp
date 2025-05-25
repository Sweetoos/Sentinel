#include "command.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace CommandParser
{
std::vector<std::string> commandTokenizer(const std::string &input)
{
    std::vector<std::string> tokens;
    std::string current;
    bool escaping = false;
    for (char c : input)
    {
        if (escaping)
        {
            current += c;
            escaping = false;
        }
        else if (c == '\\')
        {
            escaping = true;
        }
        else if (std::isspace(c))
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current.clear();
            }
        }
        else
        {
            current += c;
        }
    }

    if (!current.empty())
    {
        tokens.push_back(current);
    }
    return tokens;
}
}  // namespace CommandParser
//

/*
CreateDirectory::CreateDirectory()
{
    using json = nlohmann::json;
    const std::string jsonFileDirectory = "res/";
    const std::string jsonFileName = "commands.json";
    const std::string fileName = jsonFileDirectory + jsonFileName;
    std::ifstream ifs(fileName);
    json file;
    if (ifs.is_open())
    {
        std::cerr << "[ERROR]: Couldn't open " << jsonFileName << " file \n";
        return;
    }
    try
    {
        ifs >> file;
        ifs.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[ERROR]: JSON parse error in " << jsonFileName << '\n';
        if (ifs.is_open()) ifs.close();
    }
}
*/
using json = nlohmann::json;
static Flag fromJson(const json &j)
{
    return Flag{
        j.value("short", ""),
        j.value("long", ""),
        j.value("description", ""),
    };
}

void CreateDirectory::execute(const ParsedCommand &command) {}

std::string CreateDirectory::help() const
{
    namespace cp = CommandParser;
    namespace fs = std::filesystem;
    if (cp::commandTokenizer(command)[1][0] == '-' ||
        (cp::commandTokenizer(command)[1][0] == '-' &&
         cp::commandTokenizer(command)[1][1] == '-'))
    {
        
        // handle all files from 2 to the rest
    }
}

bool CreateDirectory::fileChecker(const std::vector<std::string> &command,
                                  const int startingPoint)
{
    // check if file exists in command, if exists then dont create this file
}

//
