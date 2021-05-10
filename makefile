DEBUG ?= 0

.PHONY: all

all: main

main: ./src/leitura.c ./src/menu.c ./src/algorithms.c ./src/main.c
ifeq ($(DEBUG),1)
	gcc -D DEBUG ./src/menu.c ./src/leitura.c ./src/algorithms.c -lm ./src/main.c -o main
else
	gcc ./src/menu.c ./src/leitura.c ./src/algorithms.c -lm ./src/main.c -o main
endif

clean:
ifeq ($(OS),Windows_NT)
	del main
else
	rm main
endif
