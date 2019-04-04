all: apertus

apertus: main.o Input.o Output.o Demosaicing.o
	g++ -o apertus main.o Input.o Output.o Demosaicing.o

main.o: main.cpp src/headers/functional.h
	g++ -c main.cpp

Output.o: src/Output.cpp src/headers/Output.h src/headers/functional.h
	g++ -c src/Output.cpp

Demosaicing.o: src/Demosaicing.cpp src/headers/Demosaicing.h src/headers/functional.h
	g++ -c src/Demosaicing.cpp

Input.o: src/Input.cpp src/headers/Input.h src/headers/functional.h
	g++ -c src/Input.cpp

clean_all: clean clean_results

clean:
	rm -f *.o src/*.o apertus 

clean_results:
	rm -f result/*.ppm result/*.bmp result/*.avi
