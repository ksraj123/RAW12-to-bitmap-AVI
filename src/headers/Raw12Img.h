#ifndef Raw12Img_H
#define Raw12Img_H

#include "functional.h"
#include "OutImg.h"
#include "Demosaicing.h"
#include "riffAVI.h"
#define inputSize (4096 * 3072 * 3 / 2)
#define totalPix (4096 * 3072)

class Channels
{
    public:
    uint8_t *red;
    uint8_t *blue;
    uint8_t *green;
    char* fileData;

    Channels();
    void Push(uint8_t, uint8_t, uint8_t);
};

class Raw12Img
{
    std::string _filePath;
    std::ifstream _intputFile;

    public:
    Channels chnl;
    Raw12Img (std::string);
    void Load();
    void DebayerChannels();
    void WriteChannels();
    void WriteAVI();
    void WriteDebayered();
};

#endif
