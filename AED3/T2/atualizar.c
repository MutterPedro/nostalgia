#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
	char nome[50];
	int mat;
}Aluno;


int main(){
	FILE* arq = fopen("teste.dat", "w+b");
	
	Aluno aluno,aluno2,aluno3;
	strcpy(aluno.nome, "pedro");
	aluno.mat = 123;
	strcpy(aluno2.nome, "carlos");
	aluno2.mat = 321;
	
	fwrite(&aluno,sizeof(Aluno),1,arq);
	fclose(arq);
	
	FILE *arq2 =fopen("teste.dat", "rb");	
	
	fread(&aluno3,sizeof(Aluno),1,arq2);
	printf("Nome: %s\n", aluno3.nome);
	printf("Matricula: %d\n", aluno3.mat);
	fclose(arq2);
	
	FILE *arq3 = fopen("teste.dat", "wb");
	fseek(arq,0,SEEK_SET);
	fwrite(&aluno2,sizeof(Aluno),1,arq3);
	fclose(arq3);
	
	FILE *arq4 = fopen("teste.dat", "rb");
	fread(&aluno3,sizeof(Aluno),1,arq4);
	fclose(arq4);
	
	printf("Nome: %s\n", aluno3.nome);
	printf("Matricula: %d\n", aluno3.mat);
	
	return 0;
}
