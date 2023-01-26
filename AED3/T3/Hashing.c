#include "Hashing.h"


void Inserir_hash_interno(char chave[],int pos,FILE* arq);
Aluno Carregar_registro(FILE* arq, int RRN);
int Hash(char chave[]);

void Inserir_hash(Aluno aluno,int pos,int tipo,FILE* arq){
    if(tipo == 1){
        Inserir_hash_interno(aluno.Identidade,pos,arq);
    }
    else{
        Inserir_hash_interno(aluno.Matricula,pos,arq);
    }
}

int Hash(char chave[]){
	return atoi(chave) % NUM_INICIAL_BLOCOS;
}

void Inicializar_Bloco(FILE* arq){
   int i,j;
   fseek(arq,0,SEEK_SET);
   for(i=0;i<NUM_INICIAL_BLOCOS;i++){
   	Bloco *blocos = malloc(sizeof(Bloco));
        for(j=0;j<TAM_BLOCO;j++){
            blocos->chaves[j] = malloc(sizeof(Chave));
            blocos->chaves[j]->RRN = -1;
        }
    fwrite(blocos,sizeof(Bloco),1,arq);
    free(blocos);
   }
}

int Inserir_registro(Aluno aluno,FILE* arq){
	if(numero_dis < NUM_INICIAL_BLOCOS*TAM_BLOCO){
		numero_reg++;
		numero_dis++;
		fseek(arq,0,SEEK_SET);
		fwrite(&numero_reg,sizeof(int),1,arq);
		fwrite(&numero_dis,sizeof(int),1,arq);
		fseek(arq,0,SEEK_END);
		int x = ftell(arq);
		fwrite(&aluno,sizeof(Aluno),1,arq);
		Aluno aux = Carregar_registro(arq,x);
		printf("Aluno %s inserido com sucesso.\n", aluno.Nome);
		return x;
	}
	else{
		printf("Sem espaço para nova inserção.\n");
		return -1;
	}
}

void Inserir_hash_interno(char chave[],int pos, FILE* arq){
	if(pos >= 0){
	    int posicao = Hash(chave);
	   // printf("%d\n",posicao);
	    fseek(arq,0,SEEK_END);
	    Bloco* bloco = malloc(sizeof(Bloco));
	    if(ftell(arq) <= 0){
	        Inicializar_Bloco(arq);
	    }
	    fseek(arq,posicao*sizeof(Bloco),SEEK_SET);
	    fread(bloco,sizeof(Bloco),1,arq);

	    int i=0,k=0;
	    while(bloco->chaves[i]->RRN >= 0 && k <= TAM_BLOCO*NUM_INICIAL_BLOCOS){
	        
	        i++;
	        if(i >= TAM_BLOCO){
	            i=0;
	            posicao++;
	            if(posicao >= NUM_INICIAL_BLOCOS){
	                posicao = 0;
	                //printf("caiu\n");
	            }
	            fseek(arq,posicao*sizeof(Bloco),SEEK_SET);
	            fread(bloco,sizeof(Bloco),1,arq);
	        }

	        k++;
	    }
    	if(k <= TAM_BLOCO*NUM_INICIAL_BLOCOS){
        	strcpy(bloco->chaves[i]->indice,chave);
        	bloco->chaves[i]->RRN = pos;
        	fseek(arq,posicao*sizeof(Bloco),SEEK_SET);
        	fwrite(bloco,sizeof(Bloco),1,arq);
    	}
    	free(bloco);
	}
}

void Exibir(FILE* arq){
    fseek(arq,0,SEEK_END);
    if(ftell(arq) <= 0){
        printf("Arquivo vazio.\n");
        return;
    }

    int i =0,j=0;
    Bloco* bloco = malloc(sizeof(Bloco));
    fseek(arq,0,SEEK_SET);
    fread(bloco,sizeof(Bloco),1,arq);

    while(i < NUM_INICIAL_BLOCOS){
        if(j == 0){
            printf("[");
        }
        if(bloco->chaves[j]->RRN >= 0)
            printf(" %s,", bloco->chaves[j]->indice);
        printf(" %d ", bloco->chaves[j]->RRN);
        j++;
        if(j >= TAM_BLOCO){
            i++;
            j=0;
            printf("]\n");
        }
        else{
            printf("|");
        }
    fseek(arq,i*sizeof(Bloco),SEEK_SET);
    fread(bloco,sizeof(Bloco),1,arq);    
    }
    free(bloco);
}

Aluno Carregar_registro(FILE* arq, int RRN){
    fseek(arq,RRN,SEEK_SET);
    Aluno aluno;
    fread(&aluno,sizeof(Aluno),1,arq);

    return aluno;
}

void Busca(char chave[],FILE* reg,FILE* hash,void (*P)(Chave*,FILE*,FILE*)){
	
	int i,j=0;
	i = Hash(chave);
	Bloco* bloco = malloc(sizeof(Bloco));
	fseek(hash,i*sizeof(Bloco),SEEK_SET);
	fread(bloco,sizeof(Bloco),1,hash);
	while(bloco->chaves[j]->RRN != -1){
		if(strcmp(chave,bloco->chaves[j]->indice)==0){
			(*P)(bloco->chaves[j],reg,hash);
			return;
		}
		j++;
		if(j >= TAM_BLOCO){
			i++;
			j=0;
			if(i >= NUM_INICIAL_BLOCOS){
				i=0;
			}
			fseek(hash,i*sizeof(Bloco),SEEK_SET);
			fread(bloco,sizeof(Bloco),1,hash);
		}
	}
	printf("Aluno nao encontrado\n");
	free(bloco);
}

