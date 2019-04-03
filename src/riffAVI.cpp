#include "headers/riffAVI.h"

void WriteToAvi(uint8_t* arr_r, uint8_t* arr_b, uint8_t* arr_g)
{
    MainAVIHeader MainHeader;
    AVIStreamHeader StreamHeader;
    AVIStreamFormat StreamFormat;

    std::ofstream file;
    file.open("result/AVI_output.avi", std::ios::binary);
    if(!file)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting\n";
        exit(1);
    }

    uint32_t size_pix = max_width * max_height * 3;
    uint32_t size_rec = 3*4 + size_pix;
    uint32_t size_movi = 3*4 + size_rec;
    uint32_t size_strl = 3*4 + sizeof(StreamHeader) + 2*4 + sizeof(StreamFormat);
    uint32_t size_hrdl =  3*4 + sizeof(MainHeader) + 2*4 + size_strl;
    uint32_t size_riff = 3 + 2*4 + size_hrdl + 2*4 + size_movi;

    file.write("RIFF", 4);
    file.write(reinterpret_cast<const char*>(&size_riff), 4);
    file.write("AVI ", 4);

    file.write("LIST", 4);
    file.write(reinterpret_cast<const char*>(&size_hrdl), 4);
    file.write("hdrl", 4);

    file.write("avih", 4);
    uint32_t size_mainaviheader = sizeof(MainHeader);
    file.write(reinterpret_cast<const char*>(&size_mainaviheader), 4);
    file.write(reinterpret_cast<const char*>(&MainHeader), sizeof(MainHeader));

    file.write("LIST", 4);
    file.write(reinterpret_cast<const char*>(&size_strl), 4);
    file.write("strl", 4);

    file.write("strh", 4);
    int temp = sizeof(StreamHeader);
    file.write(reinterpret_cast<const char*>(&temp), 4);
    file.write(reinterpret_cast<const char*>(&StreamHeader), sizeof(StreamHeader));

    file.write("strf", 4);
    temp = sizeof(StreamFormat);
    file.write(reinterpret_cast<const char*>(&temp), 4);
    file.write(reinterpret_cast<const char*>(&StreamFormat), sizeof(StreamFormat));

    file.write("LIST", 4);
    file.write(reinterpret_cast<const char*>(&size_movi), 4);
    file.write("movi", 4);

    file.write("LIST", 4);
    file.write(reinterpret_cast<const char*>(&size_rec), 4);
    file.write("rec ", 4);

    file.write("00db", 4); //uncompressed video frame
    file.write(reinterpret_cast<const char*>(&size_pix), 4);
    for (int row = max_height-1; row >= 0; row--)
    {
        for (int col = row * max_width; col < (row+1)*max_width; col++)
        {
            file.write(reinterpret_cast<const char*>(&arr_b[col]), sizeof(uint8_t));
            file.write(reinterpret_cast<const char*>(&arr_g[col]), sizeof(uint8_t));
            file.write(reinterpret_cast<const char*>(&arr_r[col]), sizeof(uint8_t));
        }
    }

    file.close();
    if (!file)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting\n";
        exit(1);
    }
}
