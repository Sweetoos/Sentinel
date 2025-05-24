#include "command.h"

#include <cctype>
#include <filesystem>
#include <iostream>

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
void CreateDirectory::execute(const ParsedCommand &command) {}

std::string CreateDirectory::help() const
{
    namespace cp = CommandParser;
    namespace fs = std::filesystem;
    if (cp::commandTokenizer(command)[1][0] == '-' ||
        (cp::commandTokenizer(command)[1][0] == '-' &&
         cp::commandTokenizer(command)[1][1] == '-'))
    {
        //handle all files from 2 to the rest
    }
    
}

bool CreateDirectory::fileChecker(const std::vector<std::string> &command,
                                  const int startingPoint)
{
    // check if file exists in command, if exists then dont create this file
}

//
