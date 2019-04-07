#include "headers/ImageProcessor.h"

// Bilinear Interpolation approach

ImageProcessor::ImageProcessor()
                       : redChannel(new uint8_t[TOTAL_PIX]{0}),
                         blueChannel(new uint8_t[TOTAL_PIX]{0}),
                         greenChannel(new uint8_t[TOTAL_PIX]{0})
{
}


ImageProcessor::~ImageProcessor()
{
    delete redChannel;
    delete blueChannel;
    delete greenChannel;
}


void ImageProcessor::SeperateChannels(uint8_t* cfa)
{
    InitializeRedChannel(cfa);
    InitializeGreenChannel(cfa);
    InitializeBlueChannel(cfa);
}


void ImageProcessor::InitializeRedChannel(uint8_t* cfa)
{
    for (int itrRed = 0; itrRed < TOTAL_PIX;)
    {
        int row = itrRed / IMAGE_WIDTH;
        if (row % 2 == 0)
        {
            redChannel[itrRed] = cfa[itrRed];
            itrRed += 2;
        }
        else
        {
            itrRed += IMAGE_WIDTH;
        }
    }
}


void ImageProcessor::InitializeBlueChannel(uint8_t* cfa)
{
    for (int itrBlue = IMAGE_WIDTH + 1; itrBlue < TOTAL_PIX;)
    {
        int row = itrBlue / IMAGE_WIDTH;
        if (row % 2 != 0)
        {
            blueChannel[itrBlue] = cfa[itrBlue];
            itrBlue += 2;
        }
        else
        {
            itrBlue += IMAGE_WIDTH;
        }
    }
}


void ImageProcessor::InitializeGreenChannel(uint8_t* cfa)
{
    for (int itrGreen = 1; itrGreen < TOTAL_PIX; itrGreen += 2)
    {
        int row = itrGreen / IMAGE_WIDTH;
        if (row % 2 == 0)
        {
            greenChannel[itrGreen] = cfa[itrGreen];
        }
        else
        {
            greenChannel[itrGreen - 1] = cfa[itrGreen - 1];
        }
    }
}


void ImageProcessor::Red()
{
    int row;
    for (int itrChnl = 1; itrChnl < TOTAL_PIX; itrChnl += 2)
    {
        row = itrChnl / IMAGE_WIDTH;
        if (row % 2 == 1)
        {
            redChannel[itrChnl - 1] = (redChannel[itrChnl - 1 - IMAGE_WIDTH] 
                                 +  redChannel[itrChnl - 1 + IMAGE_WIDTH]) / 2;
            redChannel[itrChnl + 1] = (redChannel[itrChnl+1-IMAGE_WIDTH] 
                                 +  redChannel[itrChnl+1+IMAGE_WIDTH]) / 2;
        }
        redChannel[itrChnl] = (redChannel[itrChnl - 1] + redChannel[itrChnl + 1]) / 2;
    }
    std::fill(redChannel, redChannel+IMAGE_WIDTH, 0); // first row
    std::fill(redChannel + TOTAL_PIX - IMAGE_WIDTH, redChannel + TOTAL_PIX, 0); //last row
}


void ImageProcessor::Blue()
{
    int row;
    for (int itrChnl = 0; itrChnl < TOTAL_PIX; itrChnl += 2)
    {
        row = itrChnl / IMAGE_WIDTH;
        if (row % 2 == 0)
        {
            blueChannel[itrChnl - 1] = (blueChannel[itrChnl - 1 - IMAGE_WIDTH] 
                                 +  blueChannel[itrChnl - 1 + IMAGE_WIDTH]) / 2;
            blueChannel[itrChnl + 1] = (blueChannel[itrChnl+1-IMAGE_WIDTH] 
                                 +  blueChannel[itrChnl+1+IMAGE_WIDTH]) / 2;
        }
        blueChannel[itrChnl] = (blueChannel[itrChnl - 1] + blueChannel[itrChnl + 1]) / 2;
    }
    std::fill(blueChannel, blueChannel+IMAGE_WIDTH, 0); // first row
    std::fill(blueChannel + TOTAL_PIX - IMAGE_WIDTH, blueChannel + TOTAL_PIX, 0); //last row
}


void ImageProcessor::Green()
{
    for (int itrChnl = IMAGE_WIDTH+1; itrChnl < TOTAL_PIX;)
    {
        greenChannel[itrChnl] = (greenChannel[itrChnl - 1] + greenChannel[itrChnl + 1] 
                         +  greenChannel[itrChnl - IMAGE_WIDTH]
                         +  greenChannel[itrChnl + IMAGE_WIDTH])/4;
        if (itrChnl / IMAGE_WIDTH != (itrChnl + 2) / IMAGE_WIDTH)
        {
            itrChnl += 3;
            continue;
        }
        itrChnl += 2;
    }
    std::fill(greenChannel, greenChannel+IMAGE_WIDTH, 0); //first row
    std::fill(greenChannel + TOTAL_PIX - IMAGE_WIDTH, greenChannel + TOTAL_PIX, 0); //last row
}