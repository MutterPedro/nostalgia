/*Implementação do TAD Dicinário usando Árvore-B*/

#include "Dicionario.h"

#define ORDEM 4
#define MIN_ITENS ((ORDEM+1)/2-1)

/*
Estrutura para nós em uma Árvore-B
*/
typedef struct{
	char indice[50];
	int end;
}Chave;


struct No//Ou página
{
    Chave* chaves[ORDEM];
    int numItens;
    int Filhos[ORDEM];
    int pai;
    int endereco;
};

int numero_reg=0;
int numero_exc=0;



/*
Estrutura para Árvores-B
*/
struct dicionario
{
	struct No* raiz;
};

void  Destroi_Interno(struct No* r);
void Insere_Interno(struct No **R, char chave[],int pos,FILE *arq);
Alunos Remove_Interno(struct No **R, char c[], int tipo);
void Divide(struct No **R, struct No** filho1, struct No** filho2, FILE* arq);
void Carregar_Pagina(struct No** pagina, int pos, FILE *arq);
void Exibir_registros_interno(int RRN,int x,FILE* arq);

/*
Inicializa a Árvore-B (Dicionario)
*/
Dicionario Inicializa(FILE* arq){
	Dicionario D = malloc(sizeof(struct dicionario));
    D->raiz = NULL;
    //printf("sucesso\n");

    return D;
}

void Imprimir(Alunos aluno){    

    if(!aluno) return;

    printf("\nNome: %s\n",aluno->Nome);
    printf("ID: %s\n",aluno->Identidade);
    printf("CPF: %s\n",aluno->CPF);
    printf("Matricula: %s\n",aluno->Matricula);
    printf("CRA: %.2f\n",aluno->CRA);

}
int rrn_reg,rrn_indice;
Alunos Busca_interno(struct No* busca, char chave[],FILE* arq,FILE* reg){
    int i=0;

    while(i < busca->numItens){

        if(strcmp(busca->chaves[i]->indice,chave) == 0){
            Alunos aluno = malloc(sizeof(Aluno));           
            //printf("achou!!!\n");
            fseek(reg,0,SEEK_SET);
            rrn_reg = busca->chaves[i]->end;
            rrn_indice = busca->endereco;
            fseek(reg,(busca->chaves[i])->end,SEEK_CUR);
            fread(aluno,1,sizeof(Aluno),reg);
            return aluno;
        }
        if(busca->Filhos[i] != -1){
           // printf("tem filho em %d\n", i);
            if(strcmp(busca->chaves[i]->indice,chave) > 0){
                //printf("eh menor que a chave %s\n",busca->chaves[i]->indice);
                struct No* aux = malloc(sizeof(struct No));
                Carregar_Pagina(&aux,busca->Filhos[i],arq);
                return Busca_interno(aux,chave,arq,reg);
            }
            else{
                if(busca->chaves[i+1]){
                    if(strcmp(busca->chaves[i+1]->indice,chave) > 0){
                       // printf("eh menor que a chave %s\n",busca->chaves[i+1]->indice);
                        struct No* aux = malloc(sizeof(struct No));
                        Carregar_Pagina(&aux,busca->Filhos[i+1],arq);                   
                        return Busca_interno(aux,chave,arq,reg);
                    }
                }
                else if(strcmp(busca->chaves[i]->indice,chave) < 0){
                    //printf("eh maior que a chave %s\n",busca->chaves[i]->indice);
                    struct No* aux = malloc(sizeof(struct No));
                    Carregar_Pagina(&aux,busca->Filhos[i+1],arq);
                    return Busca_interno(aux,chave,arq,reg);
                }
            }
        }
        i++;
    }
        printf("Registro nao encontrado.\n");
        return NULL;

}



Alunos Busca(Dicionario D, char chave[],FILE* arq,FILE* reg){
 	if(!D){
 		printf("Arvore nula.\n");
 		return NULL;
 	}

    return Busca_interno(D->raiz, chave, arq,reg);
}


/*
Insere o Alunos I no dicionario D
*/
void Insere(Dicionario D, Alunos I,int pos,FILE *arq,int tipo){

    if(tipo == 1){
  	 Insere_Interno(&(D->raiz),I->Identidade,pos,arq);
       // printf("%s\n",D->raiz->chaves[0]->indice);
    }
    else
         Insere_Interno(&(D->raiz),I->Matricula,pos,arq);

    int endereco = D->raiz->endereco;
    free(D->raiz);
    D->raiz = malloc(sizeof(struct No));
    Carregar_Pagina(&(D->raiz),endereco,arq);
}

