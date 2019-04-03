#include "headers/Raw12Img.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)
#include <endian.h>

// constructor of class Channels
Channels::Channels()
{
    red = new uint8_t[2*totalPix]{0};
    blue = new uint8_t[2*totalPix]{0};
    green = new uint8_t[2*totalPix]{0};
    fileData = new char [2*inputSize]{0};
}

// member fuction of class Channels
void Channels::Push(uint8_t r, uint8_t g, uint8_t b)
{
    static int index = 0;
    red[index] = r;
    green[index] = g;
    blue[index] = b;
    index++;
}

// constructor of class Raw12Img
Raw12Img::Raw12Img(std::string filePath)
            : _filePath(filePath)
{
    _intputFile.open(_filePath, std::ios::binary);
    if(!_intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
}

// member fuction of class Raw12Img
void Raw12Img::Load()
{
    _intputFile.read(chnl.fileData, inputSize);
    for (int itr = 0; itr < inputSize; itr+= 3)
    {
        int row = (itr * 2) / (max_width * 3);
        if (row % 2 == 0)
        {
            chnl.Push(chnl.fileData[itr], 0, 0);
            chnl.Push(0, Sensel(chnl.fileData[itr+1], chnl.fileData[itr+2]), 0);
        }
        else
        {
            chnl.Push(0, chnl.fileData[itr], 0);
            chnl.Push(0, 0, Sensel(chnl.fileData[itr+1], chnl.fileData[itr+2]));
        }
    }
    _intputFile.close();
}

// member fuction of class Raw12Img
void Raw12Img::DebayerChannels()
{
    // Calling methods in namespace Demosaic
    Demosaic::Type1(chnl.red, 1);
    Demosaic::Type2(chnl.green);
    Demosaic::Type1(chnl.blue, 0);
}

// member fuction of class Raw12Img
void Raw12Img::WriteChannels()
{
    // WritePpm() declared in headers/OutImg.h
    WritePpm(chnl.red, "red");
    WritePpm(chnl.green, "green");
    WritePpm(chnl.blue, "blue");
}

// member fuction of class Raw12Img
void Raw12Img::WriteDebayered()
{
    // WriteBmp() declared in headers/OutImg.h
    WriteBmp(chnl.red, chnl.blue, chnl.green);
}


void Raw12Img::WriteAVI()
{
    WriteToAvi(chnl.red, chnl.blue, chnl.green);
}
