#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "Item.h"
#include "Dicionario.h"

int fim(char s[5]){
	if(strcmp(s,"FIM") != 0)
		return 0;

	return 1;
}

void menu(){
    printf("\t\t\tManipulador de arquivo.\n\n");
    printf("Para inserir digite INS <Nome> <ID> <CPF> <Matricula> <CRA>\n");
    printf("Para remover digite REM <ID/MAT> <id/mat>\n");
    printf("Para buscar digite BUS <ID/MAT> <id/mat>\n");
    printf("Para atualizar digite ATU <ID/MAT> <id/mat> <nome> <ID> <CPF> <Matricula> <CRA>\n");
    printf("Para exbir digite EXI <ID/MAT>\n");
    printf("Para exibir a Arvore B dis indices digite IMP <ID/MAT>\n");
    printf("Para limpar a tela digite CLEAR\n");
    printf("Para sair do programa digite FIM\n\n");
}

int main(int argc, char** argv){   
		
        system("clear");
		char nome_id[50],nome_mat[50];
		strcpy(nome_id,argv[1]);
		strcpy(nome_mat,argv[1]);
		int i=0;
		while(i<strlen(argv[1])){
			if(argv[1][i]=='.'){
				nome_id[i]='\0';
				nome_mat[i]='\0';
				strcat(nome_id,"_ID.dat");
				strcat(nome_mat,"_MAT.dat");
			}
			i++;
		}
        //printf("%s\n", nome_id);
        //printf("%s\n", nome_mat);
		FILE *id;
		id = fopen(nome_id, "w+b");
        Dicionario arvore_ID = Inicializa(id);

        FILE *mat;
		mat = fopen(nome_mat, "w+b");
        Dicionario arvore_mat = Inicializa(mat);

        FILE *arq;
        arq = fopen(argv[1], "aw+b");
        fseek(arq,0,SEEK_END);
        int x = ftell(arq);
        //printf("%d\n",x);
        
        if(x > 0){            
            fseek(arq,2*sizeof(int),SEEK_SET);
            do{
                Aluno aluno;
                x=ftell(arq);
                //printf("%d\n",x);
                fread(&aluno,sizeof(Aluno),1,arq);
                //printf("%s\n",aluno.Nome);
                if(!feof(arq)){
                    Insere(arvore_ID,&aluno,x,id,1);
                    Insere(arvore_mat,&aluno,x,mat,2);
                }
            }while(!feof(arq));
        }
        
        fclose(arq);
        fclose(id);
        fclose(mat);
		
        char op[5];
        char argumentos[7][50];

        menu();
        do{
            //system("clear");
            scanf("%s",op);
            //INSERÇÃO
            if(strcmp(op,"INS")==0){
                scanf("%s%s%s%s%s",argumentos[0],argumentos[1],argumentos[2],argumentos[3],argumentos[4]);
                Aluno aux;
                strcpy(aux.Nome,argumentos[0]);
                strcpy(aux.Identidade,argumentos[1]);
                strcpy(aux.CPF,argumentos[2]);
                strcpy(aux.Matricula,argumentos[3]);
                aux.CRA = atof(argumentos[4]);
                FILE *registros;
                registros = fopen(argv[1],"ra+b");
                int pos = Inserir_registro(&aux, registros);
                fclose(registros);
                FILE *id;
                id = fopen(nome_id, "ra+b");
                Insere(arvore_ID,&aux,pos,id,1);
                FILE *mat;
                mat = fopen(nome_mat, "ra+b");
                Insere(arvore_mat,&aux,pos,mat,2);
                fclose(id);
                fclose(mat);
     
            }

            //REMOÇÃO
            else if(strcmp(op,"REM")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    scanf("%s",argumentos[1]);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    scanf("%s",argumentos[1]);
                }
            }

            //BUSCA
            else if(strcmp(op,"BUS")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_mat, "r+b");
                    FILE *reg = fopen(argv[1], "r+b");
                    Alunos aluno = Busca(arvore_mat,argumentos[1],arq,reg); 
                    Imprimir(aluno);
                    fclose(arq);
                    fclose(reg);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_id, "r+b");
                    FILE *reg = fopen(argv[1], "r+b");
                    Alunos aluno = Busca(arvore_ID,argumentos[1],arq,reg); 
                    Imprimir(aluno);
                    fclose(arq);
                    fclose(reg);
                }
            }

           //ATUALIZAR
           else if(strcmp(op,"ATU")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    scanf("%s%s%s%s%s%s",argumentos[1],argumentos[2],argumentos[3],argumentos[4],argumentos[5],argumentos[6]);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    scanf("%s%s%s%s%s%s",argumentos[1],argumentos[2],argumentos[3],argumentos[4],argumentos[5],argumentos[6]);
                }
            }

           //EXIBIR
           else if(strcmp(op,"IMP")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    //scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_mat,"rb");
                    Exibir_registros(arvore_mat,arq);
                    fclose(arq);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    //scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_id,"rb");
                    Exibir_registros(arvore_ID,arq);
                    fclose(arq);
                }
            }
            else if(strcmp(op,"EXI")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    //scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_mat,"rb");
                    FILE *reg = fopen(argv[1],"rb");
                    Exibir_registros_ordenados(arvore_mat,arq,reg);
                    fclose(arq);
                    fclose(reg);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    //scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_id,"rb");
                    FILE *reg = fopen(argv[1],"rb");
                    Exibir_registros_ordenados(arvore_ID,arq,reg);
                    fclose(arq);
                    fclose(reg);
                }
            }

            else if(strcmp(op,"CLEAR")==0){
                system("clear");
                menu();
            }
        //sleep(2);
        }while(fim(op)==0);

	

	return 0;
}