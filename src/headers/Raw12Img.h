#ifndef Raw12Img_H
#define Raw12Img_H

#include "functional.h"
#include "BMP_HEAD.h"
#include "PPM_HEAD.h"
#include "Demosaicing.h"
#include "AVI.h"

struct streams{
std::ifstream intputfile;
std::ofstream output_red, output_blue, output_green;
std::ofstream file_output_ppm;
};

struct channels{
uint8_t CFA[max_height+1][max_width+1];
uint8_t red[max_height+1][max_width+1];
uint8_t blue[max_height+1][max_width+1];
uint8_t green[max_height+1][max_width+1];
};

class Raw12Img{
    std::string INPUT_FILE;
public:
    Raw12Img (std::string);
    void load();
    void initialize_channels();
    void debayer_channels();
    void write_channels();
    void write_debayered_image();

};

#endif
