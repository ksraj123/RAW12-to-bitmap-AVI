#include "headers/Output.h"

// Constructor - calls GetPpmChannel() and GetBmpImage() to initialize binary channels
OutputImage::OutputImage(InputImage* input)
               : ppmRedChnl(GetPpmChannel(input->GetRedChannel(), "red")),
                 ppmGreenChnl(GetPpmChannel(input->GetGreenChannel(), "green")),
                 ppmBlueChnl(GetPpmChannel(input->GetBlueChannel(), "blue"))
{
    bmpImage = GetBmpImage(input->GetRedChannel(), 
                           input->GetBlueChannel(), 
                           input->GetGreenChannel());
}

// WritePpm() writes Binary PPM files (Red, Blue and Green)
void OutputImage::WritePpm(std::string chanelName)
{
    std::string outputFileName = "result/" + chanelName + ".ppm";
    outputFile.open(outputFileName, std::ios::out | std::ios::trunc);
    if(!outputFile)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting\n";
        exit(1);
    }
    outputFile << "P6\n" << "# " << chanelName << ".ppm\n" << IMAGE_WIDTH
               << " " << IMAGE_HEIGHT << "\n" << "255" << "\n";

    uint8_t* ppmBin = nullptr;
    switch (chanelName[0])
        {
            case 'r':
                ppmBin = ppmRedChnl;
                break;
            case 'g':
                ppmBin = ppmGreenChnl;
                break;
            case 'b':
                ppmBin = ppmBlueChnl;
                break;
        }
    // Entire Image written at once for enhanced performace
    outputFile.write(reinterpret_cast<const char*> (ppmBin), TOTAL_PIX * 3);
    delete ppmBin;
    outputFile.close();
}

// WriteBmp writes binary Bmp file
void OutputImage::WriteBmp()
{
    flleHeader.fileSize = sizeof(BitmapFileHeader)
                        + sizeof(BitmapInfoHeader) + TOTAL_PIX * 3;
    flleHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    outputFile.open("result/BMP_output.bmp", std::ios::binary);
    if(!outputFile)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting\n";
        exit(1);
    }
    outputFile.write(reinterpret_cast<const char*>(&flleHeader), sizeof(flleHeader));
    outputFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    // Entire Image written at once for enhanced performace
    outputFile.write(reinterpret_cast<const char*>(bmpImage), 3 * TOTAL_PIX);
    outputFile.close();
    if (!outputFile)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting\n";
        exit(1);
    }
}

// WriteToAVI() wirtes the Image into single frame AVI
void OutputImage::WriteToAvi()
{
    outputFile.open("result/AVI_output.avi", std::ios::binary);
    if(!outputFile)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting\n";
        exit(1);
    }
    uint32_t size_pix = TOTAL_PIX * 3;
    uint32_t size_rec = 3 * 4 + size_pix;
    uint32_t size_movi = 3 * 4 + size_rec;
    uint32_t size_strl = 3 * 4 + sizeof(streamHeader) + 2 * 4 + sizeof(streamFormat);
    uint32_t size_hrdl =  3 * 4 + sizeof(mainHeader) + 2 * 4 + size_strl;
    uint32_t size_riff = 3 + 2 * 4 + size_hrdl + 2 * 4 + size_movi;

    outputFile.write("RIFF", 4);
    outputFile.write(reinterpret_cast<const char*>(&size_riff), 4);
    outputFile.write("AVI ", 4);

    outputFile.write("LIST", 4);
    outputFile.write(reinterpret_cast<const char*>(&size_hrdl), 4);
    outputFile.write("hdrl", 4);

    outputFile.write("avih", 4);
    uint32_t size_mainaviheader = sizeof(mainHeader);
    outputFile.write(reinterpret_cast<const char*>(&size_mainaviheader), 4);
    outputFile.write(reinterpret_cast<const char*>(&mainHeader), sizeof(mainHeader));

    outputFile.write("LIST", 4);
    outputFile.write(reinterpret_cast<const char*>(&size_strl), 4);
    outputFile.write("strl", 4);

    outputFile.write("strh", 4);
    int temp = sizeof(streamHeader);
    outputFile.write(reinterpret_cast<const char*>(&temp), 4);
    outputFile.write(reinterpret_cast<const char*>(&streamHeader), sizeof(streamHeader));

    outputFile.write("strf", 4);
    temp = sizeof(streamFormat);
    outputFile.write(reinterpret_cast<const char*>(&temp), 4);
    outputFile.write(reinterpret_cast<const char*>(&streamFormat), sizeof(streamFormat));

    outputFile.write("LIST", 4);
    outputFile.write(reinterpret_cast<const char*>(&size_movi), 4);
    outputFile.write("movi", 4);

    outputFile.write("LIST", 4);
    outputFile.write(reinterpret_cast<const char*>(&size_rec), 4);
    outputFile.write("rec ", 4);

    outputFile.write("00db", 4); //uncompressed video frame
    outputFile.write(reinterpret_cast<const char*>(&size_pix), 4);
    // Entire Image written at once for enhanced performace
    outputFile.write(reinterpret_cast<const char*>(bmpImage), 3*TOTAL_PIX);

    outputFile.close();
    if (!outputFile)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting\n";
        exit(1);
    }
}

// GetPpmChannel() adds zeros in place of intensity values of other 
// channels so that a single colour channel can be written directly
// Returns pointer to image to be written in P6 PPM
uint8_t* OutputImage::GetPpmChannel(uint8_t* channel, std::string chanelName)
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

// Returns pointer to Inverted Image to writeen into Bitmap and AVI
uint8_t* OutputImage::GetBmpImage(uint8_t* channelRed, uint8_t* channelBlue, 
                                  uint8_t* channelGreen)
{
    uint8_t* bmpBin = new uint8_t [TOTAL_PIX * 3];
    for (int row = IMAGE_HEIGHT - 1, itr = 0; row >= 0; --row)
    {
        for (int col = row * IMAGE_WIDTH; col < (row + 1) * IMAGE_WIDTH; ++col)
        {
            bmpBin[itr] = channelBlue[col];
            bmpBin[itr + 1] = channelGreen[col];
            bmpBin[itr + 2] = channelRed[col];
            itr += 3;
        }
    }
    return bmpBin;
}

OutputImage::~OutputImage()
{
    delete bmpImage;
    delete ppmRedChnl;
    delete ppmGreenChnl;
    delete ppmBlueChnl;
}