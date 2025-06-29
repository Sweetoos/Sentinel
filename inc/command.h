#ifndef COMMAND_H
#define COMMAND_H

#include <set>
#include <string>
#include <vector>

#include "jsonreader.h"

class ICommand
{
public:
    virtual void execute(const ParsedCommand &command) = 0;
    virtual ~ICommand() = default;
    virtual std::string help() const = 0;
};

class ChangeDirectory : public ICommand
{
};

class CreateDirectory : public ICommand
{
private:
    Command cmd;
    const std::set<std::string> accepted_flags;
    const std::set<std::string> supported_options;

public:
    CreateDirectory(const Command &command) : cmd(command) {}
    void execute(const ParsedCommand &command) override;
    std::string help() const override;
    bool fileChecker(const std::vector<std::string> &command,
                     const int startingPoint);
};

class CreateFile : public ICommand
{
};

namespace CommandParser
{
std::vector<std::string> commandTokenizer(const std::string &input);
}  // namespace CommandParser
#endif  // !COMMAND_H