void ordenar_pagina(struct No** pagina){
    int ord=0;
    do{
        int j=0;
        ord=1;
        for(j=0;j<(*pagina)->numItens-1;j++){
            Chave *aux;
            if(strcmp((*pagina)->chaves[j]->indice,(*pagina)->chaves[j+1]->indice) > 0){
                aux = (*pagina)->chaves[j];
                (*pagina)->chaves[j]=(*pagina)->chaves[j+1];
                (*pagina)->chaves[j+1]=aux;
                ord=0;
            }
        }
    }while(ord==0);
    //printf("ordenando %s - %s - %s - %s.\n",(*pagina)->chaves[0]->indice,(*pagina)->chaves[1]->indice,(*pagina)->chaves[2]->indice,(*pagina)->chaves[3]->indice);
}


void Insere_Interno(struct No **R, char chave[],int pos,FILE *arq){
    //inserção na raiz
    if(!(*R)){
		(*R) = malloc(sizeof(struct No));
        (*R)->chaves[0] = malloc(sizeof(Chave));                
		strcpy((*R)->chaves[0]->indice,chave);
		(*R)->chaves[0]->end=pos;
		(*R)->numItens=0;
		(*R)->numItens++;
		(*R)->pai = -1;
		(*R)->endereco = ftell(arq);
        int i=0;

        for(;i<ORDEM-1;i++)
            (*R)->Filhos[i] = -1;
        
        fwrite((*R),sizeof(struct No),1,arq);
        return;
    }
    int c=0;
    int f=0;

    while((*R)->Filhos[f] != -1){
        int endereco = (*R)->endereco;
        free(*R);
        (*R) = malloc(sizeof(struct No));
        Carregar_Pagina(R,endereco,arq);
       //printf("pai: %s\nfilhos: %d e %d \n", (*R)->chaves[c]->indice,(*R)->Filhos[f],(*R)->Filhos[f+1]);
        if(strcmp(chave,(*R)->chaves[c]->indice) < 0){
            struct No* filho = malloc(sizeof(struct No));
            Carregar_Pagina(&filho,(*R)->Filhos[f],arq);

             Insere_Interno(&filho,chave,pos,arq);
            //printf("tem filho menor que a chave %s \n",(*R)->chaves[c]->indice);
            free(filho);
            return;
        }
        if((*R)->chaves[c+1]){
            if((strcmp(chave,(*R)->chaves[c]->indice) > 0) && (strcmp(chave,(*R)->chaves[c+1]->indice) < 0)){
                struct No* filho = malloc(sizeof(struct No));
                Carregar_Pagina(&filho,(*R)->Filhos[f+1],arq);

                 Insere_Interno(&filho,chave,pos,arq);
                //printf("tem filho maior que a chave %s e menor que a chave %s\n",(*R)->chaves[c]->indice,(*R)->chaves[c+1]->indice);
                free(filho);
                return;
            }
            else if((strcmp(chave,(*R)->chaves[c+1]->indice) > 0))
                c++;
        }
        else{
            struct No* filho = malloc(sizeof(struct No));
            Carregar_Pagina(&filho,(*R)->Filhos[f+1],arq);
            //printf("%d\n", filho->endereco);

             Insere_Interno(&filho,chave,pos,arq);
            //printf("tem filho maior que a chave %s \n",(*R)->chaves[c]->indice);
            free(filho);
            return;
        }
        f++;
    }

    //no com espaço disponivel
    if((*R)->numItens < ORDEM-1){
        //printf("inserção no disponivel\n");
        (*R)->chaves[(*R)->numItens] = malloc(sizeof(Chave));
		strcpy((*R)->chaves[(*R)->numItens]->indice,chave);
		(*R)->chaves[(*R)->numItens]->end=pos;
		(*R)->numItens++;
        //printf("%d\n", (*R)->numItens);
		ordenar_pagina(R);
	}
	
	//no cheio
	else{
        (*R)->chaves[(*R)->numItens] = malloc(sizeof(Chave));
		strcpy((*R)->chaves[(*R)->numItens]->indice,chave);  
        (*R)->chaves[(*R)->numItens]->end=pos;     
        (*R)->numItens++;  
		ordenar_pagina(R);
		struct No* filho1 = malloc(sizeof(struct No));
		struct No* filho2 = malloc(sizeof(struct No));
		Divide(R,&filho1,&filho2,arq);
		free(filho1);
		free(filho2);
        //printf("%s\n", (*R)->chaves[c]->indice);
	}
      //  printf("%d\n",(*R)->numItens);
    fseek(arq,0,SEEK_SET);
    fseek(arq,(*R)->endereco,SEEK_CUR);
    //printf("%ld\n",ftell(arq));
    fwrite((*R),sizeof(struct No),1,arq);
    
}


