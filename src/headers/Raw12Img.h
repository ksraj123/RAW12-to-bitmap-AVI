#ifndef Raw12Img_H
#define Raw12Img_H

#include "functional.h"
#include "BMP_HEAD.h"
#include "PPM_HEAD.h"
#include "Demosaicing.h"
#define inputSize (4096 * 3072 * 3 / 2)
#define totalPix (4096 * 3072)

struct Streams
{
    std::ifstream intputFile;
    std::ofstream outputRed, outputBlue, outputGreen;
};

struct Channels
{
    std::vector <unsigned char> red;
    std::vector <unsigned char> blue;
    std::vector <unsigned char> green;

    void Push(unsigned char r, unsigned char g, unsigned char b)
    {
        red.push_back(r);
        green.push_back(g);
        blue.push_back(b);
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
