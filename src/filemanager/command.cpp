#include "command.h"

#include <sstream>

namespace CommandParser
{
std::vector<std::string> tokenize(const std::string &input)
{
    std::vector<std::string> tokens;
    std::istringstream ss(input);
    char delimiter = ' ';
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
}  // namespace CommandParser


