#include "src/headers/ImageLoader.h"
#include "src/headers/ImageProcessor.h"
#include "src/headers/OutputWriter.h"

int main()
{
    std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!! ///////" << std::endl;

    std::cout << "Loading Raw12 Image" << std::endl;
    ImageLoader raw12Img("test_image/test_image.raw12");
    raw12Img.LoadImage();

    ImageProcessor debayer;
    debayer.SeperateChannels(raw12Img.cfa);

    std::cout << "Printing 5 by 5 tiles\n" << std::endl;
    std::cout << "CFA" << std::endl;
    OutputWriter::Print5by5tile(raw12Img.cfa);
    std::cout << "Red Channel before debayering" << std::endl;
    OutputWriter::Print5by5tile(debayer.redChannel);
    std::cout << "Green Channel before debayering" << std::endl;
    OutputWriter::Print5by5tile(debayer.greenChannel);
    std::cout << "Blue Channel before debayering" << std::endl;
    OutputWriter::Print5by5tile(debayer.blueChannel);

    std::cout << "Debayering channels" << std::endl;
    std::cout << "Debayering Red Channel" << std::endl;
    debayer.Red();
    std::cout << "Debayering Green Channel" << std::endl;
    debayer.Green();
    std::cout << "Debayering Blue Channel" << std::endl;
    debayer.Blue();

    std::cout << "Writing output" << std::endl;
    OutputWriter debayeredImage;

    std::cout << "Writing 8 bit PPM channels" << std::endl;
    std::cout << "Writing Red channel" << std::endl;

    debayeredImage.WritePpm("red", &debayer);
    std::cout << "Writing Green channel" << std::endl;
    debayeredImage.WritePpm("blue", &debayer);
    std::cout << "Writing Blue Channel" << std::endl;
    debayeredImage.WritePpm("green", &debayer); 

    std::cout << "Writing Debayered BMP image" << std::endl;
    debayeredImage.WriteBmp(&debayer);
    std::cout << "Writing Debayered Image into AVI" << std::endl;
    debayeredImage.WriteAvi();


    std::cout << "Please check ./results folder after sometime for output images" << std::endl;
    std::cout << "!!!!Thank you for using my program!!!!" << std::endl;
}
