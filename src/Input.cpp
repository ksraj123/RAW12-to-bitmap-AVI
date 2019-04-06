#include "headers/Input.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)

// Constructor - defines arrays and loads the image
InputImage::InputImage(std::string filePath)
              : _filePath(filePath),
                redChannel(new uint8_t[TOTAL_PIX]{0}),
                blueChannel(new uint8_t[TOTAL_PIX]{0}),
                greenChannel(new uint8_t[TOTAL_PIX]{0}),
                cfa(new uint8_t[TOTAL_PIX]{0}),
                fileData(new char[INPUT_SIZE]{0})

{
    _intputFile.open(_filePath, std::ios::binary);
    if(!_intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
}

// Reads the CFA and initializes the channels
void InputImage::Load()
{
    _intputFile.read(fileData, INPUT_SIZE);
    for (int itrFileData = 0, itrCfa = 0; itrFileData < INPUT_SIZE, itrCfa < TOTAL_PIX; itrFileData += 3, itrCfa+=2)
    {
        cfa[itrCfa] = fileData[itrFileData];
        cfa[itrCfa + 1] = Sensel(fileData[itrFileData + 1], fileData[itrFileData + 2]);
    }
    _intputFile.close();
}

void InputImage::InitializeChannels()
{
    InitializeRedChannel();
    InitializeGreenChannel();
    InitializeBlueChannel();
}

// Returns pointer to Red Channel
void InputImage::InitializeRedChannel()
{
    for (int itrRed = 0; itrRed < TOTAL_PIX;)
    {
        int row = itrRed / IMAGE_WIDTH;
        if (row % 2 == 0)
        {
            redChannel[itrRed] = cfa[itrRed];
            itrRed += 2;
        }
        else
        {
            itrRed += IMAGE_WIDTH;
        }
    }
}

// Returns pointer to Blue Channel
void InputImage::InitializeBlueChannel()
{
    for (int itrBlue = IMAGE_WIDTH + 1; itrBlue < TOTAL_PIX;)
    {
        int row = itrBlue / IMAGE_WIDTH;
        if (row % 2 != 0)
        {
            blueChannel[itrBlue] = cfa[itrBlue];
            itrBlue += 2;
        }
        else
        {
            itrBlue += IMAGE_WIDTH;
        }
    }
}

// Returns pointer to Green Channel
void InputImage::InitializeGreenChannel()
{
    for (int itrGreen = 1; itrGreen < TOTAL_PIX; itrGreen += 2)
    {
        int row = itrGreen / IMAGE_WIDTH;
        if (row % 2 == 0)
        {
            greenChannel[itrGreen] = cfa[itrGreen];
        }
        else
        {
            greenChannel[itrGreen - 1] = cfa[itrGreen - 1];
        }
    }
}

InputImage::~InputImage()
{
    delete redChannel;
    delete blueChannel;
    delete greenChannel;
    delete fileData;
    delete cfa;
}