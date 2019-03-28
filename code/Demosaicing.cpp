#include "headers/Demosaicing.h"

void Demosaic::green(uint8_t c_g[max_height+1][max_width+1]){

    for (int i = 2; i <= max_height-1; i++){
        if (i % 2 == 0)
        for (int j = 2; j <= max_width-2; j+=2){
                c_g[i][j] = (c_g[i][j+1] + c_g[i][j-1] + c_g[i+1][j] + c_g[i-1][j])/4;
        }
        else
        for (int j = 3; j <= max_width-1; j++){
            c_g[i][j] = (c_g[i][j+1] + c_g[i][j-1] + c_g[i+1][j] + c_g[i-1][j])/4;
        }
    }

    for (int i = 3; i<=max_width-1; i+=2){ // deals with pixels in top row
        c_g[1][i] = (c_g[1][i-1] + c_g[1][i+1])/2;
    }

    for (int i = 2; i<=max_width-2; i+=2){ // deals with pixels in bottom row
        c_g[max_height][i] = (c_g[max_height][i-1] + c_g[max_height][i+1])/2;
    }

    for (int i = 3; i<=max_height-1; i+=2){ // deals with pixels in leftmost column
        c_g[i][1] = (c_g[i-1][1] + c_g[i+1][1])/2;
    }

    for (int i = 2; i<=max_height-2; i+=2){ // deals with pixels in rightmost column
        c_g[i][max_width] = (c_g[i-1][max_width] + c_g[i+1][max_width])/2;
    }


    c_g[1][1] = (c_g[1][2] + c_g[2][1])/2;
    c_g[max_height][max_width] = (c_g[max_height-1][max_width] + c_g[max_height][max_width-1])/2;

    std::cout << "green channel debayered\n";
}

void Demosaic::blue(uint8_t c_b[max_height+1][max_width+1]){

    for (int i = 2; i <= max_height; i+=2){
        for (int j = 3; j<=max_width-1; j+=2){
            c_b[i][j] = (c_b[i][j-1] + c_b[i][j+1])/2;
        }
    }

    for (int i = 2; i <= max_width; i++){
        for (int j = 3; j<=max_height-1; j+=2){
            c_b[j][i] = (c_b[j-1][i] + c_b[j+1][i])/2;
        }
    }

    for (int i = 2; i <=max_height; i++){
        c_b[i][1] = c_b[i][2];
    }

    for (int i = 2; i <=max_width; i++){
        c_b[1][i] = c_b[2][i];
    }

    c_b[1][1] = (c_b[1][2] + c_b[2][1])/2;

    std::cout << "blue channel debayered\n";
}

void Demosaic::red(uint8_t c_r[max_height+1][max_width+1]){

    for (int i = 1; i <= max_height-1; i+= 2){
        for (int j = 2; j<= max_width-2; j+= 2){
            c_r[i][j] = (c_r[i][j-1] + c_r[i][j+1])/2;
        }
    }

    for (int i = 1; i <= max_width-1; i++){
        for (int j = 2; j<=max_height-2; j+=2){
            c_r[j][i] = (c_r[j-1][i] + c_r[j+1][i])/2;
        }
    }

    for (int i = 1; i <=max_height; i++){
        c_r[i][max_width] = c_r[i][max_width-1];
    }

    for (int i = 1; i <=max_width; i++){
        c_r[max_height][i] = c_r[max_height-1][i];
    }

    std::cout << "red channel debayered\n";
}
