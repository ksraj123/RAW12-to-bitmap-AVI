#include "src/headers/functional.h"
#include "src/headers/Raw12Img.h"

int main(){

std::cout << "//////// !!!! KUMAR SAURABH RAJ !!!!///////\n";

Raw12Img InputImg("test_image/test_image.raw12");

std::cout << "Loading Raw12Image\n";
InputImg.load();

std::cout << "Initializing R G B channels\n";
InputImg.initialize_channels();

std::cout << "Debayering channels\n";
InputImg.debayer_channels();

std::cout << "Writing chaneels to results/ \n";
InputImg.write_channels();

std::cout << "Writing debayered BMP Image to results/ \n";
InputImg.write_debayered_image();

std::cout << "Please check results folder after sometime for output images\n";

std::cout << "!!!!Thank you for using my program!!!!";

}
