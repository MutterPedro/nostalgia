AB: Dicionario_Arvore_B.o Item.o main.o
	gcc main.o Item.o Dicionario_Arvore_B.o -o SisAlunos

main.o:	main.c Dicionario.h
	gcc -c main.c

Dicionario_Arvore_B.o:	Dicionario_Arvore_B.c Dicionario.h
	gcc -c Dicionario_Arvore_B.c

Item.o:	Item.c Item.h
	gcc -c Item.c

clean: 
	rm *.o