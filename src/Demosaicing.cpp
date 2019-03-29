#include "headers/Demosaicing.h"

void Demosaic::Green(uint8_t c_g[max_height+1][max_width+1])
{
    //dealing with pixels surrounded by green pixels on all 4 sides
    for (int row = 2; row <= max_height-1; row++)
        {
        if (row % 2 == 0)
            for (int col = 2; col <= max_width-2; col+=2)
                c_g[row][col] = (c_g[row][col+1] + c_g[row][col-1]
                               + c_g[row+1][col] + c_g[row-1][col])/4;
        else
            for (int col = 3; col <= max_width-1; col++)
                c_g[row][col] = (c_g[row][col+1] + c_g[row][col-1]
                               + c_g[row+1][col] + c_g[row-1][col])/4;
        }

    // dealing with pixels in top row
    for (int col = 3; col<=max_width-1; col+=2)
         c_g[1][col] = (c_g[1][col-1] + c_g[1][col+1])/2;

    // dealing with pixels in bottom row
    for (int col = 2; col<=max_width-2; col+=2)
         c_g[max_height][col] = (c_g[max_height][col-1]
                               + c_g[max_height][col+1])/2;

    // dealing with pixels in leftmost column
    for (int row = 3; row<=max_height-1; row+=2)
         c_g[row][1] = (c_g[row-1][1] + c_g[row+1][1])/2;

    // dealing with pixels in rightmost column
    for (int row = 2; row<=max_height-2; row+=2)
         c_g[row][max_width] = (c_g[row-1][max_width]
                              + c_g[row+1][max_width])/2;


    c_g[1][1] = (c_g[1][2] + c_g[2][1])/2;
    c_g[max_height][max_width] = (c_g[max_height-1][max_width]
                                + c_g[max_height][max_width-1])/2;
}

void Demosaic::blue(uint8_t c_b[max_height+1][max_width+1])
{
    for (int i = 2; i <= max_height; i+=2)
        for (int j = 3; j<=max_width-1; j+=2)
            c_b[i][j] = (c_b[i][j-1] + c_b[i][j+1])/2;

    for (int i = 2; i <= max_width; i++)
        for (int j = 3; j<=max_height-1; j+=2)
            c_b[j][i] = (c_b[j-1][i] + c_b[j+1][i])/2;

    for (int i = 2; i <=max_height; i++)
        c_b[i][1] = c_b[i][2];

    for (int i = 2; i <=max_width; i++)
        c_b[1][i] = c_b[2][i];

    c_b[1][1] = (c_b[1][2] + c_b[2][1])/2;
}

void Demosaic::red(uint8_t c_r[max_height+1][max_width+1])
{
    for (int i = 1; i <= max_height-1; i+= 2)
        for (int j = 2; j<= max_width-2; j+= 2)
            c_r[i][j] = (c_r[i][j-1] + c_r[i][j+1])/2;

    for (int i = 1; i <= max_width-1; i++)
        for (int j = 2; j<=max_height-2; j+=2)
            c_r[j][i] = (c_r[j-1][i] + c_r[j+1][i])/2;

    for (int i = 1; i <=max_height; i++)
        c_r[i][max_width] = c_r[i][max_width-1];

    for (int i = 1; i <=max_width; i++)
        c_r[max_height][i] = c_r[max_height-1][i];
}
