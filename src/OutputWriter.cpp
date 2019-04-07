#include "headers/OutputWriter.h"

void OutputWriter::Print5by5tile(uint8_t* array)
{
    for (int row = 0; row < 5; ++row)
    {
        for (int index = 0; index < 5; ++index)
        {
            std::cout << (int)array[row * IMAGE_WIDTH + index] << " ";
        }
        std::cout << std::endl;
    }
}


void OutputWriter::WritePpm(std::string chanelName, ImageProcessor* debayeredImg)
{
    std::string outputFileName = "result/" + chanelName + ".ppm";

    std::ofstream outputPPM;
    outputPPM.open(outputFileName, std::ios::out | std::ios::trunc);
    if(!outputPPM)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting" << std::endl;
        exit(1);
    }

    outputPPM << "P6\n" << "# " << chanelName << ".ppm\n" << IMAGE_WIDTH
               << " " << IMAGE_HEIGHT << "\n" << "255" << "\n";

    uint8_t* ppmBin = nullptr;
    switch (chanelName[0])
        {
            case 'r':
                ppmBin = ConvertToPPM(debayeredImg->redChannel, "red");;
                break;
            case 'g':
                ppmBin = ConvertToPPM(debayeredImg->greenChannel, "green");
                break;
            case 'b':
                ppmBin = ConvertToPPM(debayeredImg->blueChannel, "blue");
                break;
        }
    outputPPM.write(reinterpret_cast<const char*> (ppmBin), TOTAL_PIX * 3);

    outputPPM.close();
    if (!outputPPM)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting" << std::endl;
        exit(1);
    }
}


void OutputWriter::WriteBmp(ImageProcessor* debayeredImg)
{
    BitmapFileHeader flleHeader;
    BitmapInfoHeader infoHeader;

    flleHeader.fileSize   = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) 
                            + TOTAL_PIX * 3;
    flleHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    std::ofstream outputBMP;
    outputBMP.open("result/BMP_output.bmp", std::ios::binary);
    if(!outputBMP)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting" << std::endl;
        exit(1);
    }

    outputBMP.write(reinterpret_cast<const char*>(&flleHeader), sizeof(flleHeader));
    outputBMP.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    bmpImage = ConvertToBMP(debayeredImg->redChannel, debayeredImg->blueChannel, 
                            debayeredImg->greenChannel);
    outputBMP.write(reinterpret_cast<const char*>(bmpImage), 3 * TOTAL_PIX);
    
    outputBMP.close();
    if (!outputBMP)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting" << std::endl;
        exit(1);
    }
}


Chunk::Chunk(std::string str, uint32_t size, Avi* avi)
{
    strncpy(_fourCC, str.c_str(), 4);
    _size = size;
    _avi = avi;
}


void Chunk::WriteToFile(std::ofstream* outputAVI)
{
    outputAVI->write(reinterpret_cast<const char*>(_fourCC), 4);
    outputAVI->write(reinterpret_cast<const char*>(&_size), 4);
    if (_avi == nullptr)
    {
        _size = 0;
    }
    outputAVI->write(reinterpret_cast<const char*>(_avi), _size);
}


void OutputWriter::WriteAvi()
{
    std::ofstream outputAVI;
    outputAVI.open("result/AVI_output.avi", std::ios::binary);
    if(!outputAVI)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting" << std::endl;
        exit(1);
    }

    MainAVIHeader mainHeader;
    AVIStreamHeader streamHeader;
    AVIStreamFormat streamFormat;

    uint32_t size_pix  = TOTAL_PIX * 3;
    uint32_t size_rec  = 3 * 4 + size_pix;
    uint32_t size_movi = 3 * 4 + size_rec;
    uint32_t size_strl = 3 * 4 + sizeof(streamHeader) + 2 * 4 + sizeof(streamFormat);
    uint32_t size_hrdl = 3 * 4 + sizeof(mainHeader) + 2 * 4 + size_strl;
    uint32_t size_riff = 3 + 2 * 4 + size_hrdl + 2 * 4 + size_movi;

    Chunk riff ("RIFF", size_riff);
    riff.WriteToFile(&outputAVI);

    outputAVI.write("AVI ", 4);

    Chunk listHdrl ("LIST", size_hrdl);
    listHdrl.WriteToFile(&outputAVI);

    outputAVI.write("hdrl", 4);

    Chunk avih ("avih", sizeof(mainHeader), &mainHeader);
    avih.WriteToFile(&outputAVI);

    Chunk listStrl ("LIST", size_strl);
    listStrl.WriteToFile(&outputAVI);

    outputAVI.write("strl", 4);

    Chunk strh ("strh", sizeof(streamHeader), &streamHeader);
    strh.WriteToFile(&outputAVI);

    Chunk strf ("strf", sizeof(streamFormat), &streamFormat);
    strf.WriteToFile(&outputAVI);

    Chunk listMovi ("LIST", size_movi);
    listMovi.WriteToFile(&outputAVI);

    outputAVI.write("movi", 4);

    Chunk listRec ("LIST", size_rec);
    listRec.WriteToFile(&outputAVI);

    outputAVI.write("rec ", 4);

    Chunk imgSubChnk ("00db", size_pix);
    imgSubChnk.WriteToFile(&outputAVI);

    // Entire Image written at once for enhanced performace
    outputAVI.write(reinterpret_cast<const char*>(bmpImage), 3*TOTAL_PIX);

    outputAVI.close();
    if (!outputAVI)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting" << std::endl;
        exit(1);
    }
}


uint8_t* OutputWriter::ConvertToPPM(uint8_t* channel, std::string chanelName)
{
    uint8_t* ppmBin = new uint8_t[3 * TOTAL_PIX]{0};
    for (int itrPpmBin = 0, itrChnl = 0; itrPpmBin < 3 * TOTAL_PIX, 
                            itrChnl < TOTAL_PIX; itrPpmBin += 3, ++itrChnl)
    {
        switch (chanelName[0])
        {
            case 'r':
                ppmBin[itrPpmBin] = channel[itrChnl];
                break;
            case 'g':
                ppmBin[itrPpmBin + 1] = channel[itrChnl];
                break;
            case 'b':
                ppmBin[itrPpmBin + 2] = channel[itrChnl];
                break;
        }      
    }
    return ppmBin;
}


uint8_t* OutputWriter::ConvertToBMP(uint8_t* channelRed, uint8_t* channelBlue, 
                                  uint8_t* channelGreen)
{
    uint8_t* bmpBin = new uint8_t [TOTAL_PIX * 3];
    for (int row = IMAGE_HEIGHT - 1, itr = 0; row >= 0; --row)
    {
        for (int col = row * IMAGE_WIDTH; col < (row + 1) * IMAGE_WIDTH; ++col)
        {
            bmpBin[itr]     = channelBlue[col];
            bmpBin[itr + 1] = channelGreen[col];
            bmpBin[itr + 2] = channelRed[col];
            itr += 3;
        }
    }
    return bmpBin;
}