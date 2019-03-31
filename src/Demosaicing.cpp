#include "headers/Demosaicing.h"

// following Bilinear Interpolation approach

void Demosaic::Green(unsigned char* arr)
 {
     for (int itr = 0; itr < totalPix; itr++)
     {
         if (arr[itr] == 0)
         {
             if (itr < max_width || totalPix-1-itr < max_width) // first and last row
                 arr[itr] = (arr[itr-1] + arr[itr+1])/2;
             else if (itr % max_width == 0 || itr+1 % max_width == 0) // first and last colm
                 arr[itr] = (arr[itr-max_width] + arr[itr+max_width])/2;
             else
                 arr[itr] = (arr[itr-1] + arr[itr+1] + arr[itr-max_width]
                           + arr[itr+max_width])/4;
         }
     }
 }

void Demosaic::Blue(unsigned char* arr)
 {
     int row;
     for (int itr = max_width; itr < totalPix; itr++)
     {
         row = itr / max_width;
         if ((int)arr[itr] == 0)
         {
             if (row % 2 != 0)
                 arr[itr] = (arr[itr-1] + arr[itr+1])/2;
             else
                 arr[itr] = (arr[itr-max_width] + arr[itr+max_width])/2;
         }
     }
     for (int itr = 0; itr < max_width; itr++) //first row
         arr[itr] = arr[itr + max_width];
 
     for (int itr = 0; itr < totalPix; itr += max_width) //first column
         arr[itr] = arr[itr+1];
 }

void Demosaic::Red(unsigned char* arr)
 {
     int row;
     for (int itr = 0; itr < totalPix-max_width; itr++)
     {
         row = itr / max_width;
         if ((int)arr[itr] == 0)
         {
             if (row % 2 == 0)
                 arr[itr] = (arr[itr-1] + arr[itr+1])/2;
             else
                 arr[itr] = (arr[itr-max_width] + arr[itr+max_width])/2;
         }
     }
     for (int itr = 1; itr <= max_width; itr++) //last row
         arr[totalPix - itr] = arr[totalPix - itr - max_width];
 
     for (int itr = max_width-1; itr < totalPix; itr += max_width) //last column
         arr[itr] = arr[itr-1];
 }
