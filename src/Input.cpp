#include "headers/Input.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)

// Constructor - defines arrays and loads the image
ImageLoader::ImageLoader(std::string filePath)
              : _filePath(filePath),
                cfa(new uint8_t[TOTAL_PIX]{0}),
                fileData(new char[INPUT_SIZE]{0})

{
}

ImageLoader::~ImageLoader()
{
    delete fileData;
    delete cfa;
}

void ImageLoader::LoadImage()
{
    _intputFile.open(_filePath, std::ios::binary);
    if(!_intputFile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
        _intputFile.read(fileData, INPUT_SIZE);
    for (int itrFileData = 0, itrCfa = 0; itrFileData < INPUT_SIZE, itrCfa < TOTAL_PIX; itrFileData += 3, itrCfa+=2)
    {
        cfa[itrCfa] = fileData[itrFileData];
        cfa[itrCfa + 1] = Sensel(fileData[itrFileData + 1], fileData[itrFileData + 2]);
    }
    _intputFile.close();
}