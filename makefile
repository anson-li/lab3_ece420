###
# Designating default compiler and compiler values
###
CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread -lm

###
# Setting default make
###
default: datagen serialtester main
all: datagen serialtester main

###
# Support
###
datagen:
	$(CC) -o datagen datagen.c Lab3IO.c

serialtester:
	$(CC) -o serialtester serialtester.c Lab3IO.c -lm

main:
	clang-omp -fopenmp main.c Lab3IO.c -ggdb

###
# Clean process
###
clean:
	rm -f datagen serialtester main main.o
