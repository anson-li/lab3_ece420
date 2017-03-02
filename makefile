###
# Designating default compiler and compiler values
###
CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread -lm

###
# Setting default make
###
default: datagen lab3io serialtester main
all: datagen lab3io serialtester main

###
# Support
###
datagen:
	$(CC) -o datagen datagen.c

lab3io:
	$(CC) -o lab3IO lab3IO.c

serialtester:
	$(CC) -o serialtester serialtester.c

main:
	$(CC) -g -o main main.c

###
# Clean process
###
clean:
	rm -f datagen lab3IO serialtester main
