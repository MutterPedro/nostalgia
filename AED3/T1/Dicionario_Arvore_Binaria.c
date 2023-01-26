/*
Implementado por Dilson Lucas Pereira - DCC/UFLA

Implementação para o tipo dicionário usando árvore binária de busca. Assume-se que o cliente fornece um tipo Item por meio da interface Item.h.
*/

#include "Dicionario.h"

/*
Estrutura para nós em uma ABB
*/
struct No 
{
	Item I;
	struct No *esq, *dir;
};

/*
Estrutura para ABBs
*/
struct dicionario
{
	struct No* raiz;
};

int ma=0;
Item maior,maiores[10];


//Declarações de funções internas
void DIC_Destroi_Interno(struct No* r);
Item DIC_Busca_Rec(struct No* r, char c[]);
struct No* Novo(Item I, struct No *esq, struct No *dir);
void Insere_ou_Processa_Interno(struct No** R, Item I);
void DIC_Remove_Interno(struct No **R, char c[], Item *I);
void DIC_Remove_Maior(struct No **R, Item *I);
void DIC_Processa_In_Ordem(struct No *r, void (*P)(Item));

/*
Inicializa a ABB (Dicionario)
*/
Dicionario DIC_Inicializa()
{
	Dicionario D = malloc(sizeof(struct dicionario));
	D->raiz = NULL;
}

/*
Cria um novo nó
*/
struct No* Novo(Item I, struct No *esq, struct No *dir)
{
	struct No* n = malloc(sizeof(struct No));
	n->I = I;
        n->I->cont=0;
	n->esq = esq;
	n->dir = dir;
	return n;
}

/*
Desaloca o dicionario
*/
void DIC_Destroi(Dicionario D)
{
	DIC_Destroi_Interno(D->raiz);
}

/*
Procedimento de desalocação recursivo.
*/
void DIC_Destroi_Interno(struct No* r)
{
	if(!r) return;

	DIC_Destroi_Interno(r->esq);
	DIC_Destroi_Interno(r->dir);
	free(r);
}

/*
Retorna o item de chave c no dicionaro D.
*/
Item DIC_Busca(Dicionario D, char c[])
{
	if(!D)
	{
		printf("Dicionario nao inicializado\n");
		return Null_Item();
	}

	DIC_Busca_Rec(D->raiz, c);
}

/*
Função interna para realização de busca.
Retorna o item de chave c na árvore de raiz r.
*/
Item DIC_Busca_Rec(struct No* r, char c[])
{
	if(!r) return Null_Item();

	char d[50];
        strcpy(d,r->I->c);
        int valor = strcasecmp(d,c);
        
	if( valor > 0 )
		return DIC_Busca_Rec(r->dir, c);
	else if( valor < 0)
		return DIC_Busca_Rec(r->esq, c);
	else
		return r->I;
}

/*
Insere o item I no dicionario D
*/
void Insere_ou_Processa(Dicionario D, Item I)
{
	Insere_ou_Processa_Interno( &(D->raiz), I );
}

/*
Procedimento interno de inserção.
*/
void Insere_ou_Processa_Interno(struct No** R, Item I)
{
        
	struct No *r = *R;
        
        
	//Encontrou o ponto de inserção
	if(r == NULL)
	{
            *R = Novo(I, NULL, NULL);
            return;
	}
        
        int valor = strcasecmp(r->I->c,I->c);
        
        //Se a chave do item do nó for igual ao item de inserção, o contador somara
        if(valor == 0){
            r->I->cont++;            
            free(I);
            return;
        }


	//Inserção à esquerda
	if( valor < 0)
	{
		Insere_ou_Processa_Interno( &(r->esq), I );
		return;
	}

	//Inserção à direita
 	if( valor > 0 )
	{
		Insere_ou_Processa_Interno( &(r->dir), I );
		return;
	}

}

/*
Remove o item com chave c do dicionario D. Retorna o item removido.
*/
Item DIC_Remove(Dicionario D, char c[])
{
	Item I;
	DIC_Remove_Interno( &(D->raiz), c, &I);
	return I;
}

