 /*
Implementado por Dilson Lucas Pereira - DCC/UFLA

Este arquivo apresenta a definição de um item genérico, para ser usado com um tipo dicionário.
O dicionário não sabe o tipo do item. A única coisa que se assume é que cada item possui uma chave. 
O dicionário não sabe o tipo da chave. O dicionário só acessa itens e chaves por meio das funções definidas aqui.
*/

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_BLOCO 3
#define NUM_INICIAL_BLOCOS 10

typedef struct
{
    char Nome[50];
    char Identidade[15];
    char CPF[15];
    char Matricula[15];
    double CRA;
} Aluno;


typedef struct{
	char indice[15];
	int RRN;
}Chave;


typedef struct{
    Chave* chaves[TAM_BLOCO];
}Bloco;
/*
Tipo item
*/
typedef Aluno* Alunos;


#endif
