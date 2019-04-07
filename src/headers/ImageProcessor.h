#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "ImageLoader.h"

class ImageProcessor
{
	void InitializeRedChannel(uint8_t*);
    void InitializeBlueChannel(uint8_t*);
    void InitializeGreenChannel(uint8_t*);
    
public:
	uint8_t *redChannel;
    uint8_t *blueChannel;
    uint8_t *greenChannel;
    ImageProcessor();
    ~ImageProcessor();
    void Red();
    void Blue();
    void Green();
    void SeperateChannels(uint8_t*);
};

#endif
