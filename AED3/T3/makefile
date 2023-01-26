HASH: Hashing.o Item.o main.o
	gcc main.o Item.o Hashing.o -o SisAlunos

main.o:	main.c Hashing.h
	gcc -c main.c

Hashing.o:	Hashing.c Hashing.h
	gcc -c Hashing.c

Item.o:	Item.c Item.h
	gcc -c Item.c

clean: 
	rm *.o
