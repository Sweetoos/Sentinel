#include "filemanager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

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
    parsed_command = redistrubuteTokens();
}

// each command has: command, flags, option, argument
ParsedCommand Terminal::redistrubuteTokens()
{
    parsed_command.command = tokens[0];

    for (size_t i = 1; i < tokens.size(); i++)
    {
        const std::string &token = tokens[i];
        if (token.starts_with("--"))
        {
            if (token.contains("="))
            {
            }
            else
            {
                parsed_command.flags.push_back(token);
            }
        }
    }
}
