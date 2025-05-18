#ifndef FILEMANAGER_H 
#define FILEMANAGER_H

#include <cstdint>
#include <ctime>
#include <string>
#include <filesystem>

struct FileInfo
{
    std::string path;
    std::string hash;
    std::time_t last_modified;
    uintmax_t file_size;
};

namespace fs=std::filesystem;
class Terminal
{
private:
    fs::path file_path;

public:
    Terminal(const std::string &systemDirectory);
    void run();
};

#endif
