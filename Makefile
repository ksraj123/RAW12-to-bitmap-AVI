all: apertus

apertus: main.o Raw12Img.o OutImg.o Demosaicing.o
	g++ -o apertus main.o Raw12Img.o OutImg.o Demosaicing.o

main.o: main.cpp
	g++ -c main.cpp

OutImg.o: src/OutImg.cpp src/headers/OutImg.h
	g++ -c src/OutImg.cpp

Demosaicing.o: src/Demosaicing.cpp src/headers/Demosaicing.h
	g++ -c src/Demosaicing.cpp

Raw12Img.o: src/Raw12Img.cpp src/headers/functional.h
	g++ -c src/Raw12Img.cpp

clean_all: clean clean_results

clean:
	rm -f *.o src/*.o apertus 

clean_results:
	rm -f result/*.ppm result/*.bmp
