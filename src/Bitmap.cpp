#include "headers/BMP_HEAD.h"

namespace OutputImage::bitmap
{
    void Write(uint8_t* arr_r, uint8_t* arr_b, uint8_t* arr_g)
    {
        BitmapFileHeader flleHeader;
        BitmapInfoHeader infoHeader;
        flleHeader.fileSize = sizeof(BitmapFileHeader)
                            + sizeof(BitmapInfoHeader)
                            + max_width * max_height * 3;
        flleHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
        std::ofstream file;
        file.open("result/BMP_output.bmp", std::ios::binary);
        if(!file)
        {
            std::cerr << "Error: File cannot be opened\n\tExiting\n";
            exit(1);
        }
        file.write((char*)&flleHeader, sizeof(flleHeader));
        file.write((char*)&infoHeader, sizeof(infoHeader));

        for (int row = max_height-1; row >= 0; row--)
        {
            for (int col = row * max_width; col < (row+1)*max_width; col++)
            {
                file.write((char*)&arr_b[col], sizeof(uint8_t));
                file.write((char*)&arr_g[col], sizeof(uint8_t));
                file.write((char*)&arr_r[col], sizeof(uint8_t));
            }
        }
        file.close();
        if (!file)
        {
            std::cerr << "Error: File cannot be Closed\n\tExiting\n";
            exit(1);
        }
    }
}
