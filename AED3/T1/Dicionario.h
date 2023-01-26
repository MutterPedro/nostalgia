/*
Implementado por Dilson Lucas Pereira - DCC/UFLA

Interface para um tipo dicionário. Assume a definição de um tipo Item. Cada item contém um campo do tipo Chave.
*/

#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "Item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct dicionario* Dicionario;

Dicionario DIC_Inicializa();
void Insere_ou_Processa(Dicionario, Item);
Item DIC_Remove(Dicionario, char[]);
Item DIC_Busca(Dicionario, char[]);
void DIC_Imprime(Dicionario);
void DIC_Mais_Repete(Dicionario);

/*
A função processa aplica a função *P uma vez a cada item do dicionário.
P é um ponteiro para uma função
*/
void DIC_Processa(Dicionario D, void (*P)(Item));


#endif