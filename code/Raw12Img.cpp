#include "headers/Raw12Img.h"

void Raw12Img::load(){

    std::cout << "loading file\n";

    intputfile.open("test_image/test_image.raw12", std::ios::binary);
    if(!intputfile){
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }

    int total_row_bytes = (max_width * 3) / 2;

    for (int i = 1; i <= max_height; i++){
        int cnt = 1;
        for (int j = 1; j <= (total_row_bytes/3); j++){
            char inBuf [3];
            intputfile.read(inBuf, 3);
            int r_g = ((uint8_t)inBuf[0]) << 4 | ((uint8_t)inBuf[1] & 0xF0) >> 4;
            int g_b = ((uint8_t)inBuf[1] & 0x0F) << 8 | ((uint8_t)inBuf[2]);
            r_g = (r_g & 0xFF0) >> 4;
            g_b = (g_b & 0xFF0) >> 4;
            cfa[i][cnt] = r_g;
            cfa[i][cnt+1] = g_b;
            cnt += 2;
        }
    }
    std::cout << "image loaded\n";
    fflush(stdout);
	intputfile.close();
}


void Raw12Img::initialize_channels(){

    std::cout << "initializing channels\n";

    for (int i = 1; i <= max_height; i+=2){
        for (int j = 1; j<=max_width; j+=2){
            c_r[i][j] = cfa[i][j];
        }
    }

    for (int i = 2; i <= max_height; i+=2){
        for (int j = 2; j<=max_width; j+=2){
            c_b[i][j] = cfa[i][j];
        }
    }

    for (int i = 1; i <= max_height; i++){

        if (i %2 != 0){
        for (int j = 2; j<=max_width; j+=2)
            c_g[i][j] = cfa[i][j];}
        else{
        for (int j = 1; j<=max_width; j+=2)
            c_g[i][j] = cfa[i][j];}
    }
}


void Raw12Img::debayer_channels(){
    std::cout << "debayering channels\n";
    Demosaic::green(c_g);
    Demosaic::blue(c_b);
    Demosaic::red(c_r);
}


void Raw12Img::write_channels(){
    std::cout << "writing PPM r g b channels\n";
    OutputImage::pixelmap::write_channel(&output_red, c_r, "red");
    OutputImage::pixelmap::write_channel(&output_green, c_g, "green");
    OutputImage::pixelmap::write_channel(&output_blue, c_b, "blue");
}


void Raw12Img::write_debayered_image(){
    OutputImage::bitmap::write_bitmap(c_r, c_b, c_g);
}


void execution(){
std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!!///////\n";

Raw12Img InputImg;

std::cout << "Loading Raw12Image\n";
InputImg.load();

std::cout << "Initializing R G B channels\n";
InputImg.initialize_channels();

std::cout << "Debayering channels\n";
InputImg.debayer_channels();

std::cout << "Writing chaneels to results/ \n";
InputImg.write_channels();

std::cout << "Writing debayered BMP Image to results/ \n";
InputImg.write_debayered_image();

std::cout << "Please check results folder after sometime for output images\n";

std::cout << "!!!!Thank you for using my program!!!!";

std::cout << "main opened\n";
}
