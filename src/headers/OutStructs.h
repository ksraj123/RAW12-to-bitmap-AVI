#ifndef OUTSTRUCTS_H
#define OUTSTRUCTS_H

#ifndef WIN32
#define GCC_PACK __attribute__((packed))
#else
#define GCC_PACK
#pragma pack(push,1)
#endif

struct BitmapFileHeader
{
    char header[2] {'B', 'M'};
    int32_t fileSize;
    int32_t reserved {0};
    int32_t dataOffset;
} GCC_PACK ;


struct BitmapInfoHeader
{
    int32_t headerSize {40};
    int32_t width {IMAGE_WIDTH};
    int32_t height {IMAGE_HEIGHT};
    int16_t planes {1};
    int16_t bitsPerPixel {24};
    int32_t compression {0};
    int32_t dataSize {0};
    int32_t horizontalResolution {2400};
    int32_t verticalResolution {2400};
    int32_t colours{0};
    int32_t importantColors {0};
} GCC_PACK ;


#ifdef _WIN32
#pragma pack(pop)
#endif

#include <string.h>
#include <stdlib.h>

struct Avi{};


struct MainAVIHeader : Avi
{
    uint32_t  MicroSecPerFrame {1000000};
    uint32_t  MaxBytesPerSec {IMAGE_HEIGHT * IMAGE_WIDTH * 3 + 1000};
    uint32_t  PaddingGranularity {2048};
    uint32_t  Flags {0};
    uint32_t  TotalFrames {1};
    uint32_t  InitialFrames {0};
    uint32_t  Streams {1};
    uint32_t  SuggestedBufferSize {IMAGE_HEIGHT * IMAGE_WIDTH * 3};
    uint32_t  Width {IMAGE_WIDTH};
    uint32_t  Height {IMAGE_HEIGHT};
    uint32_t  Reserved[4] {0};
} ;


struct AVIStreamHeader : Avi
{
    char fccType[4] {'v', 'i', 'd', 's'};
    char fccHandler[4] {'R', 'A', 'W', ' '};
    uint32_t  Flags{0};
    uint16_t  Priority{0};
    uint16_t  Language{0};
    uint32_t  InitialFrames{0};
    uint32_t  Scale{1};
    uint32_t  Rate{1};
    uint32_t  Start{0};
    uint32_t  Length{1};
    uint32_t  SuggestedBufferSize{IMAGE_HEIGHT * IMAGE_WIDTH * 3};
    int32_t   Quality{-1};
    uint32_t  SampleSize{0};
    struct
    {
        uint16_t left{0};
        uint16_t top{0};
        uint16_t right{IMAGE_WIDTH};
        uint16_t bottom{IMAGE_HEIGHT};
    }  rcFrame;
};


struct AVIStreamFormat : Avi
{
    uint32_t headerSize {40};
    uint32_t width {IMAGE_WIDTH};
    uint32_t height {IMAGE_HEIGHT};
    uint16_t planes {1};
    uint16_t bitsPerPixel {24};
    uint32_t compression {0};
    uint32_t dataSize {0};
    uint32_t horizontalResolution {2400};
    uint32_t verticalResolution {2400};
    uint32_t colours{0};
    uint32_t importantColors {0};
};

#endif