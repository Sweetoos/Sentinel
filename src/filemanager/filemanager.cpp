#include "filemanager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "command.h"

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
    std::cout << file_path.c_str() << "> ";
    std::getline(std::cin, cmd);
    CommandParser::tokenize(cmd);
}
