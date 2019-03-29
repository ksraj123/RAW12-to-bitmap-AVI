#include "headers/Raw12Img.h"

channels chnl;

streams strm;

Raw12Img::Raw12Img(std::string INPUT_FILE){
    this->INPUT_FILE = INPUT_FILE;
}

void Raw12Img::load(){
    strm.intputfile.open(INPUT_FILE.c_str(), std::ios::binary);
    if(!strm.intputfile){
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }

    int total_row_bytes = (max_width * 3) / 2;

    for (int i = 1; i <= max_height; i++){
        int cnt = 1;
        for (int j = 1; j <= (total_row_bytes/3); j++){
            char inBuf [3];
            strm.intputfile.read(inBuf, 3);

            int r_g = ((uint8_t)inBuf[0]) << 4 |
                      ((uint8_t)inBuf[1] & 0xF0) >> 4;
            int g_b = ((uint8_t)inBuf[1] & 0x0F) << 8 |
                      ((uint8_t)inBuf[2]);

            r_g = (r_g & 0xFF0) >> 4;
            g_b = (g_b & 0xFF0) >> 4;
            chnl.CFA[i][cnt] = r_g;
            chnl.CFA[i][cnt+1] = g_b;
            cnt += 2;
        }
    }
	strm.intputfile.close();
}


void Raw12Img::initialize_channels(){
    for (int i = 1; i <= max_height; i+=2)
        for (int j = 1; j<=max_width; j+=2)
            chnl.red[i][j] = chnl.CFA[i][j];

    for (int i = 2; i <= max_height; i+=2)
        for (int j = 2; j<=max_width; j+=2)
            chnl.blue[i][j] = chnl.CFA[i][j];

    for (int i = 1; i <= max_height; i++){
        if (i %2 != 0)
           for (int j = 2; j<=max_width; j+=2)
               chnl.green[i][j] = chnl.CFA[i][j];
        else
           for (int j = 1; j<=max_width; j+=2)
               chnl.green[i][j] = chnl.CFA[i][j];
    }
}


void Raw12Img::debayer_channels(){
    Demosaic::red(chnl.red);
    Demosaic::green(chnl.green);
    Demosaic::blue(chnl.blue);
}

void Raw12Img::write_channels(){
    OutputImage::pixelmap::write_channel(&strm.output_red, chnl.red, "red");
    OutputImage::pixelmap::write_channel(&strm.output_green, chnl.green, "green");
    OutputImage::pixelmap::write_channel(&strm.output_blue, chnl.blue, "blue");
}

void Raw12Img::write_debayered_image(){
    OutputImage::bitmap::write_bitmap(chnl.red, chnl.blue, chnl.green);
    write_to_avi(chnl.red, chnl.blue, chnl.green);
}
