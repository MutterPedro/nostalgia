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
Retorna um item vazio
*/
#define Null_Item() (NULL)

/*
Escreve um item
*/
#define Escreve(A) printf("%s ", A->c)


/*
Tipo chave
*/

/*
Tipo Registro
*/
typedef struct
{
	char c[100];
        int cont;
} Registro;

/*
Tipo item
*/
typedef Registro* Item;

void Imprime(Item i);

#endif