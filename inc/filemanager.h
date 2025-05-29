#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <cstdint>
#include <ctime>
#include <filesystem>
#include <string>
#include <vector>
#include "command.h"
#include "jsonreader.h"

struct FileInfo
{
    std::string path;
    std::string hash;
    std::time_t last_modified;
    uintmax_t file_size;
};

namespace fs = std::filesystem;
class Terminal
{
private:
    fs::path file_path;
    std::string command;
    std::vector<std::string> tokens;
    ParsedCommand parsed_command;

public:
    Terminal(const std::string &systemDirectory);
    void run();
    void runCommand(const std::string &input);
    void redistrubuteTokens();
};

#endif
