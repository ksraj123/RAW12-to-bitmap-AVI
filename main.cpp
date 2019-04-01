#include "src/headers/functional.h"
#include "src/headers/Raw12Img.h"

int main()
{
    Raw12Img InputImg("test_image/test_image.raw12");
    std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!!///////\n";
    std::cout << "Loading Raw12Image\n";
    InputImg.Load();
    std::cout << "Debayering channels\n";
    InputImg.DebayerChannels();
    std::cout << "Writing chaneels to results/ \n";
    InputImg.WriteChannels();
    std::cout << "Writing debayered BMP Image to results/ \n";
    InputImg.WriteDebayered();
    std::cout << "Please check results folder after sometime for output images\n";
    std::cout << "!!!!Thank you for using my program!!!!";
}
