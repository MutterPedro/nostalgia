#ifndef HASHING_H
#define HASHING_H

#include "Item.h"
#include <stdio.h>
#include <stdlib.h>

int numero_reg;
int numero_dis;

int Inserir_registro(Aluno,FILE*);
void Inicializar_Bloco(FILE*);
void Inserir_hash(Aluno,int,int,FILE*);
void Exibir(FILE*);
void Busca(char chave[],FILE* reg,FILE* hash,void (*P)(Chave*,FILE*,FILE*));
void Imprimir(Chave*,FILE*,FILE*);
void Remover(Chave*,FILE*,FILE*);
void Atualizar(char[],Aluno,int,FILE*,FILE*,FILE*);
Aluno Carregar_registro2(char[],FILE*,FILE*);
void Carregar_cabecalho(FILE* arq);
int Checar_existe(char[],FILE*);
int Exibir_alunos(FILE*);
#endif
