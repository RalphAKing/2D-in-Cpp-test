all: compile link

compile:
	g++ -Isrc/include -c main.cpp

	g++ -Isrc/include -c seedgen.cpp

link:
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

	g++ seedgen.o -o seedgen -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system