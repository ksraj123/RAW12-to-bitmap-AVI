#include "src/headers/Input.h"
#include "src/headers/Demosaicing.h"
#include "src/headers/Output.h"

int main()
{
    std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!! ///////\n";

    InputImage inputImg("test_image/test_image.raw12");
    std::cout << "Loading Raw12Image\n";
    inputImg.Load();
    inputImg.InitializeChannels();

    std::cout << "Debayering channels\n";
    Demosaic demo;
    demo.DemosaicChannels(&inputImg);

    std::cout << "Writing output\n";
    OutputImage outImg(&inputImg);

    std::cout << "Writing 8 bit PPM channels\n";
    std::cout << "Writing Red channel\n";
    outImg.WritePpm("red");
    std::cout << "Writing Green channel\n";
    outImg.WritePpm("blue");
    std::cout << "Writing Blue Channel\n";
    outImg.WritePpm("green"); 

    std::cout << "Writing Debayered BMP image\n";
    outImg.WriteBmp();
    std::cout << "Writing Debayered Image into AVI\n";
    outImg.WriteToAvi();


    std::cout << "Please check results folder after sometime for output images\n";
    std::cout << "!!!!Thank you for using my program!!!!\n";
}
