#ifndef Raw12Img_H
#define Raw12Img_H

#include "functional.h"
#include "BMP_HEAD.h"
#include "PPM_HEAD.h"
#include "Demosaicing.h"
#define inputSize (4096 * 3072 * 3 / 2)
#define totalPix (4096 * 3072)

struct Channels
{
    uint8_t red[totalPix]{0};
    uint8_t blue[totalPix]{0};
    uint8_t green[totalPix]{0};

    void Push(uint8_t r, uint8_t g, uint8_t b)
    {
        static int index = 0;
        red[index] = r;
        green[index] = g;
        blue[index] = b;
        index++;
    }
};

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

#endif
