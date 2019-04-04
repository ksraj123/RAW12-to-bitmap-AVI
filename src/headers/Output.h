// assuming C++11 or higher compiler
#ifndef OUTPUT_IMAGE
#define OUTPUT_IMAGE

#include "functional.h"
#include "Input.h"
#include "OutStructs.h"

class InputImage;

class OutputImage
{
    std::ofstream file;
    BitmapFileHeader flleHeader;
    BitmapInfoHeader infoHeader;
    MainAVIHeader MainHeader;
    AVIStreamHeader StreamHeader;
    AVIStreamFormat StreamFormat;

    public:
    void WriteOutput(InputImage*);
    void WritePpm(uint8_t*, std::string);
    void WritePpmRed(uint8_t*, std::string);
    void WriteBmp(uint8_t*, uint8_t*, uint8_t*);
    void WriteToAvi(uint8_t*, uint8_t*, uint8_t*);
};

#endif // BMP_HEAD
