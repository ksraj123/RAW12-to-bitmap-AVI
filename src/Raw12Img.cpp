#include "headers/Raw12Img.h"
#define Sensel(A, B) ((A & 0x0F) << 4 | (B & 0xF0) >> 4)

channels chnl;
streams strm;
char* file_data;

Raw12Img::Raw12Img(std::string file_name)
{
    this->file_name = file_name;
}

void Raw12Img::Load()
{
    strm.intputfile.open(file_name.c_str(), std::ios::binary);
    if(!strm.intputfile)
    {
        std::cerr << "Error: File cannot be opened\b\tExiting" << std::endl;
        exit(1);
    }
    file_data = new char [inputSize];
    strm.intputfile.read(file_data, inputSize);

    for (int itr = 0; itr < inputSize; itr+= 3)
    {
        uint8_t byte1 = file_data[itr];
        uint8_t byte2 = file_data[itr+1];
        uint8_t byte3 = file_data[itr+2];
        int row = (itr * 2) / (max_width * 3);

        if (row % 2 == 0)
        {
            chnl.Push(byte1, 0, 0);
            chnl.Push(0, Sensel(byte2, byte3), 0);
        }
        else
        {
            chnl.Push(0, byte1, 0);
            chnl.Push(0, 0, Sensel(byte2, byte3));
        }
    }
	strm.intputfile.close();
}

void Raw12Img::Debayer_channels()
{
    Demosaic::Red(chnl.red.data());
    Demosaic::Green(chnl.green.data());
    Demosaic::Blue(chnl.blue.data());
}

void Raw12Img::Write_channels()
{
    OutputImage::pixelmap::Write_channel(&strm.output_red, chnl.red.data(), "red");
    OutputImage::pixelmap::Write_channel(&strm.output_green, chnl.green.data(), "green");
    OutputImage::pixelmap::Write_channel(&strm.output_blue, chnl.blue.data(), "blue");
}

void Raw12Img::Write_debayered_image()
{
    OutputImage::bitmap::Write_bitmap(chnl.red.data(), chnl.blue.data(), chnl.green.data());
}
