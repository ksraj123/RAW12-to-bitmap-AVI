#include "headers/Raw12Img.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)
#include <endian.h>

Channels chnl;

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
    intputFile.read(chnl.fileData, inputSize);
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
    intputFile.close();
}

void Raw12Img::DebayerChannels()
{
    Demosaic::Type1(chnl.red, 1);
    Demosaic::Type2(chnl.green);
    Demosaic::Type1(chnl.blue, 0);
}

void Raw12Img::WriteChannels()
{
    WritePpm(chnl.red, "red");
    WritePpm(chnl.green, "green");
    WritePpm(chnl.blue, "blue");
}

void Raw12Img::WriteDebayered()
{
    WriteBmp(chnl.red, chnl.blue, chnl.green);
}
