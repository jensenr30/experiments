SDL_FLAGS := $(shell sdl2-config --cflags --libs)

all:
	g++ main.cpp $(SDL_FLAGS) -O0 -g -ggdb3 -DDEBUG -Wall -o main && ./main