void Divide(struct No **R, struct No** filho1, struct No** filho2, FILE* arq){
    struct No* r = *R;
	int i=0;
	for(i=0;i<ORDEM/2;i++){
		(*filho1)->chaves[i]=r->chaves[i];
		(*filho2)->chaves[i]=r->chaves[(ORDEM/2+1)+i];
	}
        //printf("sucesso.\n");
    (*filho1)->numItens = ORDEM/2;
    (*filho2)->numItens = ORDEM/2 - 1;
    fseek(arq,0,SEEK_END);

    for(i=0;i < ORDEM;i++){
        (*filho1)->Filhos[i]=-1;
        (*filho2)->Filhos[i]=-1;
    }

    (*filho1)->endereco = ftell(arq);
    fwrite((*filho1),sizeof(struct No),1,arq);
    (*filho2)->endereco = ftell(arq);
	fwrite((*filho2),sizeof(struct No),1,arq);

	
	if(r->pai != -1){		
		(*filho1)->pai = r->pai;
		(*filho2)->pai = r->pai;

        int i=0;

		struct No* pai = malloc(sizeof(struct No));
		Carregar_Pagina(&pai,r->pai,arq);
        pai->chaves[pai->numItens] = r->chaves[ORDEM/2];
        pai->numItens++;
        ordenar_pagina(&pai);
        if(pai->numItens < ORDEM){
            //printf("pai: %s - %s - %s\n",pai->chaves[0]->indice,pai->chaves[1]->indice,pai->chaves[2]->indice);
    		for(i=pai->numItens;i<ORDEM;i++)
    			pai->chaves[i]=NULL;
            i=0;
            int acho=0;
            while((i < pai->numItens) && (acho==0)){
                if(strcmp(pai->chaves[i]->indice,(*filho1)->chaves[(*filho1)->numItens-1]->indice) > 0){
                //printf("dividindo no nao raiz\n");
                   if(pai->Filhos[i+1] != -1){
                        int j=pai->numItens;
                        while(j > i+1){
                            pai->Filhos[j] = pai->Filhos[j-1];
                            j--;
                        }
                    }
                    pai->Filhos[i] = (*filho1)->endereco;
                    pai->Filhos[i+1] = (*filho2)->endereco;
                    acho=1;
                }
                i++;
            }
            if(i == pai->numItens){
                pai->Filhos[i-1] = (*filho1)->endereco;
                pai->Filhos[i] = (*filho2)->endereco;
            }
        }
        else{
            struct No* filho3 = malloc(sizeof(struct No));
            struct No* filho4 = malloc(sizeof(struct No));
            Divide(&pai,&filho3,&filho4,arq);
            free(filho3);
            free(filho4);
        }
        
        fseek(arq,0,SEEK_SET);
        fseek(arq,pai->endereco,SEEK_CUR);
        fwrite(pai,sizeof(struct No),1,arq);
    }
	else{
		r->chaves[0]=r->chaves[ORDEM/2];

        int i;
        for(i=1;i<ORDEM;i++)
            r->chaves[i]=NULL;

        (*filho1)->pai=r->endereco;
        (*filho2)->pai=r->endereco;

        r->Filhos[0]=(*filho1)->endereco;
        r->Filhos[1]= (*filho2)->endereco;

        r->numItens = 1;

	}	
}


