all: compile link

compile:
	g++ -IC:/msys64/ucrt64/include -c main.cpp

link:
	g++ main.o -o main -LC:\msys64\ucrt64\lib -lsfml-graphics -lsfml-window -lsfml-system
