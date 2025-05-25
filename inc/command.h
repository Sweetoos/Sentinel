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
    std::string command;
    const std::set<std::string> accepted_flags;
    const std::set<std::string> supportedOptions;

public:
    //CreateDirectory();
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
