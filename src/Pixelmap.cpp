#include "headers/PPM_HEAD.h"

namespace OutputImage::pixelmap
{

void Write_channel(std::ofstream* channel, uint8_t arr[max_height+1][max_width+1], std::string chanel_name)
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

    for (int i = 1; i <= max_height; i++)
    {
        for (int j = 1; j<= max_width; j++)
        {

            switch(chanel_name[0])
            {

                case 'r':
                    *channel << (int)arr[i][j] << " 0 0";
                    break;
                case 'g':
                    *channel << "0 " << (int)arr[i][j] << " 0";
                    break;
                case 'b':
                    *channel << "0 0 " << (int)arr[i][j];
                    break;
            }

            if (j!=max_width)
                *channel << " ";
            else
                *channel << "\n";
        }
    }

channel->close();
}
}
