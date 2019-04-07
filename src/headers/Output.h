// assuming C++11 or higher compiler
#ifndef OUTPUT_IMAGE_H
#define OUTPUT_IMAGE_H

#include "Input.h"
#include "Demosaicing.h"
#include "OutStructs.h"

class OutputWriter
{
    uint8_t* bmpImage;
    uint8_t* ConvertToPPM(uint8_t*, std::string);
    uint8_t* ConvertToBMP(uint8_t*, uint8_t*, uint8_t*);

public:
    static std::ofstream outputFile;
    void static Print5by5tile (uint8_t* channel);
    void WritePpm(std::string, ImageProcessor*);
    void WriteBmp(ImageProcessor*);
    void WriteAvi();
};

class Chunk
{
    char _fourCC[4];
    uint32_t _size;
    Avi* _avi;

public:
    Chunk(std::string, uint32_t, Avi* avi = nullptr);
    void WriteToFile(std::ofstream*);
};

#endif
