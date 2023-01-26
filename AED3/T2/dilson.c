/*Implementação do TAD Dicinário usando Árvore-B*/

#include "Dicionario.h"

#define ORDEM 4
#define PROMOVE 1
#define NAO_PROMOVE 0
#define CHAVE_JA_EXISTE 2
#define MIN_ITENS ((ORDEM+1)/2-1)
#define REMOCAO_NORMAL 1
#define REMOCAO_MENOR 0

/*
Estrutura para nós em uma Árvore-B
*/
struct No//Ou página 
{
	Item Itens[ORDEM-1];
	struct No* Filhos[ORDEM];
	int numItens;
};


/*
Estrutura para Árvores-B
*/
struct dicionario
{
	struct No* raiz;
};

void DIC_Destroi_Interno(struct No* r);
Item DIC_Busca_Rec(struct No* r, Chave c);
int DIC_Insere_Interno(struct No *r, Item I, Item *itemPromovido, struct No **filhoDItemPromovido);
void Divide(struct No *r, Item *itemPromovido, struct No **filhoDItemPromovido);
Item DIC_Remove_Interno(struct No **R, Chave c, int tipo);

/*
Inicializa a Árvore-B (Dicionario)
*/
Dicionario DIC_Inicializa()
{
	Dicionario D = malloc(sizeof(struct dicionario));
	D->raiz = NULL;
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

	/*IMPLEMENTAR*/
}

Item Busca_Rec(struct No *r, Chave c)
{
	if(r==NULL) return Null_Item();
	
	int i = 0;

	while(i < r->numItens && Maior(c, Get_Chave(r->Itens[i])))
		i++;

	if(i != r->numItens && Igual(c , Get_Chave(r->Itens[i])) )
		return r->Itens[i];

	return Busca_Rec(r->Filhos[i], c);
}
/*
Retorna o item de chave c no dicionaro D.
*/
Item DIC_Busca(Dicionario D, Chave c)
{
	if(!D)
	{
		printf("Dicionario nao inicializado\n");
		return Null_Item();
	}

	return DIC_Busca_Rec(D->raiz, c);
}

/*
Função interna para realização de busca.
Retorna o item de chave c na árvore de raiz r.
*/
Item DIC_Busca_Rec(struct No* r, Chave c)
{
	if(!r) return Null_Item();

	/*IMPLEMENTAR*/
}

/*
Insere o item I no dicionario D
*/
void DIC_Insere(Dicionario D, Item I)
{
	Item itemPromovido;
	struct No *filhoDItemPromovido;
	if( DIC_Insere_Interno(D->raiz, I, &itemPromovido, &filhoDItemPromovido) == PROMOVE)
	{
		struct No *aux = D->raiz;
		D->raiz = malloc(sizeof(struct No));
		D->raiz->Itens[0] = itemPromovido;
		D->raiz->Filhos[0] = aux;
		D->raiz->Filhos[1] = filhoDItemPromovido;
		D->raiz->numItens = 1;
	}
}

/*
Procedimento interno de inserção.
*/
int DIC_Insere_Interno(struct No *r, Item I, Item *itemPromovido, struct No **filhoDItemPromovido)
{
	//Se for um nó nulo, insere na página pai
	if(r == NULL)
	{
		*itemPromovido = I;
		*filhoDItemPromovido = NULL;
		return PROMOVE;
	}

	//Senão, procura o ponto i onde I deveria estar na página atual
	int i;
	for(i = 0; (i < r->numItens) && Maior(Get_Chave(I), Get_Chave(r->Itens[i])); i++);

	//Se o item I já estiver na página, retorna
	if(i < r->numItens && Igual(Get_Chave(I), Get_Chave(r->Itens[i])) )
	{
		printf("ERRO, item ja existente\n");
		return CHAVE_JA_EXISTE;
	}
	//Senão, manda inserir na página filha adequada
	int retorno = DIC_Insere_Interno(r->Filhos[i], I, itemPromovido, filhoDItemPromovido);

	//Se nenhum item for promovido da página filha, retorna
	if(retorno == NAO_PROMOVE || retorno == CHAVE_JA_EXISTE)
		return retorno;

	//Se um item for promovido e houver espaço nesta página
	if(r->numItens < ORDEM-1)
	{
		int pos = i;
		for(i = r->numItens; i > pos; i--)
		{
			r->Itens[i] = r->Itens[i-1];
			r->Filhos[i+1] = r->Filhos[i];
		} 
		r->Itens[pos] = *itemPromovido;
		r->Filhos[pos+1] = *filhoDItemPromovido;
		r->numItens++;
		return NAO_PROMOVE;
	}
	//Se não houver espaço, faz a divisão de página
	//itemPromovido será o pivô e filhoDItemPromovido será a nova página, o pivô será inserido na página pai
	Divide(r, itemPromovido, filhoDItemPromovido);
	return PROMOVE; 
}

void Divide(struct No *r, Item *itemPromovido, struct No **filhoDItemPromovido)
{
	Item Itens[ORDEM];
	struct No *Filhos[ORDEM+1];

	int i;
	for(i = 0; i < r->numItens && Menor(Get_Chave(r->Itens[i]), Get_Chave(*itemPromovido)); i++)
	{
		Itens[i] = r->Itens[i];
		Filhos[i] = r->Filhos[i];
	}

	Filhos[i] = r->Filhos[i];
	Itens[i] = *itemPromovido;
	Filhos[i+1] = *filhoDItemPromovido;
	i++;

	for(; i < ORDEM; i++)
	{
		Itens[i] = r->Itens[i-1];
		Filhos[i+1] = r->Filhos[i];
	} 

	int meio = ORDEM/2;
	*filhoDItemPromovido = malloc(sizeof(struct No));
	(*filhoDItemPromovido)->numItens = ORDEM-1-meio;
	*itemPromovido = Itens[meio];
	r->numItens = meio;
	for(i = 0; i < meio; i++)
	{
		r->Itens[i] = Itens[i];
		r->Filhos[i] = Filhos[i];
	}
	r->Filhos[i] = Filhos[i];

	int j;
	for(i = meio+1, j = 0; i < ORDEM; i++, j++)
	{
		(*filhoDItemPromovido)->Itens[j] = Itens[i];
		(*filhoDItemPromovido)->Filhos[j] = Filhos[i];
	}
	(*filhoDItemPromovido)->Filhos[j] = Filhos[i];
}