void Imprimir(Chave* chave,FILE* reg,FILE* hash){
	Aluno aux = Carregar_registro(reg,chave->RRN);
	printf("\nNome: %s\n",aux.Nome);
	printf("Identidade: %s\n",aux.Identidade);
	printf("CPF: %s\n",aux.CPF);
	printf("Matricula: %s\n",aux.Matricula);
	printf("CRA: %.2f\n",aux.CRA);
}

void Remover(Chave* chave,FILE* reg,FILE* hash){
	Aluno aux = Carregar_registro(reg,chave->RRN);
	char nome[50];
	
	strcpy(nome,aux.Nome);
	aux.Nome[0] = '#';	
	fseek(reg,chave->RRN,SEEK_SET);
	fwrite(&aux,sizeof(Aluno),1,reg);
	int i,j=0;
	i = Hash(chave->indice);
	
	Bloco* bloco = malloc(sizeof(Bloco));
	fseek(hash,i*sizeof(Bloco),SEEK_SET);
	fread(bloco,sizeof(Bloco),1,hash);	


	while(bloco->chaves[j]->RRN != -1){
		if(strcmp(chave->indice,bloco->chaves[j]->indice)==0){
			bloco->chaves[j]->RRN = -2;
			strcpy(bloco->chaves[j]->indice,"");
			break;
		}
		j++;
		if(j >= TAM_BLOCO){
			i++;
			j=0;
			if(i >= NUM_INICIAL_BLOCOS){
				i=0;
			}
			fseek(hash,i*sizeof(Bloco),SEEK_SET);
			fread(bloco,sizeof(Bloco),1,hash);
		}
	}
	fseek(hash,i*sizeof(Bloco),SEEK_SET);
	fwrite(bloco,sizeof(Bloco),1,hash);	
	if(nome[0] !='#'){
		printf("Aluno %s removido com sucesso.\n",nome);
		numero_dis--;
		fseek(reg,sizeof(int),SEEK_SET);
		fwrite(&numero_dis,sizeof(int),1,reg);
	}

	free(bloco);
}

void Atualizar(char chave[],Aluno aluno,int tipo,FILE* reg,FILE* mat,FILE* id){
	
	Aluno aux;
	if(tipo == 1){
		aux = Carregar_registro2(chave,reg,id);
		if(aux.Nome[0] == '#'){
			printf("Registro a ser atualizado não encontrado\n");
			return;
		}
		Busca(chave,reg,id,Remover);
		Busca(aux.Matricula,reg,mat,Remover);
	}
	else{
		aux = Carregar_registro2(chave,reg,mat);
		if(aux.Nome[0] == '#'){
			printf("Registro a ser atualizado não encontrado\n");
			return;
		}
		Busca(chave,reg,mat,Remover);
		Busca(aux.Identidade,reg,id,Remover);
	}
	int RRN = Inserir_registro(aluno, reg);
	Inserir_hash(aluno,RRN,1,id);
	Inserir_hash(aluno,RRN,2,mat);
}

Aluno Carregar_registro2(char chave[],FILE*reg,FILE* arq){
	int i,j=0;
	i = Hash(chave);
	Bloco* bloco = malloc(sizeof(Bloco));
	fseek(arq,i*sizeof(Bloco),SEEK_SET);
	fread(bloco,sizeof(Bloco),1,arq);	
	
	Aluno aux;
	aux.Nome[0] = '#';

	while(bloco->chaves[j]->RRN != -1){
		if(strcmp(chave,bloco->chaves[j]->indice)==0){
			aux = Carregar_registro(reg,bloco->chaves[j]->RRN);
			//printf("mat: %s\n",aux.Matricula);
			return aux;
		}
		j++;
		if(j >= TAM_BLOCO){
			i++;
			j=0;
			if(i >= NUM_INICIAL_BLOCOS){
				i=0;
			}
			fseek(arq,i*sizeof(Bloco),SEEK_SET);
			fread(bloco,sizeof(Bloco),1,arq);	
		}
	}
	free(bloco);
	return aux;
}

void Carregar_cabecalho(FILE* arq){
	fseek(arq,0,SEEK_END);
	if(ftell(arq) <= 0){
		numero_dis = 0;
		numero_reg = 0;
	}
	else{
		fseek(arq,0,SEEK_SET);
		fread(&numero_reg,sizeof(int),1,arq);
		fread(&numero_dis,sizeof(int),1,arq);
	}
}

int Checar_existe(char chave[],FILE* arq){
	int i,j=0;
	i = Hash(chave);
	fseek(arq,0,SEEK_END);
	if(ftell(arq) == 0) return 1;
	Bloco* bloco = malloc(sizeof(Bloco));
	fseek(arq,i*sizeof(Bloco),SEEK_SET);
	fread(bloco,sizeof(Bloco),1,arq);

	while(bloco->chaves[j]->RRN != -1){
		if(strcmp(chave,bloco->chaves[j]->indice)==0){
			return 0;
		}
		j++;
		if(j >= TAM_BLOCO){
			i++;
			j=0;
			if(i >= NUM_INICIAL_BLOCOS){
				i=0;
			}
			fseek(arq,i*sizeof(Bloco),SEEK_SET);
			fread(bloco,sizeof(Bloco),1,arq);
		}
	}
		free(bloco);
		return 1;
}

int Exibir_alunos(FILE* arq){
	Aluno aluno;
	int i = 0;
	fseek(arq,2*sizeof(int),SEEK_SET);
	while(i < numero_reg){
		fread(&aluno,sizeof(Aluno),1,arq);
		if(aluno.Nome[0] != '#'){
			printf("%s %s %.2f\n",aluno.Nome,aluno.Matricula,aluno.CRA);
		}
		i++;
		//fseek(arq,sizeof(Aluno),SEEK_CUR);
	}
}
