#include "src/headers/Input.h"
#include "src/headers/Demosaicing.h"
#include "src/headers/Output.h"

int main()
{
    std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!! ///////" << std::endl;

    std::cout << "Loading Raw12 Image" << std::endl;
    ImageLoader raw12Img("test_image/test_image.raw12");
    raw12Img.LoadImage();

    std::cout << "Demosaicing channels" << std::endl;
    ImageProcessor debayer;
    debayer.SeperateChannels(raw12Img.cfa);

    
    std::cout << "Printing 5 by 5 tile of CFA" << std::endl;
    OutputWriter::Print5by5tile(raw12Img.cfa);
    std::cout << "Printing 5 by 5 tile of Red Channel before debayering" << std::endl;
    OutputWriter::Print5by5tile(debayer.redChannel);
    std::cout << "Printing 5 by 5 tile of Green Channel before debayering" << std::endl;
    OutputWriter::Print5by5tile(debayer.greenChannel);
    std::cout << "Printing 5 by 5 tile of Blue Channel before debayering" << std::endl;
    OutputWriter::Print5by5tile(debayer.blueChannel);

    std::cout << "Demosaicing Red Channel" << std::endl;
    debayer.Red();
    std::cout << "Demosaicing Green Channel" << std::endl;
    debayer.Green();
    std::cout << "Demosaicing Blue Channel" << std::endl;
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


    std::cout << "Please check results folder after sometime for output images" << std::endl;
    std::cout << "!!!!Thank you for using my program!!!!" << std::endl;
}
