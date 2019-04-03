#include "headers/Demosaicing.h"
#include <algorithm>

// Bilinear Interpolation approach

// This fuction demosaics red and blue channels
// the approach to demosaicing red and blue channels
// are similar hence they are delt with in one fuction
void Demosaic::Type1(uint8_t* arr, int start)
{
    int row;
    for (int itr = start; itr < totalPix; itr+=2)
    {
        row = itr / max_width;
        if (row % 2 == start)
        {
            arr[itr-1] = (arr[itr-1-max_width] + arr[itr-1+max_width])/2;
            arr[itr+1] = (arr[itr+1-max_width] + arr[itr+1+max_width])/2;
        }
        arr[itr] = (arr[itr-1] + arr[itr+1])/2;
    }
    std::fill(arr, arr+max_width, 0); // first row
    std::fill(arr+totalPix-max_width, arr+totalPix, 0); //last row
 }

// This fuctions demosaics green channel
void Demosaic::Type2(uint8_t* arr)
{
    for (int itr = 0; itr < totalPix;)
    {
        arr[itr] = (arr[itr-1] + arr[itr+1] + arr[itr-max_width]
                 + arr[itr+max_width])/4;
        if (itr/max_width != (itr+2)/max_width)
        {
            itr+= 3;
            continue;
        }
        itr+=2;
    }
    std::fill(arr, arr+max_width, 0); //first row
    std::fill(arr+totalPix-max_width, arr+totalPix, 0); //last row
}
