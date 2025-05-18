#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command
{
private:
    std::string command_name;

public:
    virtual void execute() = 0;
    virtual ~Command() = default;
    virtual std::string help() const = 0;
};

class ChangeDirectory:public Command
{
};

class CreateDirectory:public Command
{
};

class CreateFile:public Command
{
};




#endif  // !COMMAND_H
