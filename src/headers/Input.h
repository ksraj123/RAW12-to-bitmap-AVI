#ifndef INPUT_IMAGE_H
#define INPUT_IMAGE_H

#include <iostream>
#include <fstream>
#include <cstdint>
#define IMAGE_WIDTH 4096
#define IMAGE_HEIGHT 3072
#define INPUT_SIZE (4096 * 3072 * 3 / 2)
#define TOTAL_PIX (4096 * 3072)

class Raw12Img
{   

    uint8_t *cfa;
    char* fileData;
    std::string _filePath;
    std::ifstream _intputFile;

public:
    uint8_t *redChannel;
    uint8_t *blueChannel;
    uint8_t *greenChannel;
    Raw12Img(std::string);
    ~Raw12Img();
    void Push(uint8_t, uint8_t, uint8_t);
    void LoadImage();
    void InitializeCfa();
    void InitializeChannels();
    void print5by5tile();
    void printIntensity(uint8_t*);
    void InitializeRedChannel();
    void InitializeBlueChannel();
    void InitializeGreenChannel();
};

#endif
