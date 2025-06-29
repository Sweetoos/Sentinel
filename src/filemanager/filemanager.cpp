#include "filemanager.h"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace fs = std::filesystem;

Terminal::Terminal(const std::string &systemDirectory)
{
    file_path = fs::current_path();
    if (fs::is_empty(file_path))
    {
        fs::create_directory(systemDirectory);
    }
    file_path = fs::current_path() / systemDirectory;
}

void Terminal::run()
{
    std::string cmd;
    bool runnable = true;
    while (runnable)
    {
        std::cout << file_path.c_str() << "> ";
        std::getline(std::cin, cmd);
        if (cmd != "exit")
            runCommand(cmd);
        else
            runnable = false;
    }
}

void Terminal::runCommand(const std::string &input)
{
    tokens = CommandParser::commandTokenizer(input);
    redistrubuteTokens();
}

// each command has: command, flags, option, argument
// mkdir -p --mode=755 folder1 folder2
void Terminal::redistrubuteTokens()
{

    using json = nlohmann::json;
    std::ifstream file("res/commands.json");
    if(!file.is_open())
        throw "file commands.json can't be found";
    json data = json::parse(file);


    if (tokens.empty()) throw "command is empty";

    /*
     * commands: mkdir, cd etc
     */
    parsed_command.command = tokens[0];
    json command_def;
    for (const auto &cmd : data["commands"])
    {
        if (cmd["command_name"] == parsed_command.command)
        {
            command_def = cmd;
            break;
        }
    }

    if (command_def.empty())
    {
        std::cout << "command not found\n";
        return;
    }

    for (size_t i = 1; i < tokens.size(); i++)
    {
        const std::string &token = tokens[i];
        if (token.starts_with("-") && data.contains("command") &&
            command_def["command"].is_object())
        {
            if (token.contains("="))  // option with value e. g. --mode=755
            {
                size_t pos = token.find('=');
                std::string name = token.substr(0, pos);
                std::string value = token.substr(pos + 1);
                parsed_command.options[name] = value;
            }
            else
            {
                parsed_command.flags.push_back(token);
            }
        }
        else if (token.starts_with("-") && token.length() > 1)
        {
            for (size_t j = 1; j < token.length(); j++)
            {
                char flag = token[j];
                parsed_command.flags.push_back("-" + flag);
            }
        }
        else
        {
            parsed_command.args.push_back(token);
        }
    }
}
