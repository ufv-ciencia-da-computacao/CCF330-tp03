.PHONY: all

all: main

main: ./src/algorithms.c ./src/main.c
	gcc ./src/algorithms.c -lm ./src/main.c -o main

clean:
ifeq ($(OS),Windows_NT)
	del main
else
	rm main
endif
