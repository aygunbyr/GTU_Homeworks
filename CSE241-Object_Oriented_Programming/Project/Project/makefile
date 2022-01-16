all: project

project: main.o organism.o world.o ant.o doodlebug.o
	g++ -std=c++11 main.o organism.o world.o ant.o doodlebug.o  -o project

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

organism.o: organism.cpp organism.h
	g++ -std=c++11 -c organism.cpp

world.o: world.cpp world.h
	g++ -std=c++11 -c world.cpp

ant.o: ant.cpp ant.h
	g++ -std=c++11 -c ant.cpp

doodlebug.o: doodlebug.cpp doodlebug.h
	g++ -std=c++11 -c doodlebug.cpp

clean:
	rm -rf *o project
