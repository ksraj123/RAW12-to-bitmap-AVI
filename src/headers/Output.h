// assuming C++11 or higher compiler
#ifndef OUTPUT_IMAGE_H
#define OUTPUT_IMAGE_H

#include "Input.h"
#include "OutStructs.h"

class OutputWriter
{
    uint8_t* bmpImage;
    uint8_t* ppmRedChnl;
    uint8_t* ppmGreenChnl;
    uint8_t* ppmBlueChnl;
    BitmapFileHeader flleHeader;
    BitmapInfoHeader infoHeader;

public:
    static std::ofstream outputFile;
    OutputWriter();
    ~OutputWriter();
    void InitializeOutputChannels(Raw12Img*);
    void WritePpm(std::string);
    void WritePpmRed(uint8_t*, std::string);
    void WriteBmp();
    void WriteToAvi();
    uint8_t* GetBmpImage(uint8_t*, uint8_t*, uint8_t*);
    uint8_t* GetPpmChannel(uint8_t*, std::string);
};

class Chunk
{
    char _fourCC[4];
    uint32_t _size;
    Avi* _avi;

public:
    Chunk(std::string, uint32_t, Avi* avi = nullptr);
    void Write();
};

#endif
