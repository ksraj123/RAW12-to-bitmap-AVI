#include "headers/Input.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)

// Constructor - defines arrays and loads the image
Raw12Img::Raw12Img(std::string filePath)
              : _filePath(filePath),
                redChannel(new uint8_t[TOTAL_PIX]{0}),
                blueChannel(new uint8_t[TOTAL_PIX]{0}),
                greenChannel(new uint8_t[TOTAL_PIX]{0}),
                cfa(new uint8_t[TOTAL_PIX]{0}),
                fileData(new char[INPUT_SIZE]{0})

{
}

Raw12Img::~Raw12Img()
{
    delete redChannel;
    delete blueChannel;
    delete greenChannel;
    delete fileData;
    delete cfa;
}

void Raw12Img::LoadImage()
{
    _intputFile.open(_filePath, std::ios::binary);
    if(!_intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
}

// Reads the CFA and initializes the channels
void Raw12Img::InitializeCfa()
{
    _intputFile.read(fileData, INPUT_SIZE);
    for (int itrFileData = 0, itrCfa = 0; itrFileData < INPUT_SIZE, itrCfa < TOTAL_PIX; itrFileData += 3, itrCfa+=2)
    {
        cfa[itrCfa] = fileData[itrFileData];
        cfa[itrCfa + 1] = Sensel(fileData[itrFileData + 1], fileData[itrFileData + 2]);
    }
    _intputFile.close();
}

void Raw12Img::PrintIntensity(uint8_t* array)
{
    for (int row = 0; row < 5; ++row)
    {
        for (int index = 0; index < 5; ++index)
        {
            std::cout << (int)array[row * IMAGE_WIDTH + index] << " ";
        }
        std::cout << std::endl;
    }
}

void Raw12Img::Print5by5tile()
{
    std::cout << "Printing 5 by 5 tile of CFA" << std::endl;
    PrintIntensity(cfa);
    std::cout << "Printing 5 by 5 tile of Red Channel" << std::endl;
    PrintIntensity(redChannel);
    std::cout << "Printing 5 by 5 tile of Green Channel" << std::endl;
    PrintIntensity(greenChannel);
    std::cout << "Printing 5 by 5 tile of Blue Channel" << std::endl;
    PrintIntensity(blueChannel);
}

void Raw12Img::InitializeChannels()
{
    InitializeRedChannel();
    InitializeGreenChannel();
    InitializeBlueChannel();
}

// Returns pointer to Red Channel
void Raw12Img::InitializeRedChannel()
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
void Raw12Img::InitializeBlueChannel()
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
void Raw12Img::InitializeGreenChannel()
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