void Exibir_registros_ordenado(struct No* r, FILE *arq, FILE *registros){
    if(!r) return;
    int i=0;
    struct No* filho = malloc(sizeof(struct No));
    while(i < r->numItens){
        if(r->Filhos[i] != -1){
            Carregar_Pagina(&filho,r->Filhos[i],arq);
            Exibir_registros_ordenado(filho,arq,registros);
        }
        Aluno aluno;
        fseek(registros,0,SEEK_SET);
        fseek(registros,(r->chaves[i]->end),SEEK_CUR);
        fread(&aluno,1,sizeof(Aluno),registros);
        printf("\nNome: %s\n",aluno.Nome);
        printf("ID: %s\n",aluno.Identidade);
        printf("CPF: %s\n",aluno.CPF);
        printf("Matricula: %s\n",aluno.Matricula);
        printf("CRA: %.2f\n",aluno.CRA);
        i++;
    }
    if(r->Filhos[i] != -1){
        Carregar_Pagina(&filho,r->Filhos[i],arq);
        Exibir_registros_ordenado(filho,arq,registros);
    }

    
    free(filho);
}

void Exibir_registros_ordenados(Dicionario D,FILE* arq, FILE* reg){
    if(!D){
        printf("Arvore nula.\n");
        return;
    }
    Exibir_registros_ordenado(D->raiz,arq,reg);
}

void Exibir_registros_interno(int RRN,int x,FILE* arq){
    struct No* P = malloc(sizeof(struct No));
    Carregar_Pagina(&P,RRN,arq);
    int i=0;
    for(;i < 3*x;i++){
        printf(" ");
    }
    for(i=0;i < P->numItens;i++){
        printf("%s ", P->chaves[i]->indice);
    }
    printf("\n");
    for(i=0; i<= P->numItens; i++){
        if(P->Filhos[i] !=-1)
            Exibir_registros_interno(P->Filhos[i],x+1,arq);
    }
    free(P);
}

void Exibir_registros(Dicionario D,FILE *arq){
    if(!D->raiz){
        printf("Raiz nula\n");
        return;
    }
    //printf("%d\n", D->raiz->endereco);
    Exibir_registros_interno(0,0,arq);
}

void Carregar_Pagina(struct No** pagina, int pos, FILE *arq){
    fseek(arq,0,SEEK_SET);
    fseek(arq,pos,SEEK_CUR);
    //printf("sucesso\n");
    fread(*pagina,1,sizeof(struct No),arq);
}

int Inserir_registro(Alunos aluno, FILE *arq){
    numero_reg++;
    fseek(arq,0,SEEK_SET);
    fwrite(&numero_reg,sizeof(int),1,arq);
    fwrite(&numero_exc,sizeof(int),1,arq);
    fseek(arq,0,SEEK_END);
    int x=ftell(arq);
    fwrite(aluno,sizeof(Aluno),1,arq);  
    return x; 
}

void Remove_Interno(struct No** no, char chave[],FILE* arq){

    
    if((*no)->numItens > MIN_ITENS)){
        //1º caso
        if((*no)->Filhos[0] == -1)){
            int i=0;
            while((*no)->chaves[i]->indice != chave) i++;
            if(i < (*no)->numItens-1) (*no)->chaves[i] = (*no)->chaves[(*no)->numItens-1];
            (*no)->chaves[(*no)->numItens-1] = NULL;
            (*no)->numItens--;
            ordenar_pagina(no);
            fseek(arq,(*no)->endereco,SEEK_SET);
            fwrite((*no),1,sizeof(struct No),arq);
            return;
        }
        //2ª caso
        else{
            int i=0;
            while((*no)->chaves[i]->indice != chave) i++;
            struct No* aux = malloc(sizeof(struct No));
            Carregar_Pagina(&aux,(*no)->Filhos[i],arq);
            Chave* c = aux->chaves[aux->numItens-1];
            aux->chaves[aux->numItens-1] = NULL;
            (*no)->chaves[i] = c;
            fseek(arq,(*no)->endereco,SEEK_SET);
            fwrite((*no),1,sizeof(struct No),arq);
            fseek(arq,aux->endereco,arq);
            fwrite(aux,1,sizeof(struct No),arq);
            free(aux);
            return;
        }
    }

}

Alunos Remove(Dicionario D, char chave[], FILE* arq, FIL* reg){
    Alunos aluno = Busca_interno(D->raiz,chave,arq,reg);
    if(!aluno) return;

    struct No* aux = malloc(sizeof(struct No));
    fseek(arq,rrn_indice,SEEK_SET);
    fread(aux,1,sizeof(struct No),arq);
    Remove_Interno(&(aux),chave,arq);

}

