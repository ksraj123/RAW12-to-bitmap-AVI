#include "headers/Raw12Img.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)
#include <endian.h>

Channels chnl;
Streams strm;
char* fileData;

Raw12Img::Raw12Img(std::string t_fileName)
            : m_fileName(t_fileName)
{
}

void Raw12Img::Load()
{
    strm.intputFile.open(m_fileName.c_str(), std::ios::binary);
    if(!strm.intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
    fileData = new char [inputSize];
    strm.intputFile.read(fileData, inputSize);
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
    strm.intputFile.close();
}

void Raw12Img::DebayerChannels()
{
    Demosaic::Red(chnl.red.data());
    Demosaic::Green(chnl.green.data());
    Demosaic::Blue(chnl.blue.data());
}

void Raw12Img::WriteChannels()
{
    OutputImage::PixelMap::Write(&strm.outputRed, chnl.red.data(), "red");
    OutputImage::PixelMap::Write(&strm.outputGreen, chnl.green.data(), "green");
    OutputImage::PixelMap::Write(&strm.outputBlue, chnl.blue.data(), "blue");
}

void Raw12Img::WriteDebayered()
{
    OutputImage::bitmap::Write(chnl.red.data(), chnl.blue.data(), chnl.green.data());
}
