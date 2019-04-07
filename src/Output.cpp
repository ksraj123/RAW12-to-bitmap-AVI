#include "headers/Output.h"

// Constructor - calls GetPpmChannel() and GetBmpImage() to initialize binary channels

std::ofstream OutputWriter::outputFile;

OutputWriter::OutputWriter()
{
    ppmRedChnl   = nullptr;
    ppmGreenChnl = nullptr;
    ppmBlueChnl  = nullptr;
    bmpImage     = nullptr;
}

OutputWriter::~OutputWriter()
{
    delete bmpImage;
    delete ppmRedChnl;
    delete ppmGreenChnl;
    delete ppmBlueChnl;
}

void OutputWriter::InitializeOutputChannels(Raw12Img* input)
{
    ppmRedChnl   = GetPpmChannel(input->redChannel, "red");
    ppmGreenChnl = GetPpmChannel(input->greenChannel, "green");
    ppmBlueChnl  = GetPpmChannel(input->blueChannel, "blue");
    bmpImage     = GetBmpImage(input->redChannel, 
                               input->blueChannel, 
                               input->greenChannel);
}

// WritePpm() writes Binary PPM files (Red, Blue and Green)
void OutputWriter::WritePpm(std::string chanelName)
{
    std::string outputFileName = "result/" + chanelName + ".ppm";

    outputFile.open(outputFileName, std::ios::out | std::ios::trunc);
    if(!outputFile)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting" << std::endl;
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
    outputFile.close();
    if (!outputFile)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting" << std::endl;
        exit(1);
    }
}

// WriteBmp writes binary Bmp file
void OutputWriter::WriteBmp()
{
    flleHeader.fileSize   = sizeof(BitmapFileHeader)
                          + sizeof(BitmapInfoHeader) + TOTAL_PIX * 3;
    flleHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    outputFile.open("result/BMP_output.bmp", std::ios::binary);
    if(!outputFile)
    {
        std::cerr << "Error: File cannot be opened\n\tExiting" << std::endl;
        exit(1);
    }
    outputFile.write(reinterpret_cast<const char*>(&flleHeader), sizeof(flleHeader));
    outputFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    // Entire Image written at once for enhanced performace
    outputFile.write(reinterpret_cast<const char*>(bmpImage), 3 * TOTAL_PIX);
    outputFile.close();
    if (!outputFile)
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

void Chunk::Write()
{
    OutputWriter::outputFile.write(reinterpret_cast<const char*>(_fourCC), 4);
    OutputWriter::outputFile.write(reinterpret_cast<const char*>(&_size), 4);
    if (_avi == nullptr)
    {
        _size = 0;
    }
    OutputWriter::outputFile.write(reinterpret_cast<const char*>(_avi), _size);
}


// WriteToAVI() wirtes the Image into single frame AVI
void OutputWriter::WriteToAvi()
{
    outputFile.open("result/AVI_output.avi", std::ios::binary);
    if(!outputFile)
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
    riff.Write();

    outputFile.write("AVI ", 4);


    Chunk listHdrl ("LIST", size_hrdl);
    listHdrl.Write();

    outputFile.write("hdrl", 4);


    Chunk avih ("avih", sizeof(mainHeader), &mainHeader);
    avih.Write();

    Chunk listStrl ("LIST", size_strl);
    listStrl.Write();

    outputFile.write("strl", 4);

    Chunk strh ("strh", sizeof(streamHeader), &streamHeader);
    strh.Write();

    Chunk strf ("strf", sizeof(streamFormat), &streamFormat);
    strf.Write();

    Chunk listMovi ("LIST", size_movi);
    listMovi.Write();

    outputFile.write("movi", 4);

    Chunk listRec ("LIST", size_rec);
    listRec.Write();

    outputFile.write("rec ", 4);

    Chunk imgSubChnk ("00db", size_pix);
    imgSubChnk.Write();

    // Entire Image written at once for enhanced performace
    outputFile.write(reinterpret_cast<const char*>(bmpImage), 3*TOTAL_PIX);

    outputFile.close();
    if (!outputFile)
    {
        std::cerr << "Error: File cannot be Closed\n\tExiting" << std::endl;
        exit(1);
    }
}

// GetPpmChannel() adds zeros in place of intensity values of other 
// channels so that a single colour channel can be written directly
// Returns pointer to image to be written in P6 PPM
uint8_t* OutputWriter::GetPpmChannel(uint8_t* channel, std::string chanelName)
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
uint8_t* OutputWriter::GetBmpImage(uint8_t* channelRed, uint8_t* channelBlue, 
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