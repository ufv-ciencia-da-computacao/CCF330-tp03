.PHONY: all

all: main

main: ./src/leitura.c ./src/algorithms.c ./src/main.c
	gcc ./src/menu.c ./src/leitura.c ./src/algorithms.c -lm ./src/main.c -o main

clean:
ifeq ($(OS),Windows_NT)
	del main
else
	rm main
endif
