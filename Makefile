CC = gcc
BIN = bin/Minecraft
CFLAGS = -std=c11 -g -flto
INC = -I./glfw/include -I./cglm/include -I./glad
LDFLAGS = -L./glfw/src/ -L./cglm/ -lglfw3 -lcglm -lGL -lX11 -lm

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)

.PHONY: all libs clean

all:
	mkdir -p bin/
	$(CC) $(CFLAGS) -DMC_DEBUG $(INC) $(SRC) $(LDFLAGS) -o $(BIN)

libs:
	cd glfw && cmake -DGLFW_BUILD_WAYLAND=OFF . && make
	cd cglm && cmake . && make
	
clean:
	rm -r $(BIN)
