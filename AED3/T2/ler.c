#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char Nome[50];
    char Identidade[15];
    char CPF[15];
    char Matricula[15];
    double CRA;
} Aluno;

struct No//Ou página
{
    char chaves[4-1][15];
	int numItens;
    int Filhos[4];
    int pai;
    int endereco;
    int num_filhos;
};

int main(int argc, char** argv){   

FILE *arq;

arq = fopen("alunos_ID.dat", "r+b");
int i=0;

struct No aux;
while(!feof(arq)){
	fread(&aux,1,sizeof(struct No),arq);
	for(i=0;i<aux.numItens;i++)
		printf("%s\n",aux.chaves[i]);
}


fclose(arq);

return 0;

}
