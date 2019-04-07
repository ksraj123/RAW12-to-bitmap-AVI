all: apertus

apertus: main.o ImageLoader.o OutputWriter.o ImageProcessor.o
	g++ -o apertus main.o ImageLoader.o OutputWriter.o ImageProcessor.o

main.o: main.cpp
	g++ -c main.cpp

OutputWriter.o: src/OutputWriter.cpp src/headers/OutputWriter.h
	g++ -c src/OutputWriter.cpp

ImageProcessor.o: src/ImageProcessor.cpp src/headers/ImageProcessor.h
	g++ -c src/ImageProcessor.cpp

ImageLoader.o: src/ImageLoader.cpp src/headers/ImageLoader.h
	g++ -c src/ImageLoader.cpp

clean_all: clean clean_results

clean:
	rm -f *.o src/*.o apertus 

clean_results:
	rm -f result/*.ppm result/*.bmp result/*.avi
