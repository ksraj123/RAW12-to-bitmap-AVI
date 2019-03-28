#ifndef Raw12Img_H
#define Raw12Img_H

#include "functional.h"
#include "BMP_HEAD.h"
#include "PPM_HEAD.h"
#include "Demosaicing.h"

std::ifstream intputfile;
std::ofstream output_red, output_blue, output_green;
std::ofstream file_output_ppm;


uint8_t cfa[max_height+1][max_width+1];
uint8_t c_r[max_height+1][max_width+1];
uint8_t c_b[max_height+1][max_width+1];
uint8_t c_g[max_height+1][max_width+1];


class Raw12Img{

public:
    void load();
    void initialize_channels();
    void debayer_channels();
    void write_channels();
    void write_debayered_image();

};

#endif
