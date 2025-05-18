#include "filemanager.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs=std::filesystem;

Terminal::Terminal(const std::string &systemDirectory)
{
    file_path=fs::current_path();
    if(fs::is_empty(file_path))
    {
        fs::create_directory(systemDirectory);
    }
    file_path=fs::current_path()/systemDirectory;
}


void Terminal::run()
{
    std::cout<<file_path<<'\n';
    std::cin>>    
}
