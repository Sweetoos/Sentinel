#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <cstdint>
#include <ctime>
#include <string>
#include <map>
#include <functional>

struct FileInfo
{
    std::string path;
    std::string hash;
    std::time_t last_modified;
    uintmax_t file_size;
};

class Terminal
{
private:
    std::string file_path;

public:
    std::map<std::string, std::function<int>> command();
};

#endif
