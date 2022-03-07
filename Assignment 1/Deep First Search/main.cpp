#include "FileManager.h"

int main(int argc, char **argv)
{
    FileManager::Config conf = FileManager::OpenFile(FileManager::FileSelector("m1.txt").c_str());

    for(size_t i = 0; i < conf.height; i++)
    {
        for(size_t j = 0; j < conf.width; j++) 
            std::cout << conf.file[conf.width * i + j];
        
        std::cout << std::endl;
    }
        

    FileManager::DisposeConfig(conf);

    return 0;
}