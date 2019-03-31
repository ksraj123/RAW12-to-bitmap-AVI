#include "src/headers/functional.h"
#include "src/headers/Raw12Img.h"

int main(){
std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!!///////\n";

Raw12Img InputImg("test_image/test_image.raw12");

std::cout << "Loading Raw12Image\n";
InputImg.Load();
std::cout << "Debayering channels\n";
InputImg.Debayer_channels();
std::cout << "Writing chaneels to results/ \n";
InputImg.Write_channels();
std::cout << "Writing debayered BMP Image to results/ \n";
InputImg.Write_debayered_image();
std::cout << "Please check results folder after sometime for output images\n";

std::cout << "!!!!Thank you for using my program!!!!";
}