/*
Remove o item de chave c da sub-árvore *R, armazena o item removido em I.
*/
void DIC_Remove_Interno(struct No **R, char c[], Item *I)
{
	struct No *r = *R;
        int valor = strcasecmp(r->I->c,(*I)->c);
        
	/*Item não encontrado*/
	if(r == NULL)
	{ 
		*I = Null_Item(); 
		return;  
	}

	/*Remoção à esquerda*/
	if( valor < 0 )
	{
		DIC_Remove_Interno( &(r->esq), c, I );
		return;
	}
	
	/*Remoção à direita*/
	if( valor > 0 )
	{
		DIC_Remove_Interno( &(r->dir), c, I );
		return;
	}

	/*Item encontrado*/
	*I = r->I;
	/*Nó sem filhos*/
	if(r->esq == NULL && r->dir == NULL)
	{
		free(r);
		*R = NULL;
		return;
	}
	/*Nó com apenas um filho, à direita*/
	if(r->esq == NULL)
	{
		free(r);
		*R = r->dir;
		return;
	}
	/*Nó com apenas um filho, à esquerda*/
	if(r->dir == NULL)
	{
		free(r);
		*R = r->esq;
		return;
	}

	DIC_Remove_Maior(&(r->esq), &(r->I));
}

/*
Remove o item de maior chave da sub-árvore *R, armazena o item em I
*/
void DIC_Remove_Maior(struct No **R, Item *I)
{
	struct No *r = *R;

	/*sub-árvore vazia*/
	if(!r){ *I = Null_Item(); return;}
	/*Se r tem filho à direita, o maior está naquela sub-árvore*/
	if(r->dir){ DIC_Remove_Maior( &(r->dir), I ); return; }

	/*Maior elemento encontrado*/
	/*Armazena o item*/
	*I = r->I;
	/*Desaloca r*/
	free(r);
	/*Altera o ponteiro que apontava para r para seu filho à esquerda*/
	*R = r->esq;
}

void DIC_Imprime_Interno2(struct No *r, int profundidade)
{
	int i,j;
	for(i = 0; i < 2; i++)
	{	
		for(j = 0; j < profundidade; j++)
		{
			printf("   |");
		}
		printf("\n");
	}
	for(j = 0; j < profundidade-1; j++)
	{
		printf("   |");
	}
	if(!r)
	{	

		printf("   +---x\n");
	}
	else
	{
		if(profundidade == 0)
			printf("+---( ");
		else
			printf("   +---( ");
		Escreve(r->I);
		printf(")\n");
		DIC_Imprime_Interno2(r->dir, profundidade+1);
		DIC_Imprime_Interno2(r->esq, profundidade+1);
	}

}
void DIC_Imprime_Interno(struct No *r)
{
	if(r == NULL) return;

	Escreve(r->I);
	DIC_Imprime_Interno(r->esq);
	DIC_Imprime_Interno(r->dir);
}

void DIC_Imprime(Dicionario D)
{
	DIC_Imprime_Interno2(D->raiz, 0);
	printf("\n********************\n");
}


void DIC_Processa(Dicionario D, void (*P)(Item))
{
	DIC_Processa_In_Ordem(D->raiz, P);
}

void DIC_Processa_In_Ordem(struct No *r, void (*P)(Item))
{
	if(!r) return;
	DIC_Processa_In_Ordem(r->esq, P);
	(*P)(r->I);
	DIC_Processa_In_Ordem(r->dir, P);
}

 void DIC_Mais_Repete_Interno(struct No* r){
    if(!r) return;
    if(r->I->cont > ma){
        ma=r->I->cont;
        maior=r->I;        
    }
    DIC_Mais_Repete_Interno(r->esq);
    DIC_Mais_Repete_Interno(r->dir);
}

void DIC_Mais_Repete(Dicionario D){
    struct No* r = D->raiz;
    int i=0;
    printf("Os 10 que mais repetiram foram:\n\n");
    for(;i<10;i++){
        ma=0;
        DIC_Mais_Repete_Interno(r);
        maiores[i]=maior;
        int aux=maior->cont;
        maior->cont=-1;
        printf("%s: %d repetições\n",maiores[i]->c,aux);
    }
}