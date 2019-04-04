all: apertus

apertus: main.o Raw12Img.o OutImg.o Demosaicing.o riffAVI.o
	g++ -o apertus main.o Raw12Img.o OutImg.o Demosaicing.o riffAVI.o

main.o: main.cpp src/headers/functional.h
	g++ -c main.cpp

OutImg.o: src/OutImg.cpp src/headers/OutImg.h src/headers/functional.h
	g++ -c src/OutImg.cpp

riffAVI.o: src/riffAVI.cpp src/headers/riffAVI.h src/headers/functional.h
	g++ -c src/riffAVI.cpp

Demosaicing.o: src/Demosaicing.cpp src/headers/Demosaicing.h src/headers/functional.h
	g++ -c src/Demosaicing.cpp

Raw12Img.o: src/Raw12Img.cpp src/headers/Raw12Img.h src/headers/functional.h
	g++ -c src/Raw12Img.cpp

clean_all: clean clean_results

clean:
	rm -f *.o src/*.o apertus 

clean_results:
	rm -f result/*.ppm result/*.bmp
