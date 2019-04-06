#include "headers/Demosaicing.h"

// Bilinear Interpolation approach

void Demosaic::Red(uint8_t* channel)
{
    int row;
    for (int itrChnl = 1; itrChnl < TOTAL_PIX; itrChnl += 2)
    {
        row = itrChnl / IMAGE_WIDTH;
        if (row % 2 == 1)
        {
            channel[itrChnl - 1] = (channel[itrChnl - 1 - IMAGE_WIDTH] 
                                 + channel[itrChnl - 1 + IMAGE_WIDTH]) / 2;
            channel[itrChnl + 1] = (channel[itrChnl+1-IMAGE_WIDTH] 
                                 + channel[itrChnl+1+IMAGE_WIDTH]) / 2;
        }
        channel[itrChnl] = (channel[itrChnl - 1] + channel[itrChnl + 1]) / 2;
    }
    std::fill(channel, channel+IMAGE_WIDTH, 0); // first row
    std::fill(channel + TOTAL_PIX - IMAGE_WIDTH, channel + TOTAL_PIX, 0); //last row
 }

void Demosaic::Blue(uint8_t* channel)
{
    int row;
    for (int itrChnl = 0; itrChnl < TOTAL_PIX; itrChnl += 2)
    {
        row = itrChnl / IMAGE_WIDTH;
        if (row % 2 == 0)
        {
            channel[itrChnl - 1] = (channel[itrChnl - 1 - IMAGE_WIDTH] 
                                 + channel[itrChnl - 1 + IMAGE_WIDTH]) / 2;
            channel[itrChnl + 1] = (channel[itrChnl+1-IMAGE_WIDTH] 
                                 + channel[itrChnl+1+IMAGE_WIDTH]) / 2;
        }
        channel[itrChnl] = (channel[itrChnl - 1] + channel[itrChnl + 1]) / 2;
    }
    std::fill(channel, channel+IMAGE_WIDTH, 0); // first row
    std::fill(channel + TOTAL_PIX - IMAGE_WIDTH, channel + TOTAL_PIX, 0); //last row
 }

void Demosaic::Green(uint8_t* channel)
{
    for (int itrChnl = IMAGE_WIDTH+1; itrChnl < TOTAL_PIX;)
    {
        channel[itrChnl] = (channel[itrChnl - 1] + channel[itrChnl + 1] 
                          + channel[itrChnl - IMAGE_WIDTH]
                          + channel[itrChnl + IMAGE_WIDTH])/4;
        if (itrChnl / IMAGE_WIDTH != (itrChnl + 2) / IMAGE_WIDTH)
        {
            itrChnl += 3;
            continue;
        }
        itrChnl += 2;
    }
    std::fill(channel, channel+IMAGE_WIDTH, 0); //first row
    std::fill(channel + TOTAL_PIX - IMAGE_WIDTH, channel + TOTAL_PIX, 0); //last row
}
