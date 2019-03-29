all: apertus

apertus: main.o Raw12Img.o Bitmap.o Pixelmap.o Demosaicing.o
	g++ -o apertus main.o Raw12Img.o Bitmap.o Pixelmap.o Demosaicing.o

main.o: main.cpp
	g++ -c main.cpp

Pixelmap.o: src/Pixelmap.cpp src/headers/PPM_HEAD.h
	g++ -c src/Pixelmap.cpp

Bitmap.o: src/Bitmap.cpp src/headers/BMP_HEAD.h
	g++ -c src/Bitmap.cpp

Demosaicing.o: src/Demosaicing.cpp src/headers/Demosaicing.h
	g++ -c src/Demosaicing.cpp

Raw12Img.o: src/Raw12Img.cpp src/headers/functional.h
	g++ -c src/Raw12Img.cpp

clean_all: clean clean_results

clean:
	rm -f *.o src/*.o apertus 

clean_results:
	rm -f result/*.ppm result/*.bmp
