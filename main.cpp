#include "src/headers/Input.h"
#include "src/headers/Demosaicing.h"
#include "src/headers/Output.h"

int main()
{
    std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!! ///////" << std::endl;

    Raw12Img inputImg("test_image/test_image.raw12");
    std::cout << "Loading Raw12 Image" << std::endl;
    inputImg.LoadImage();
    inputImg.InitializeCfa();
    inputImg.InitializeChannels();
    inputImg.print5by5tile();

    std::cout << "Demosaicing channels" << std::endl;
    Demosaic demosaicChannel;
    std::cout << "Demosaicing Red Channel" << std::endl;
    demosaicChannel.Red(inputImg.redChannel);
    std::cout << "Demosaicing Green Channel" << std::endl;
    demosaicChannel.Green(inputImg.greenChannel);
    std::cout << "Demosaicing Blue Channel" << std::endl;
    demosaicChannel.Blue(inputImg.blueChannel);

    std::cout << "Writing output" << std::endl;
    OutputImage outImg(&inputImg);

    std::cout << "Writing 8 bit PPM channels" << std::endl;
    std::cout << "Writing Red channel" << std::endl;
    outImg.WritePpm("red");
    std::cout << "Writing Green channel" << std::endl;
    outImg.WritePpm("blue");
    std::cout << "Writing Blue Channel" << std::endl;
    outImg.WritePpm("green"); 

    std::cout << "Writing Debayered BMP image" << std::endl;
    outImg.WriteBmp();
    std::cout << "Writing Debayered Image into AVI" << std::endl;
    outImg.WriteToAvi();


    std::cout << "Please check results folder after sometime for output images" << std::endl;
    std::cout << "!!!!Thank you for using my program!!!!" << std::endl;
}
