// assuming C++11 or higher compiler
#ifndef OUTPUT_IMAGE_H
#define OUTPUT_IMAGE_H

#include "Input.h"
#include "OutStructs.h"

class OutputImage
{
    uint8_t* bmpImage;
    uint8_t* ppmRedChnl;
    uint8_t* ppmGreenChnl;
    uint8_t* ppmBlueChnl;
    std::ofstream outputFile;
    BitmapFileHeader flleHeader;
    BitmapInfoHeader infoHeader;
    MainAVIHeader mainHeader;
    AVIStreamHeader streamHeader;
    AVIStreamFormat streamFormat;

public:
    OutputImage(Raw12Img*);
    ~OutputImage();
    void WritePpm(std::string);
    void WritePpmRed(uint8_t*, std::string);
    void WriteBmp();
    void WriteToAvi();
    uint8_t* GetBmpImage(uint8_t*, uint8_t*, uint8_t*);
    uint8_t* GetPpmChannel(uint8_t*, std::string);
};

#endif
