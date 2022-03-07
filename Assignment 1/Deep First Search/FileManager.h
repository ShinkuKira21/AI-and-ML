#pragma once
#include "../Library/Functions.h"
#include <fstream>


namespace FileManager {
    // Inspiration from Gordan Dicker's code.
    // However, some changes are made.
    struct Config { 
        char* file;
        const char* directory = "content/";
        size_t height = 0, width = 0;
    };
    
    // More logic required here
    std::string FileSelector(const char* filename)
    { return Config().directory + (std::string)filename; }

    // Dynamic Pointer Control
    char* CreateCharPtr(int size)
    { return new char[size]; }

    void DeleteCharPtr(char* text)
    { delete[] text; }

    Config OpenFile(const char* path)
    {
        Config config;
        std::ifstream file(path);

        if(file.is_open())
        { 
            // Dynamically Allocated File Size
            std::string row;
            for(size_t i = 0; getline(file, row); i++) {
                if(i == 0) config.width = row.size();
                config.height++;
            }

            // Create the CStr
            config.file = CreateCharPtr(config.width * config.height);

            for(size_t i = 0; getline(file, row); i++)
                row.copy(&config.file[config.width + i], config.width, 0);
            
        } else std::cout << "Unable to open file\n";


        file.close();
        return config;
    }

    void DisposeConfig(Config config)
    {
        DeleteCharPtr(config.file);
    }
}