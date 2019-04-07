#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <iostream>
#include <fstream>
#include <cstdint>
#define IMAGE_WIDTH 4096
#define IMAGE_HEIGHT 3072
#define INPUT_SIZE (4096 * 3072 * 3 / 2)
#define TOTAL_PIX (4096 * 3072)

class ImageLoader
{   
    char* fileData;
    std::string _filePath;
    std::ifstream _intputFile;

public:
    uint8_t *cfa;
    ImageLoader(std::string);
    ~ImageLoader();
    void LoadImage();
};

#endif
