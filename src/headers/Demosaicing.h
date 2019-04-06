#ifndef DEMOSAIC_H
#define DEMOSAIC_H

#include "Input.h"

class Demosaic
{
public:
	void DemosaicChannels(InputImage*);
    void RedBlue(uint8_t*, int);
    void Green(uint8_t*);
};

#endif
