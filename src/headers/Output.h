// assuming C++11 or higher compiler
#ifndef OUTPUT_IMAGE_H
#define OUTPUT_IMAGE_H

#include "Input.h"
#include "OutStructs.h"

class InputImage;

class OutputImage
{
    uint8_t* bmpBinary;
    uint8_t* ppmBinRed;
    uint8_t* ppmBinGreen;
    uint8_t* ppmBinBlue;
    std::ofstream file;
    BitmapFileHeader flleHeader;
    BitmapInfoHeader infoHeader;
    MainAVIHeader MainHeader;
    AVIStreamHeader StreamHeader;
    AVIStreamFormat StreamFormat;

public:
    OutputImage(InputImage*);
    void WritePpm(std::string);
    void WritePpmRed(uint8_t*, std::string);
    void WriteBmp();
    void WriteToAvi();
    uint8_t* GetBmpBinary(uint8_t*, uint8_t*, uint8_t*);
    uint8_t* GetPpmBinary(uint8_t*, std::string);
};

#endif
