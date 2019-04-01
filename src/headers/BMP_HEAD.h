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
         char header[2] {'B', 'M'};
         std::int32_t fileSize;
         std::int32_t reserved {0};
         std::int32_t dataOffset;
    };
 
    struct BitmapInfoHeader
     {
          std::int32_t headerSize {40};
          std::int32_t width {max_width};
          std::int32_t height {max_height};
          std::int16_t planes {1};
          std::int16_t bitsPerPixel {24};
          std::int32_t compression {0};
          std::int32_t dataSize {0};
          std::int32_t horizontalResolution {2400};
          std::int32_t verticalResolution {2400};
          std::int32_t colours{0};
          std::int32_t importantColors {0};
     };
   }
 }

#pragma pack(pop)
#endif // BMP_HEAD
