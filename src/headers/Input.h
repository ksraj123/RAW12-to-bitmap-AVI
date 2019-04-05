#ifndef INPUT_IMAGE_H
#define INPUT_IMAGE_H

#include <iostream>
#include <fstream>
#include <cstdint>
#define max_width 4096
#define max_height 3072
#define inputSize (4096 * 3072 * 3 / 2)
#define totalPix (4096 * 3072)

class InputImage
{
    uint8_t *red;
    uint8_t *blue;
    uint8_t *green;
    char* fileData;
    std::string _filePath;
    std::ifstream _intputFile;


public:
    InputImage(std::string);
    void Push(uint8_t, uint8_t, uint8_t);
    void Load();
    uint8_t* GetRedChannel();
    uint8_t* GetBlueChannel();
    uint8_t* GetGreenChannel();
};

#endif
