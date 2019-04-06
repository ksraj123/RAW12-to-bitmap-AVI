#include "headers/Demosaicing.h"

// Bilinear Interpolation approach

void Demosaic::DemosaicChannels(InputImage* input)
{
    std::cout << "Demosaicing Red channel\n";
    RedBlue(input->GetRedChannel(), 1);
    std::cout << "Demosaicing Green channel\n";
    Green(input->GetGreenChannel());
    std::cout << "Demosaicing Blue channel\n";
    RedBlue(input->GetBlueChannel(), 0);
}

// This fuction demosaics red and blue channels
// the approach to demosaicing red and blue channels
// are similar hence they are delt with in one fuction
void Demosaic::RedBlue(uint8_t* channel, int startPos)
{
    int row;
    for (int itrChnl = startPos; itrChnl < TOTAL_PIX; itrChnl+=2)
    {
        row = itrChnl / IMAGE_WIDTH;
        if (row % 2 == startPos)
        {
            channel[itrChnl-1] = (channel[itrChnl-1-IMAGE_WIDTH] 
                                + channel[itrChnl-1+IMAGE_WIDTH])/2;
            channel[itrChnl+1] = (channel[itrChnl+1-IMAGE_WIDTH] 
                                + channel[itrChnl+1+IMAGE_WIDTH])/2;
        }
        channel[itrChnl] = (channel[itrChnl-1] + channel[itrChnl+1])/2;
    }
    std::fill(channel, channel+IMAGE_WIDTH, 0); // first row
    std::fill(channel+TOTAL_PIX-IMAGE_WIDTH, channel+TOTAL_PIX, 0); //last row
 }

// This fuctions demosaics green channel
void Demosaic::Green(uint8_t* channel)
{
    for (int itrChnl = 0; itrChnl < TOTAL_PIX;)
    {
        channel[itrChnl] = (channel[itrChnl-1] + channel[itrChnl+1] 
                          + channel[itrChnl-IMAGE_WIDTH]
                          + channel[itrChnl+IMAGE_WIDTH])/4;
        if (itrChnl/IMAGE_WIDTH != (itrChnl+2)/IMAGE_WIDTH)
        {
            itrChnl+= 3;
            continue;
        }
        itrChnl+=2;
    }
    std::fill(channel, channel+IMAGE_WIDTH, 0); //first row
    std::fill(channel+TOTAL_PIX-IMAGE_WIDTH, channel+TOTAL_PIX, 0); //last row
}
