CC = gcc
BIN = bin/Minecraft
CFLAGS = -std=c11 -Werror -g -flto
INC = -Iglfw/include -Icglm/include -I.
LDFLAGS = -L./glfw/src/ -L./cglm/ -lglfw3 -lcglm -lGL -lX11 -lm

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)

.PHONY: all libs clean

all:
	mkdir -p bin/
	$(CC) $(CFLAGS) -DMC_DEBUG $(SRC) $(INC) $(LDFLAGS) -o $(BIN)

libs:
	cd glfw && cmake . && make
	cd cglm && cmake . && make
	
clean:
	rm -r $(BIN)
