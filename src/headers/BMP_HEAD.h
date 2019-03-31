// assuming C++11 or higher compiler
#ifndef BMP_HEAD
#define BMP_HEAD
#include "functional.h"

namespace OutputImage
 {
namespace bitmap
 {
void Write_bitmap(unsigned char* arr_r,
                  unsigned char* arr_b,
                  unsigned char* arr_g);

#pragma pack(push, 2)

struct BitmapFileHeader
 {
      char header[2];
      std::int32_t fileSize;
      std::int32_t reserved;
      std::int32_t dataOffset;

      BitmapFileHeader()
       {
            reserved = 0;
            header[0] = 'B';
            header[1] = 'M';
       }
 };

struct BitmapInfoHeader
 {
      std::int32_t headerSize;
      std::int32_t width;
      std::int32_t height;
      std::int16_t planes;
      std::int16_t bitsPerPixel;
      std::int32_t compression;
      std::int32_t dataSize;
      std::int32_t horizontalResolution;
      std::int32_t verticalResolution;
      std::int32_t colours{0};
      std::int32_t importantColors;

      BitmapInfoHeader()
       {
            width = max_width;
            height = max_height;
            headerSize = 40;
            planes = 1;
            bitsPerPixel = 24;
            compression = 0;
            dataSize = 0;
            horizontalResolution = 2400;
            verticalResolution = 2400;
            colours = 0;
            importantColors = 0;
       }
 };
 }
 }

#pragma pack(pop)
#endif // BMP_HEAD
