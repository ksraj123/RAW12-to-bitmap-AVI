#include "headers/Output.h"

OutputImage::OutputImage(InputImage* input)
               : ppmBinRed(GetPpmBinary(input->GetRedChannel(), "red")),
                 ppmBinGreen(GetPpmBinary(input->GetGreenChannel(), "green")),
                 ppmBinBlue(GetPpmBinary(input->GetBlueChannel(), "blue"))
{
    bmpBinary = GetBmpBinary(input->GetRedChannel(), 
                             input->GetBlueChannel(), 
                             input->GetGreenChannel());
}

void OutputImage::WritePpm(std::string chanelName)
{
    std::string outputFileName = "result/" + chanelName + ".ppm";
    outputFile.open(outputFileName, std::ios::out | std::ios::trunc);
    if(!outputFile)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting\n";
        exit(1);
    }
    outputFile << "P6\n" << "# " << chanelName << ".ppm\n" << MAX_WIDTH
            << " " << MAX_HEIGHT << "\n" << "255" << "\n";

    uint8_t* ppmBin = nullptr;
    switch (chanelName[0])
        {
            case 'r':
                ppmBin = ppmBinRed;
                break;
            case 'g':
                ppmBin = ppmBinGreen;
                break;
            case 'b':
                ppmBin = ppmBinBlue;
                break;
        }
    // Entire Image written at once for enhanced performace
    outputFile.write(reinterpret_cast<const char*> (ppmBin), TOTAL_PIX*3);
    delete ppmBin;
    outputFile.close();
}

void OutputImage::WriteBmp()
{
    flleHeader.fileSize = sizeof(BitmapFileHeader)
                        + sizeof(BitmapInfoHeader)
                        + MAX_WIDTH * MAX_HEIGHT * 3;
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
    outputFile.write(reinterpret_cast<const char*>(bmpBinary), 3*TOTAL_PIX);
    outputFile.close();
    if (!outputFile)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting\n";
        exit(1);
    }
}

void OutputImage::WriteToAvi()
{
    outputFile.open("result/AVI_output.avi", std::ios::binary);
    if(!outputFile)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting\n";
        exit(1);
    }
    uint32_t size_pix = MAX_WIDTH * MAX_HEIGHT * 3;
    uint32_t size_rec = 3*4 + size_pix;
    uint32_t size_movi = 3*4 + size_rec;
    uint32_t size_strl = 3*4 + sizeof(streamHeader) + 2*4 + sizeof(streamFormat);
    uint32_t size_hrdl =  3*4 + sizeof(mainHeader) + 2*4 + size_strl;
    uint32_t size_riff = 3 + 2*4 + size_hrdl + 2*4 + size_movi;

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
    outputFile.write(reinterpret_cast<const char*>(bmpBinary), 3*TOTAL_PIX);

    outputFile.close();
    if (!outputFile)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting\n";
        exit(1);
    }
}

// Returns pointer to image to be written in P6 PPM
uint8_t* OutputImage::GetPpmBinary(uint8_t* arr, std::string chanelName)
{
    uint8_t* ppmBin = new uint8_t[3*TOTAL_PIX]{0};

    for (int itr_arr = 0, itr = 0; itr_arr < 3*TOTAL_PIX, itr < TOTAL_PIX; itr_arr += 3, ++itr)
    {
        switch (chanelName[0])
        {
            case 'r':
                ppmBin[itr_arr] = arr[itr];
                break;
            case 'g':
                ppmBin[itr_arr+1] = arr[itr];
                break;
            case 'b':
                ppmBin[itr_arr+2] = arr[itr];
                break;
        }      
    }
    return ppmBin;
}

// Returns pointer to Inverted Image to writeen into Bitmap and AVI
uint8_t* OutputImage::GetBmpBinary(uint8_t* arr_r, uint8_t* arr_b, uint8_t* arr_g)
{
    uint8_t* bmpBin = new uint8_t [TOTAL_PIX*3];
    for (int row = MAX_HEIGHT-1, itr = 0; row >= 0; --row)
    {
        for (int col = row * MAX_WIDTH; col < (row+1)*MAX_WIDTH; ++col)
        {
            bmpBin[itr] = arr_b[col];
            bmpBin[itr+1] = arr_g[col];
            bmpBin[itr+2] = arr_r[col];
            itr+=3;
        }
    }
    return bmpBin;
}


OutputImage::~OutputImage()
{
    delete bmpBinary;
    delete ppmBinRed;
    delete ppmBinGreen;
    delete ppmBinBlue;
}