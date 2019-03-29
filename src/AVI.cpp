#include "headers/AVI.h"

//Chunk RIFF;

int write_to_avi(uint8_t arr_r[max_height+1][max_width+1],
                 uint8_t arr_b[max_height+1][max_width+1],
                 uint8_t arr_g[max_height+1][max_width+1])
{

        MainAVIHeader MainHeader;
        AVIStreamHeader StreamHeader;
        AVIStreamFormat StreamFormat;

        std::ofstream file;
        file.open("result/AVI_output.avi", std::ios::binary);
        if(!file){
            std::cerr << "Error: File cannot be opened\n\tExiting\n";
            exit(1);
        }
        char ch[4];
        ch[0] = 'R'; ch[1] = 'I'; ch[2] = 'F'; ch[3] = 'F';
        file.write(ch, 4);

        uint32_t size_riff = 3 + 4 + 4 + 4 + 4 + 4 + sizeof(MainHeader)
                        + 4 + 4 + 4 + 4 + 4 + sizeof(StreamHeader)
                        + 4 + 4 + sizeof(StreamFormat) + 4 + 4 + 4
                        + 4 + 4 + max_width * max_height * 3;
        file.write((char*)&size_riff, 4);

        ch[0] = 'A'; ch[1] = 'V'; ch[2] = 'I'; ch[3] = 0;
        file.write(ch, 4);

        ch[0] = 'L'; ch[1] = 'I'; ch[2] = 'S'; ch[3] = 'T';
        file.write(ch, 4);

        uint32_t size_hrdl =  4 + 4 + sizeof(MainHeader)
                        + 4 + 4 + 4 + 4 + 4 + sizeof(StreamHeader)
                        + 4 + 4 + sizeof(StreamFormat);

        file.write((char*)&size_hrdl, 4);

        ch[0] = 'h'; ch[1] = 'd'; ch[2] = 'r'; ch[3] = 'l';
        file.write(ch, 4);

        ch[0] = 'a'; ch[1] = 'v'; ch[2] = 'i'; ch[3] = 'h';
        file.write(ch, 4);

        uint32_t size_mainaviheader = sizeof(MainHeader);
        file.write((char*)&size_mainaviheader, 4);

        file.write((char*)&MainHeader, sizeof(MainHeader));

        ch[0] = 'L'; ch[1] = 'I'; ch[2] = 'S'; ch[3] = 'T';
        file.write(ch, 4);

        uint32_t size_strl = 4 + 4 + sizeof(StreamHeader)
                        + 4 + 4 + sizeof(StreamFormat);

        file.write((char*)&size_strl, 4);

        ch[0] = 's'; ch[1] = 't'; ch[2] = 'r'; ch[3] = 'l';
        file.write(ch, 4);

        ch[0] = 's'; ch[1] = 't'; ch[2] = 'r'; ch[3] = 'h';
        file.write(ch, 4);

        int temp = sizeof(StreamHeader);
        file.write((char*)&(temp), 4);

        file.write((char*)&StreamHeader, sizeof(StreamHeader));


        ch[0] = 's'; ch[1] = 't'; ch[2] = 'r'; ch[3] = 'f';
        file.write((char*)ch, 4);

        temp = sizeof(StreamFormat);
        file.write((char*)&(temp), 4);

        file.write((char*)&StreamFormat, sizeof(StreamFormat));

        ch[0] = 'L'; ch[1] = 'I'; ch[2] = 'S'; ch[3] = 'T';
        file.write(ch, 4);

        uint32_t size_movi = 4 + 4 + 4 + max_width * max_height * 3;

        file.write((char*)&size_movi, 4);

        ch[0] = 'm'; ch[1] = 'o'; ch[2] = 'v'; ch[3] = 'i';
        file.write(ch, 4);

        uint32_t size_00db = 4 + 4 + max_width * max_height * 3;

        ch[0] = '0'; ch[1] = '0'; ch[2] = 'd'; ch[3] = 'b';
        file.write(ch, 4);

        uint32_t size_pix = max_width * max_height * 3;

        for (int i = max_height; i >= 1; i--){
            for (int j = 1; j <= max_width; j++){
                file.write((char*)&arr_b[i][j], sizeof(uint8_t));
                file.write((char*)&arr_g[i][j], sizeof(uint8_t));
                file.write((char*)&arr_r[i][j], sizeof(uint8_t));
            }
        }

        file.close();
        if (!file){
            std::cerr << "Error: File cannot be Closed\n\tExiting\n";
            exit(1);
        }

}
