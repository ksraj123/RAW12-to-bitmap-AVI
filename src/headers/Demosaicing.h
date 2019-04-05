#ifndef DEMOSAIC_H
#define DEMOSAIC_H

#include "Input.h"

class Demosaic
{
public:
	void DemosaicChannels(InputImage*);
    void Type1(uint8_t*, int);
    void Type2(uint8_t*);
};

#endif
