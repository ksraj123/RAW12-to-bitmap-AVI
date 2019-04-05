#include "headers/Input.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)

InputImage::InputImage(std::string filePath)
             : _filePath(filePath)
{
    red = new uint8_t[TOTAL_PIX]{0};
    blue = new uint8_t[TOTAL_PIX]{0};
    green = new uint8_t[TOTAL_PIX]{0};
    fileData = new char [INPUT_SIZE]{0};

    _intputFile.open(_filePath, std::ios::binary);
    if(!_intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
}

void InputImage::Push(uint8_t r, uint8_t g, uint8_t b)
{
    static int index = 0;
    red[index] = r;
    green[index] = g;
    blue[index] = b;
    index++;
}

void InputImage::Load()
{
    _intputFile.read(fileData, INPUT_SIZE);
    for (int itr = 0; itr < INPUT_SIZE; itr+= 3)
    {
        int row = (itr * 2) / (MAX_WIDTH * 3);
        if (row % 2 == 0)
        {
            Push(fileData[itr], 0, 0);
            Push(0, Sensel(fileData[itr+1], fileData[itr+2]), 0);
        }
        else
        {
            Push(0, fileData[itr], 0);
            Push(0, 0, Sensel(fileData[itr+1], fileData[itr+2]));
        }
    }
    _intputFile.close();
}

uint8_t* InputImage::GetRedChannel()
{
    return red;
}

uint8_t* InputImage::GetBlueChannel()
{
    return blue;
}

uint8_t* InputImage::GetGreenChannel()
{
    return green;
}