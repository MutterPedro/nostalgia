EA1: Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_1.o Item.o
	gcc Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_1.o Item.o -o EA1 -lm
	
EA2: Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_2.o Item.o
	gcc Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_2.o Item.o -o EA2 -lm
	
EA3: Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_3.o Item.o
	gcc Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_3.o Item.o -o EA3 -lm
	
EA4: Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_4.o Item.o
	gcc Cliente_Arvore_Binaria.o Estrategia_de_Aceleracao_4.o Item.o -o EA4 -lm

ABB: Cliente_Arvore_Binaria.o Dicionario_Arvore_Binaria.o Item.o
	gcc Cliente_Arvore_Binaria.o Dicionario_Arvore_Binaria.o Item.o -o ABB -lm

DSW: Cliente_Arvore_Binaria.o Dicionario_ABB_DSW.o Item.o
	gcc Cliente_Arvore_Binaria.o Dicionario_ABB_DSW.o Item.o -o DSW -lm

AVL: Cliente_Arvore_Binaria.o Dicionario_ABB_AVL.o Item.o
	gcc Cliente_Arvore_Binaria.o Dicionario_ABB_AVL.o Item.o -o AVL -lm

Estrategia_de_Aceleracao_1.o: Estrategia_de_Aceleracao_1.c Item.h Dicionario.h
	gcc -c Estrategia_de_Aceleracao_1.c
	
Estrategia_de_Aceleracao_2.o: Estrategia_de_Aceleracao_2.c Item.h Dicionario.h
	gcc -c Estrategia_de_Aceleracao_2.c
	
Estrategia_de_Aceleracao_3.o: Estrategia_de_Aceleracao_3.c Item.h Dicionario.h
	gcc -c Estrategia_de_Aceleracao_3.c
	
Estrategia_de_Aceleracao_4.o: Estrategia_de_Aceleracao_4.c Item.h Dicionario.h
	gcc -c Estrategia_de_Aceleracao_4.c
	
Cliente_Arvore_Binaria.o: Cliente_Arvore_Binaria.c Item.h Dicionario.h
	gcc -c Cliente_Arvore_Binaria.c

Dicionario_Arvore_Binaria.o: Dicionario_Arvore_Binaria.c Item.h Dicionario.h
	gcc -c Dicionario_Arvore_Binaria.c

Dicionario_ABB_DSW.o: Dicionario_ABB_DSW.c Item.h Dicionario.h
	gcc -c Dicionario_ABB_DSW.c

Dicionario_ABB_AVL.o: Dicionario_ABB_AVL.c Item.h Dicionario.h
	gcc -c Dicionario_ABB_AVL.c

Item.o: Item.c Item.h
	gcc -c Item.c
