all: apertus

apertus: main.o Raw12Img.o Bitmap.o Pixelmap.o Demosaicing.o
	g++ -o apertus main.o Raw12Img.o Bitmap.o Pixelmap.o Demosaicing.o

main.o: main.cpp
	g++ -c main.cpp

Pixelmap.o: code/Pixelmap.cpp code/headers/PPM_HEAD.h
	g++ -c code/Pixelmap.cpp

Bitmap.o: code/Bitmap.cpp code/headers/BMP_HEAD.h
	g++ -c code/Bitmap.cpp

Demosaicing.o: code/Demosaicing.cpp code/headers/Demosaicing.h
	g++ -c code/Demosaicing.cpp

Raw12Img.o: code/Raw12Img.cpp code/headers/functional.h
	g++ -c code/Raw12Img.cpp

clean_all: clean clean_results

clean:
	rm -f *.o code/*.o apertus 

clean_results:
	rm -f result/*.ppm result/*.bmp
