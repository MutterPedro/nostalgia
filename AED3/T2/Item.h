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

/*
Atenção
As funções abaixo foram implementadas usando macros, mas poderiam ser funções normais
*/
/*
Retorna a chave do item
*/
#define Get_Chave(A) (A->c)

/*
Retorna verdadeiro se c1 < c2, falso caso contrário
*/
#define Menor(c1, c2) (c1 < c2)

/*
Retorna um item vazio
*/
#define Null_Alunos() (NULL)

/*
Escreve um item
*/
#define Escreve(A) printf("%d ", A->c)


/*
Tipo Registro
*/
typedef struct
{
    char Nome[50];
    char Identidade[15];
    char CPF[15];
    char Matricula[15];
    double CRA;
} Aluno;

/*
Tipo item
*/
typedef Aluno* Alunos;

void Imprime(Alunos i);

#endif
