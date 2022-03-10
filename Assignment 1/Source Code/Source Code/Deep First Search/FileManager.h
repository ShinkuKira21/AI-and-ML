#pragma once
#include "../Library/Functions.h"
#include <fstream>
#include <vector>


namespace FileManager {
    // Inspiration from Gordan Dicker's code.
    // However, some changes are made.
    struct Config { 
        char* file;
        const char* directory = "content/";
        size_t height = 0, width = 0;
    };

    // More logic required here
    inline std::string FileSelector(const char* filename)
    { return Config().directory + (std::string)filename; }

    // Dynamic Pointer Control
    inline char* CreateCharPtr(size_t size)
    { return new char[size]; }

    inline void DeleteCharPtr(char* text)
    { delete[] text; }

    inline std::vector<std::string> CopyFileContents(std::ifstream& file, Config* config)
    {
        // Dynamically Allocated File Size
        std::string row; std::vector<std::string> rows;
        for (size_t i = 0; getline(file, row); i++) {
            if (i == 0) config->width = row.size();
            config->height++;
            rows.push_back(row);
        }

        return rows;
    }

    inline Config OpenFile(const char* path)
    {
        Config config;
        std::ifstream file(path);

        if (file.is_open()) {
            std::vector<std::string> rows = CopyFileContents(file, &config);
            config.file = CreateCharPtr(config.width * config.height);

            for (size_t i = 0; i < rows.size(); i++)
                for (size_t j = 0; j < rows[i].size(); j++)
                {
                    config.file[config.width * i + j] = rows[i][j];
                    if (i + 1 == rows.size() && j + 1 == rows.size()) config.file[config.width * i + j] = '\0';
                }
                    

            rows.clear();
        }
        else std::cout << "Unable to open file\n";

        file.close();
        return config;
    }

    inline void DisposeConfig(Config config)
    {
        if(config.height > 0)
			DeleteCharPtr(config.file);
    }
}