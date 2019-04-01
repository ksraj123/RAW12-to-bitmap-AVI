#ifndef Raw12Img_H
#define Raw12Img_H

#include "functional.h"
#include "BMP_HEAD.h"
#include "PPM_HEAD.h"
#include "Demosaicing.h"
#define inputSize (4096 * 3072 * 3 / 2)
#define totalPix (4096 * 3072)

struct streams
 {
      std::ifstream intputfile;
      std::ofstream output_red, output_blue, output_green;
      std::ofstream file_output_ppm;
 };

struct channels
 {
      std::vector <unsigned char> red;
      std::vector <unsigned char> blue;
      std::vector <unsigned char> green;

      void Push(unsigned char r, unsigned char g, unsigned char b)
       {
            red.push_back(r);
            green.push_back(g);
            blue.push_back(b);
       }
 };

class Raw12Img
 {
      std::string file_name;

      public:
          Raw12Img (std::string);
          void Load();
          void Debayer_channels();
          void Write_channels();
          void Write_debayered_image();
 };

#endif
