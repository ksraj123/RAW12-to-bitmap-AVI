#ifndef DEMOSAIC_H
#define DEMOSAIC_H

#include "Input.h"

class Demosaic
{
public:
	void DemosaicChannels(Raw12Img*);
    void Red(uint8_t*);
    void Blue(uint8_t*);
    void Green(uint8_t*);
};

#endif
