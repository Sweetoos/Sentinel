#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <set>
#include <string>
#include <vector>

struct ParsedCommand
{
    std::string command;
    std::set<std::string> flags;
    std::map<std::string, std::string> options;
    std::vector<std::string> args;
};

class Command
{
public:
    virtual void execute(const ParsedCommand &command) = 0;
    virtual ~Command() = default;
    virtual std::string help() const = 0;
};

class ChangeDirectory : public Command
{
};

class CreateDirectory : public Command
{
private:
    std::string command;

public:
    void execute(const ParsedCommand &command) override;
    std::string help() const override;
    bool fileChecker(const std::vector<std::string> &command,
                     const int startingPoint);
};

class CreateFile : public Command
{
};

namespace CommandParser
{

std::vector<std::string> commandTokenizer(const std::string &input);
}  // namespace CommandParser
#endif  // !COMMAND_H
