#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command
{
private:
    std::string command_name;

public:
    virtual void execute() = 0;
    virtual ~Command() = default;
    virtual std::string help() const = 0;
};

class ChangeDirectory : public Command
{
};

class CreateDirectory : public Command
{
};

class CreateFile : public Command
{
};

namespace CommandParser
{
std::vector<std::string> tokenize(const std::string &input);
}
#endif  // !COMMAND_H
