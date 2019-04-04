#include "src/headers/functional.h"
#include "src/headers/Raw12Img.h"
#include "src/headers/Demosaicing.h"
#include "src/headers/OutImg.h"

int main()
{
    std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!!///////\n";

    InputImage InputImg("test_image/test_image.raw12");
    std::cout << "Loading Raw12Image\n";
    InputImg.Load();

    std::cout << "Debayering channels\n";
    Demosaic demo;
    demo.DemosaicChannels(&InputImg);

    OutputImage OutImg; 
    std::cout << "Writing output/ \n";
    OutImg.WriteOutput(&InputImg);

    std::cout << "Please check results folder after sometime for output images\n";
    std::cout << "!!!!Thank you for using my program!!!!\n";
}
