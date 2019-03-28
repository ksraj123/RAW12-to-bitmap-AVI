//#include "Bitmap.h"
#include "headers/BMP_HEAD.h"

    using namespace OutputImage::bitmap;

    namespace OutputImage::bitmap{

    void write_bitmap(uint8_t arr_r[max_height+1][max_width+1],
                      uint8_t arr_b[max_height+1][max_width+1],
                      uint8_t arr_g[max_height+1][max_width+1])
    {

        BitmapFileHeader flleHeader;
        BitmapInfoHeader infoHeader;

        flleHeader.fileSize = sizeof(BitmapFileHeader)
                            + sizeof(BitmapInfoHeader)
                            + max_width * max_height * 3;

        flleHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

        std::ofstream file;
        file.open("result/BMP_output.bmp", std::ios::binary);
        if(!file){
            std::cout << "Error: Unable to open file\n";
        }

        file.write((char*)&flleHeader, sizeof(flleHeader));
        file.write((char*)&infoHeader, sizeof(infoHeader));

        for (int i = max_height; i >= 1; i--){
            for (int j = 1; j <= max_width; j++){
                file.write((char*)&arr_b[i][j], sizeof(uint8_t));
                file.write((char*)&arr_g[i][j], sizeof(uint8_t));
                file.write((char*)&arr_r[i][j], sizeof(uint8_t));
            }
        }

        file.close();
        if (!file){
            std::cout << "Error file cannot be closed" << std::endl;
        }
    }
}
//}
