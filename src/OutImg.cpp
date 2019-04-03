#include "headers/OutImg.h"

void WritePpm(uint8_t* arr, std::string chanel_name)
{
    std::string output_file_name = "result/" + chanel_name + ".ppm";
    std::ofstream channel;
    channel.open(output_file_name.c_str(), std::ios::out | std::ios::trunc);
    if(!channel)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting\n";
        exit(1);
    }
    channel << "P3\n" << "# " << chanel_name << ".ppm\n" << max_width
            << " " << max_height << "\n" << "255" << "\n";
    for (int itr = 0; itr < totalPix; itr++)
    {
        switch(chanel_name[0])
        {
            // elements of the array get written to file as characters without casting
            case 'r':
                channel << static_cast<int>(arr[itr]) << " 0 0";
                break;
            case 'g':
                channel << "0 " << static_cast<int>(arr[itr]) << " 0";
                break;
            case 'b':
                channel << "0 0 " << static_cast<int>(arr[itr]);
                break;
        }
        if ((itr + 1) % max_width == 0)
            channel << "\n";
        else
            channel << " ";
    }
    channel.close();
}

void WriteBmp(uint8_t* arr_r, uint8_t* arr_b, uint8_t* arr_g)
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

    file.write(reinterpret_cast<const char*>(&flleHeader), sizeof(flleHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
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
