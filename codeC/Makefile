CC=gcc

all: exec

avl.o : src/avl.c include/avl.h include/maths.h
	$(CC) -c $< -o $@

fichier.o : src/fichier.c include/fichier.h
	$(CC) -c $< -o $@

maths.o : src/maths.c include/maths.h
	$(CC) -c $< -o $@
	
main.o : src/main.c include/avl.h include/fichier.h include/maths.h
	$(CC) -c $< -o $@

exec: avl.o fichier.o maths.o main.o
	$(CC) $^ -o $@

clean:
	rm -rf *.o

mrproper: clean
	rm -rf exec