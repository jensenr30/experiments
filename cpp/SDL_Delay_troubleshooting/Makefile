SDL_FLAGS := $(shell sdl2-config --cflags --libs)

.PHONY: main
main:
	g++ main.cpp $(SDL_FLAGS) -O0 -g -ggdb3 -DDEBUG -Wall -o main

run:
	./main

run20:
	./run20.sh

