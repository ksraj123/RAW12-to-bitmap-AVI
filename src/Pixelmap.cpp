#include "headers/PPM_HEAD.h"

namespace OutputImage::PixelMap
{
    void Write(std::ofstream* channel, unsigned char* arr, std::string chanel_name)
    {
        std::string output_file_name = "result/" + chanel_name + ".ppm";
        channel->open(output_file_name.c_str(), std::ios::out | std::ios::trunc);
        if(!channel)
        {
            std::cerr << "Error: File cannot be opened\n\tExiting\n";
            exit(1);
        }
        *channel << "P3\n" << "# " << chanel_name << ".ppm\n" << max_width
                 << " " << max_height << "\n" << "255" << "\n";
        for (int itr = 0; itr < totalPix; itr++)
        {
            switch(chanel_name[0])
            {
                case 'r':
                    *channel << (int)arr[itr] << " 0 0";
                    break;
                case 'g':
                    *channel << "0 " << (int)arr[itr] << " 0";
                    break;
                case 'b':
                    *channel << "0 0 " << (int)arr[itr];
                    break;
            }
            if ((itr + 1) % max_width == 0)
                *channel << "\n";
            else
                *channel << " ";
        }
        channel->close();
    }
}
