CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: exec

%.o : %.c tri.h
	$(CC) -c $< -o $@
	
exec: $(OBJ)
	$(CC) $^ -o $@
