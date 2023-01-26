/*
Implementado por Dilson Lucas Pereira - DCC/UFLA

Interface para um tipo dicionário. Assume a definição de um tipo Alunos. Cada Alunos contém um campo do tipo Chave.
*/

#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "Item.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct dicionario* Dicionario;


Dicionario Inicializa(FILE* arq);
void Insere(Dicionario, Alunos ,int ,FILE *,int);
Alunos Remove(Dicionario, char[]);
Alunos Busca(Dicionario, char[],FILE*,FILE*);
int Inserir_registro(Alunos, FILE*);
void Exibir_registros(Dicionario ,FILE *);
void Exibir_registros_ordenados(Dicionario,FILE*, FILE*);
//FILE* Abrir_arquivo(char[]);

#endif
