ALL_C = $(wildcard src/*.c)
ALL_H = $(wildcard src/*.h)

.phony: all

all:
	gcc -Wall ${ALL_C} main.c -o main.o
