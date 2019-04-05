#include "headers/Demosaicing.h"
#include <algorithm>

// Bilinear Interpolation approach

void Demosaic::DemosaicChannels(InputImage* input)
{
    std::cout << "Demosaicing Red channel\n";
    Type1(input->GetRedChannel(), 1);
    std::cout << "Demosaicing Green channel\n";
    Type2(input->GetGreenChannel());
    std::cout << "Demosaicing Blue channel\n";
    Type1(input->GetBlueChannel(), 0);
}

// This fuction demosaics red and blue channels
// the approach to demosaicing red and blue channels
// are similar hence they are delt with in one fuction
void Demosaic::Type1(uint8_t* arr, int start)
{
    int row;
    for (int itr = start; itr < TOTAL_PIX; itr+=2)
    {
        row = itr / MAX_WIDTH;
        if (row % 2 == start)
        {
            arr[itr-1] = (arr[itr-1-MAX_WIDTH] + arr[itr-1+MAX_WIDTH])/2;
            arr[itr+1] = (arr[itr+1-MAX_WIDTH] + arr[itr+1+MAX_WIDTH])/2;
        }
        arr[itr] = (arr[itr-1] + arr[itr+1])/2;
    }
    std::fill(arr, arr+MAX_WIDTH, 0); // first row
    std::fill(arr+TOTAL_PIX-MAX_WIDTH, arr+TOTAL_PIX, 0); //last row
 }

// This fuctions demosaics green channel
void Demosaic::Type2(uint8_t* arr)
{
    for (int itr = 0; itr < TOTAL_PIX;)
    {
        arr[itr] = (arr[itr-1] + arr[itr+1] + arr[itr-MAX_WIDTH]
                 + arr[itr+MAX_WIDTH])/4;
        if (itr/MAX_WIDTH != (itr+2)/MAX_WIDTH)
        {
            itr+= 3;
            continue;
        }
        itr+=2;
    }
    std::fill(arr, arr+MAX_WIDTH, 0); //first row
    std::fill(arr+TOTAL_PIX-MAX_WIDTH, arr+TOTAL_PIX, 0); //last row
}
