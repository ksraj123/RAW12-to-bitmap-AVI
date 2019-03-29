#ifndef AVI_H
#define AVI_H

#include "functional.h"

    struct Chunk{
    uint8_t ChunkID[4];
    uint32_t ChunkSize;
    uint8_t ChunkData[4];
    };

    struct MainAVIHeader{
uint32_t dwMicroSecPerFrame; //Time between frames
uint32_t dwMaxBytesPerSec; //AVI data rate
uint32_t dwReserved1;
uint32_t dwFlags; //type of data parameters
uint32_t dwTotalFrames; //Number of frames
uint32_t dwInitialFrames; //preview frames
uint32_t dwStreams; //Number of data streams in chunk
uint32_t dwSuggestedBufferSize; //Minimum playback buffer size
uint32_t dwWidth; //frame width in pixels
uint32_t dwHeight; //frame height in pixels
uint32_t dwScale; //time units
uint32_t dwRate; //playback rate
uint32_t dwStart; //Start time of AVI data
uint32_t dwLength; //Size of AVI data
} ;

struct AVIStreamHeader{
uint32_t fccType; //vids = video, auds = audio
uint32_t fccHandler; //compressor used
uint32_t dwFlags;
uint32_t dwReserved1;
uint32_t dwInitialFrames; //if interleaved no of preview frames
uint32_t dwScale; //playback stream characteristics
uint32_t dwRate;
uint32_t dwStart;
uint32_t dwLength;
uint32_t dwSuggestedBufferSize;
uint32_t dwQuality;
uint32_t dwSampleSize;
};

struct AVIStreamFormat{ //similar to BITMAPINFOHEADER
uint32_t biSize; //40
uint32_t biWidth; //image width
uint32_t biHeight; //image height
uint16_t biPlanes; //1
uint16_t biBitCount; //bits / pixel 1,4,8,16,24,32
uint32_t biCompression; //0,1,2,3, CRAM etc
uint32_t biSizeImage;
uint32_t biXPelsPerMeter; //resolution
uint32_t biYPelsPerMeter;
uint32_t biClrUsed;
uint32_t biClrImportant;
};

int write_to_avi(uint8_t arr_r[max_height+1][max_width+1],
                 uint8_t arr_b[max_height+1][max_width+1],
                 uint8_t arr_g[max_height+1][max_width+1]);

#endif
