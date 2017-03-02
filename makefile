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
	$(CC) -g -o main main.c Lab3IO.c

###
# Clean process
###
clean:
	rm -f datagen serialtester main
