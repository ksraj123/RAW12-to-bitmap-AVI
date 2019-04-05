#include "src/headers/Input.h"
#include "src/headers/Demosaicing.h"
#include "src/headers/Output.h"

int main()
{
    std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!!///////\n";

    InputImage InputImg("test_image/test_image.raw12");
    std::cout << "Loading Raw12Image\n";
    InputImg.Load();

    std::cout << "Debayering channels\n";
    Demosaic demo;
    demo.DemosaicChannels(&InputImg);

    std::cout << "Writing output\n";
    OutputImage OutImg(&InputImg);

    std::cout << "Writing 8 bit PPM channels\n";
    std::cout << "Writing Red channel\n";
    OutImg.WritePpm("red");
    std::cout << "Writing Green channel\n";
    OutImg.WritePpm("blue");
    std::cout << "Writing Blue Channel\n";
    OutImg.WritePpm("green"); 

    std::cout << "Writing Debayered BMP image\n";
    OutImg.WriteBmp();
    std::cout << "Writing Debayered Image into AVI\n";
    OutImg.WriteToAvi();


    std::cout << "Please check results folder after sometime for output images\n";
    std::cout << "!!!!Thank you for using my program!!!!\n";
}