/*
Remove o item com chave c do dicionario D. Retorna o item removido.
*/
Item DIC_Remove(Dicionario D, Chave c)
{
	return DIC_Remove_Interno( &(D->raiz), c, REMOCAO_NORMAL);

	if(D->raiz->numItens == 0)
	{
		struct No *r = D->raiz;
		D->raiz = D->raiz->Filhos[0];
		free(r);
	}
}

void DIC_Imprime_Interno(struct No *r, int nivel)
{
	if(!r) return;
	int i;
	for(i = 0; i < nivel; i++) printf("   ");
	printf("[");
	for(i = 0; i < r->numItens; i++)
	{
		printf("%d ", Get_Chave(r->Itens[i]));
	}
	printf("]\n");
	for(i = 0; i <= r->numItens; i++)
	{
		DIC_Imprime_Interno(r->Filhos[i], nivel+1);	
	}
}

void DIC_Imprime(Dicionario D)
{
	DIC_Imprime_Interno(D->raiz, 0);
}

void DIC_Processa(Dicionario D, void (*P)(Item))
{
}

Item DIC_Remove_Interno(struct No **R, Chave c, int tipo)
{
	struct No *r = *R;
	if(r == NULL) return Null_Item();

	int i = 0;
	if(tipo == REMOCAO_NORMAL) 
		while(i < r->numItens && Maior(c, Get_Chave(r->Itens[i])))
			i++;

	Item I;
	if(
		(
			tipo == REMOCAO_MENOR &&
			r->Filhos[i] == NULL
		) 
		||
		(
			tipo == REMOCAO_NORMAL &&
			i < r->numItens && Igual(Get_Chave(r->Itens[i]), c)
		)
	)
	{
		//Elemento encontrado
		if(r->Filhos[i] == NULL)
		{
			//Folha
			I = r->Itens[i];
			for(++i; i < r->numItens; i++)
				r->Itens[i-1] = r->Itens[i];
			r->numItens--;
			return I;
		}

		//remove pos i
		I = r->Itens[i];
		r->Itens[i] =  DIC_Remove_Interno(&(r->Filhos[i+1]), c, REMOCAO_MENOR);
		printf("-> %d\n", r->Itens[i]->c);
		i++;
	}
	else
	{
		//Elemento não encontrado
		I = DIC_Remove_Interno(&(r->Filhos[i]), c, tipo);
	}

	if(r->Filhos[i] && r->Filhos[i]->numItens < MIN_ITENS)
	{
		if(i > 0 && r->Filhos[i-1]->numItens > MIN_ITENS)
		{
			printf("A\n");
			//Recebe um item da esquerda
			int j;
			struct No *f = r->Filhos[i];
			struct No *g = r->Filhos[i-1];
			f->Filhos[f->numItens+1] = f->Filhos[f->numItens];
			for(j = f->numItens; j > 0; j--)
			{
				f->Itens[j] = f->Itens[j-1];
				f->Filhos[j] = f->Filhos[j-1];
			}
			f->Itens[0] = r->Itens[i-1];
			f->Filhos[0] = g->Filhos[g->numItens];
			(f->numItens)++;
			r->Itens[i-1] = g->Itens[g->numItens-1];
			(g->numItens)--; 
		}
		else if(i < r->numItens && r->Filhos[i+1]->numItens > MIN_ITENS)
		{
			printf("B\n");
			//Recebe um item da direita
			int j;
			struct No *f = r->Filhos[i];
			struct No *g = r->Filhos[i+1];
	
			f->Itens[f->numItens] = r->Itens[i];
			f->Filhos[f->numItens+1] = g->Filhos[0];
			(f->numItens)++;
			r->Itens[i] = g->Itens[0];
			for(j = 1; j < g->numItens; j++)
			{
				g->Itens[i-1] = g->Itens[i];
				g->Filhos[i-1] = g->Filhos[i]; 
			}
			g->Filhos[i-1] = g->Filhos[i];
			(g->numItens)--; 
		}
		else
		{
			printf("C\n");
			//Merge
			int j, k;

			struct No *f, *g;

			if(i>0)
			{
				f = r->Filhos[i];
				g = r->Filhos[i-1];
				i--;
			}
			else
			{
				g = r->Filhos[i];
				f = r->Filhos[i+1];
			}

			g->Itens[g->numItens] = r->Itens[i];
			(g->numItens)++;
			for(j = 0; j < f->numItens; j++)
			{
				g->Itens[g->numItens] = f->Itens[j];
				g->Filhos[g->numItens] = f->Filhos[j];
				(g->numItens)++;
			}
			g->Filhos[g->numItens] = f->Filhos[j];
			free(f);
			for(; i < r->numItens-1; i++)
			{
				r->Itens[i] = r->Itens[i+1];
				r->Filhos[i+1] = r->Filhos[i+2];
			}
			r->numItens--;
		}
	}
	return I;
}



