#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "Item.h"
#include "Hashing.h"

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
    printf("Para atualizar digite ATU <ID/MAT> <nome> <ID> <CPF> <Matricula> <CRA>\n");
    printf("Para exbir digite EXI <ID/MAT/ALU>\n");
    printf("Para limpar a tela digite CLEAR\n");
    printf("Para sair do programa digite FIM\n\n");
    printf("Estão inseridos %d registros e %d estão disponiveis.\n\n",numero_reg,numero_dis);
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
		FILE *id;
		id = fopen(nome_id, "w+b");

        FILE *mat;
		mat = fopen(nome_mat, "w+b");

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
                if(aluno.Nome[0] != '#'){
                    if(!feof(arq)){
                        Inserir_hash(aluno,x,1,id);
                        Inserir_hash(aluno,x,2,mat);
                    }
                }
            }while(!feof(arq));
        }
        
        Carregar_cabecalho(arq);
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
                FILE *id;
                FILE *mat;
                registros = fopen(argv[1],"raw+b");
                id = fopen(nome_id, "raw+b");
                mat = fopen(nome_mat, "raw+b");
                if(Checar_existe(aux.Matricula,mat) == 1 && Checar_existe(aux.Identidade,id) == 1){
					int pos = Inserir_registro(aux, registros);
					fclose(registros);
					Inserir_hash(aux,pos,1,id);
					Inserir_hash(aux,pos,2,mat);
				}
				else{
					printf("Falha ao inserir, matricula ou identidade já existente.\n");
					fclose(registros);
				}
                fclose(id);
                fclose(mat);
     
            }

            //REMOÇÃO
            else if(strcmp(op,"REM")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    scanf("%s",argumentos[1]);
                    FILE* mat = fopen(nome_mat,"ra+b");
                    FILE* reg = fopen(argv[1], "ra+b");
                    FILE* id = fopen(nome_id, "ra+b");
                    Aluno aux = Carregar_registro2(argumentos[1],reg,mat);
                    Busca(argumentos[1],reg,mat,Remover);
                    Busca(aux.Identidade,reg,id,Remover);
                    fclose(mat);
                    fclose(id);
                    fclose(reg);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    scanf("%s",argumentos[1]);
                    FILE* mat = fopen(nome_mat,"ra+b");
                    FILE* reg = fopen(argv[1], "ra+b");
                    FILE* id = fopen(nome_id, "ra+b");
                    Aluno aux = Carregar_registro2(argumentos[1],reg,id);
                    Busca(argumentos[1],reg,id,Remover);
                    Busca(aux.Matricula,reg,mat,Remover);
                    fclose(mat);
                    fclose(id);
                    fclose(reg);
                }
            }

            //BUSCA
            else if(strcmp(op,"BUS")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_mat, "r+b");
                    FILE *reg = fopen(argv[1], "r+b");
                    int x;
					Busca(argumentos[1],reg,arq,Imprimir);
                    fclose(arq);
                    fclose(reg);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_id, "r+b");
                    FILE *reg = fopen(argv[1], "r+b");
					Busca(argumentos[1],reg,arq,Imprimir);
                    fclose(arq);
                    fclose(reg);
                }
                else{
					printf("Comando invalido\n");
				}
            }

           //ATUALIZAR
           else if(strcmp(op,"ATU")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    scanf("%s%s%s%s%s%s",argumentos[1],argumentos[2],argumentos[3],argumentos[4],argumentos[5],argumentos[6]);
                    FILE *mat = fopen(nome_mat,"ra+b");
                    FILE *id = fopen(nome_id,"ra+b");
                    FILE *reg = fopen(argv[1],"ra+b");
                    Aluno aluno;
                    strcpy(aluno.Nome,argumentos[2]);
                    strcpy(aluno.Identidade,argumentos[3]);
                    strcpy(aluno.CPF,argumentos[4]);
                    strcpy(aluno.Matricula,argumentos[5]);
                    aluno.CRA = atof(argumentos[6]);
                    if(Checar_existe(aluno.Matricula,mat) == 1 && Checar_existe(aluno.Identidade,id) == 1){
						Atualizar(argumentos[1],aluno,2,reg,mat,id);
					}
					else{
						printf("Falha ao atualizar, matricula ou identidade já existente.\n");
					}
					fclose(reg);
                    fclose(mat);
                    fclose(id);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    scanf("%s%s%s%s%s%s",argumentos[1],argumentos[2],argumentos[3],argumentos[4],argumentos[5],argumentos[6]);
                    FILE *mat = fopen(nome_mat,"ra+b");
                    FILE *id = fopen(nome_id,"ra+b");
                    FILE *reg = fopen(argv[1],"ra+b");
                    Aluno aluno;
                    strcpy(aluno.Nome,argumentos[2]);
                    strcpy(aluno.Identidade,argumentos[3]);
                    strcpy(aluno.CPF,argumentos[4]);
                    strcpy(aluno.Matricula,argumentos[5]);
                    aluno.CRA = atof(argumentos[6]);
                    if(Checar_existe(aluno.Matricula,mat) == 1 && Checar_existe(aluno.Identidade,id) == 1){
						Atualizar(argumentos[1],aluno,1,reg,mat,id);
					}
					else{
						printf("Falha ao atualizar, matricula ou identidade já existente.\n");
					}
                    fclose(reg);
                    fclose(mat);
                    fclose(id);
                }
                else{
					printf("Comando invalido\n");
				}
            }


            //EXIBIR
            else if(strcmp(op,"EXI")==0){
                scanf("%s", argumentos[0]);
                if(strcmp(argumentos[0],"MAT")==0){
                    //scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_mat,"rb");
                    Exibir(arq);
                    fclose(arq);
                }
                else if(strcmp(argumentos[0],"ID")==0){
                    //scanf("%s",argumentos[1]);
                    FILE *arq = fopen(nome_id,"rb");
                    Exibir(arq);
                    fclose(arq);
                }
                else if(strcmp(argumentos[0],"ALU")==0){
					FILE *arq = fopen(argv[1],"rb");
					Exibir_alunos(arq);
					fclose(arq);
				}
                else{
					printf("Comando invalido\n");
				}
            }
            
            else if(strcmp(op,"CLEAR")==0){
                system("clear");
                FILE* arq = fopen(argv[1],"r+b");
                Carregar_cabecalho(arq);
                menu();
            }
            
            else if (fim(op)==0){
				printf("Comando invalido\n");
			}
        //sleep(2);
        }while(fim(op)==0);

	

	return 0;
}
