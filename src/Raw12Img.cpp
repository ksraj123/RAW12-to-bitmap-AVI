#include "headers/Raw12Img.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)
#include <endian.h>

Channels chnl;
char* fileData;

Raw12Img::Raw12Img(std::string t_fileName)
            : m_fileName(t_fileName)
{
}

void Raw12Img::Load()
{
    std::ifstream intputFile;
    intputFile.open(m_fileName.c_str(), std::ios::binary);
    if(!intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
    fileData = new char [inputSize];
    intputFile.read(fileData, inputSize);
    for (int itr = 0; itr < inputSize; itr+= 3)
    {
        int row = (itr * 2) / (max_width * 3);
        if (row % 2 == 0)
        {
        chnl.Push(fileData[itr], 0, 0);
        chnl.Push(0, Sensel(fileData[itr+1], fileData[itr+2]), 0);
        }
        else
        {
            chnl.Push(0, fileData[itr], 0);
            chnl.Push(0, 0, Sensel(fileData[itr+1], fileData[itr+2]));
        }
    }
    intputFile.close();
}

void Raw12Img::DebayerChannels()
{
    Demosaic::Red(chnl.red);
    Demosaic::Green(chnl.green);
    Demosaic::Blue(chnl.blue);
}

void Raw12Img::WriteChannels()
{
    OutputImage::PixelMap::Write(chnl.red, "red");
    OutputImage::PixelMap::Write(chnl.green, "green");
    OutputImage::PixelMap::Write(chnl.blue, "blue");
}

void Raw12Img::WriteDebayered()
{
    OutputImage::bitmap::Write(chnl.red, chnl.blue, chnl.green);
}
