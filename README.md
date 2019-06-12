# Debayering of RAW12 images to obtain red, green and blue channels as PPM(P6) images and output full colour debayered image as bitmap(BMP) and single frame AVI from scratch without using any external libraries

descriptionSensors used in digital cameras lack the ability to capture color images as they lack the ability to distinguish how much of each color they are receiving. To capture color images a filter is placed above the sensor which permits only a particular color light at each sensel but as a result of this, each sensel has intensity values of only one channel which is not sufficient to produce a color image. Hence different demosaicing algorithms are used to obtain full-color RGB images from RAW images.

For more information about demosaicing refer to these links -
https://en.wikipedia.org/wiki/Demosaicing
https://en.wikipedia.org/wiki/Bayer_filter

This project is written in C++, it debayers a 12-bit RAW12 RGGB image using bilinear interpolation approach and writes 8-bit Red, Green and Blue channels into PPM(P6) files and writes the deBayered full-color RGB image into a BMP file and into a single frame riff AVI file.

This project can be easily made by using make build system.
Open terminal in root directory of the project and execute the command - make (go through the make file for details)

All three channels namely red, green and blue in PPM format and debayered output image in BMP and single frame AVI is writeen inside results folder.

test_image folder contains a RAW12 file for testing purpose.
