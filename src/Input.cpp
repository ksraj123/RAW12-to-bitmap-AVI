#include "headers/Input.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)

// Constructor - defines arrays and loads the image
InputImage::InputImage(std::string filePath)
              : _filePath(filePath),
                red(new uint8_t[TOTAL_PIX]{0}),
                blue(new uint8_t[TOTAL_PIX]{0}),
                green(new uint8_t[TOTAL_PIX]{0}),
                fileData(new char[INPUT_SIZE]{0})
{
    _intputFile.open(_filePath, std::ios::binary);
    if(!_intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
}

// Adds the current red pixel value to channels
void InputImage::Push(uint8_t r, uint8_t g, uint8_t b)
{
    static int index = 0;
    red[index] = r;
    green[index] = g;
    blue[index] = b;
    ++index;
}

// Reads the CFA and initializes the channels
void InputImage::Load()
{
    _intputFile.read(fileData, INPUT_SIZE);
    for (int itrFileData = 0; itrFileData < INPUT_SIZE; itrFileData+= 3)
    {
        int row = (itrFileData * 2) / (IMAGE_WIDTH * 3);
        if (row % 2 == 0)
        {
            Push(fileData[itrFileData], 0, 0);
            Push(0, Sensel(fileData[itrFileData+1], fileData[itrFileData+2]), 0);
        }
        else
        {
            Push(0, fileData[itrFileData], 0);
            Push(0, 0, Sensel(fileData[itrFileData+1], fileData[itrFileData+2]));
        }
    }
    _intputFile.close();
}

// Returns pointer to Red Channel
uint8_t* InputImage::GetRedChannel()
{
    return red;
}

// Returns pointer to Blue Channel
uint8_t* InputImage::GetBlueChannel()
{
    return blue;
}

// Returns pointer to Green Channel
uint8_t* InputImage::GetGreenChannel()
{
    return green;
}

InputImage::~InputImage()
{
    delete red;
    delete blue;
    delete green;
    delete fileData;
}