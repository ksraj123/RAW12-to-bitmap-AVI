#ifndef Raw12Img_H
#define Raw12Img_H

#include "functional.h"
#include "OutImg.h"
#include "Demosaicing.h"
#define inputSize (4096 * 3072 * 3 / 2)
#define totalPix (4096 * 3072)

class Raw12Img
{
    std::string m_fileName;

    public:
    Raw12Img (std::string);
    void Load();
    void DebayerChannels();
    void WriteChannels();
    void WriteDebayered();
};

class Channels
{
    public:
    uint8_t *red;
    uint8_t *blue;
    uint8_t *green;
    char* fileData;

    Channels()
    {
        red = new uint8_t[totalPix]{0};
        blue = new uint8_t[totalPix]{0};
        green = new uint8_t[totalPix]{0};
        fileData = new char [inputSize]{0};
    }

    void Push(uint8_t r, uint8_t g, uint8_t b)
    {
        static int index = 0;
        red[index] = r;
        green[index] = g;
        blue[index] = b;
        index++;
    }
};

#endif
