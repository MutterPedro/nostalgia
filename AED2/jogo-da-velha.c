#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MAX 3


char tab[9];
int i,j;

typedef struct Jogada{ //struct que representa as jogadas, contendo uma flag para definir quem ganhou, o numero de jogadas e a ordem das jogadas.
    int venceu;
    int numjo;
    int jogadas[9];
}Jogada;

typedef struct Nodo{ 
    struct Jogada jogo;
    struct Nodo *pProximo;
}Nodo;

struct Nodo *hashtable[MAX]; 

int hash(struct Nodo *pNodo){ //função hash que define o nivel de dificuldade de cada jogada pelo seu número de jogadas.
    int pos;
    if(pNodo->jogo.numjo<=5){
        pos=2;
    }
    else if(pNodo->jogo.numjo<=7){
        pos=1;
    }
    else{
        pos=0;
    }
    
    return pos;
}

void inserir(struct Nodo *pNodo, struct Nodo *pInicio){ //função inserir que insere em na hashtable e encadea se já houver jogadas no local.
    if(pInicio==NULL){
        hashtable[hash(pNodo)]=pNodo;
        hashtable[hash(pNodo)]->pProximo=NULL;
    }
    else{
        struct Nodo *pAux=pInicio;
        while(pAux->pProximo!=NULL){
            pAux=pAux->pProximo;
        }
        pAux->pProximo=pNodo;
        pNodo->pProximo=NULL;
    }
}

int impopar(){ //função que defini um numero aleatorio e retorna 1 se ele for impar, 0 se for par.
    int x;
    srand( (unsigned)time(NULL) );
    x=rand()%100;
    if(x%2==0)
        x=0;
    else
        x=1;
    
    return x;
}

int vencer(){ //função que percorre o tabuleiro e retorna 1 se houver um ganhador, 0 se o jogo n estiver terminado e 2 caso houver um empate.
    int pos[3];
    int velha=1;
    FILE *arq;
    arq = fopen("casos.txt", "r");
    while(!feof(arq)){
        fscanf(arq,"%i%*c",&pos[0]);
        fscanf(arq,"%i%*c",&pos[1]);
        fscanf(arq,"%i%*c",&pos[2]);
        if((tab[pos[0]]==tab[pos[1]]) && (tab[pos[0]]==tab[pos[2]]) && (tab[pos[0]]!=' ')){
            return 1;
        }
    }
    fclose(arq);
    i=0;
    while((velha==1)&&(i<9)){
        if(tab[i]==' '){
            velha=0;
        }
        i++;
    }
    if(velha==1){
        return 2;
    }
 
    return 0;
    
} 

int main(){
    
   
int op=0,venceu=0,comeca,dnv; 
int dois;
int pos,vez=0,jgds=0;
int dificuldade=1;
struct Jogada jogada;
struct Nodo *pVetor[100];
char peca[2];
int conte[3],percent[3];
struct Nodo *pNodo;

srand( time( NULL));

for(i=0;i<MAX;i++){
    hashtable[i]=NULL;
}

FILE *arq;
arq = fopen("jogadas.txt",  "r"); // abre o arquivo

while(!feof(arq)){ // lê o arquivo e inserre na hashtable de acordo com o numero de jogadas (dificuldade)
    struct Nodo *pNodo = malloc(sizeof(struct Nodo));
    fscanf(arq,"%i%*c",&pNodo->jogo.numjo);
    fscanf(arq,"%i%*c",&pNodo->jogo.venceu);
    for(i=0;i<pNodo->jogo.numjo;i++){
        fscanf(arq,"%i%*c",&pNodo->jogo.jogadas[i]);
    }
    inserir(pNodo,hashtable[hash(pNodo)]);
}
        

do{  // MENU principal
    printf("\t\t\tJOGO DA VELHA\n");
    printf("1 - Player x Player.\n");
    printf("\n2 - Player x Computer.\n");
    printf("\n3 - Computer x Computer.\n");
    printf("\n4 - Estatisticas de dificuldades.\n");
    printf("\n0 - Para sair do programa.\n");
    scanf("%d",&op);
    switch(op){
        case 1:        
        vez=0; 
        jgds=0;
        for(j=0;j<9;j++){
                tab[j]=' ';
        } 

        do{
            for(i=0;i<9;i++){ // cria o tabuleiro
              printf("[ %c ] ",tab[i]);
              if((i+1)%3==0)  {
                printf("\n");
              }
            }
            pos=0;
            while((pos>9) || (pos<1) || (tab[pos-1]!=' ')){ // confere se a posição digitada existe e está desocupada
                scanf("%d",&pos);
                if(tab[pos-1]!=' '){
                    if((pos>9) || (pos<1)){
                        printf("Posição Invalida, digite novamente.\n");
                    }
                    else{
                        printf("Posição ja esta ocupada, digite novamente.\n");
                    }
                }
            }
            jogada.jogadas[jgds]=pos-1; // marca casa
            jgds++; // contador de jogadas
            if(vez%2==0){
                tab[pos-1]='O';
            }
            else{
                tab[pos-1]='X';
            }
            vez++;
            venceu=vencer(); //verifica se houve vencedor
        }while(venceu==0);
        for(i=0;i<9;i++){
            printf("[ %c ] ",tab[i]);
            if((i+1)%3==0)  {
              printf("\n");
            }
        }
        jogada.numjo=jgds;
        if(venceu==1){ // define o vencedor
            if(vez%2==0){
                printf("O vencedor foi o Player 2.\n");
                jogada.venceu=0;
              
            }
            else{
                printf("O vencedor foi o Player 1.\n");
                jogada.venceu=1;
                }
            jogada.numjo=jgds;
            FILE *arq; 
            
            arq=fopen("jogadas.txt","a"); // abre o arquivo.          
            
            fprintf(arq,"%d\n",jogada.numjo);// salva a jogada.
            fprintf(arq,"%d\n",jogada.venceu);
            for(i=0;i<jgds;i++){                
                fprintf(arq,"%d ",jogada.jogadas[i]);
            }
            fprintf(arq,"\n"); 
            
            
            fclose(arq);
            
        }
        else{
            printf("O jogo empatou.\n");
        }
        
       
        printf("Digite 1 para jogar novamente, ou 0 para sair.\n");
        scanf("%d",&dnv);
        if(dnv==0){
            op=0;
        }
        else{
            system("clear");
        }
        break;
        
        case 2:            
            while((dificuldade>0) && (dificuldade<4)){
                printf("Escolha uma dificuldade.\n");
                printf("1 - Fácil.\n");
                printf("2 - Medio.\n");
                printf("3 - Dificil.\n");
                scanf("%d",&dificuldade);
                dois=2;
                
                for(i=0;i<100;i++){
                    pVetor[i]=NULL;// define nulo em todas posições do vetor que receberá as jogadas
                }
                
                struct Nodo *pAux=hashtable[dificuldade-1];// ponteiro auxiliar que recebe o inicio relativo a dificuldade
                int cont=0;
                i=0;
                while((pAux != NULL) && (cont<100)){ // vetor recebe as jogadas da hashtable
                    pVetor[i]=pAux;
                    pAux=pAux->pProximo;
                    i++;
                    cont++;
                }
            
                int index=cont/2,aux,done; //ordenaçao das jogadas pelo metodo shellsort
                do{
                    done=0;
                    for(i=0;i<cont-index;i++){
			if(pVetor[i]->jogo.numjo > pVetor[i+index]->jogo.numjo){
                            aux=pVetor[i]->jogo.numjo;
                            pVetor[i]->jogo.numjo=pVetor[i+index]->jogo.numjo;
                            pVetor[i+index]->jogo.numjo=aux;
                            done=1;
			}
                    }
                if(index>1)
                    index/=2;
            
                }while(done==1);
                
                while((dois!=1)&&(dois!=0)){ // definir na sorte quem começa atraves da fuçao impopar
                        printf("0 ou 1?\n");
                        scanf("%d",&dois);
                }
                        comeca=impopar();
                        if(comeca==dois){ 
                            printf("O jogador começa.\n");                      
                            peca[0]='O';
                            peca[1]='X';
                            vez=0;
                        }
                        else{ 
                            printf("O computador começa.\n");
                            peca[0]='X';
                            peca[1]='O';
                            vez=1;
                        }
                        
                        jgds=0;
                        for(j=0;j<9;j++){
                            tab[j]=' ';
                        } 

                        do{
                            if(vez%2==0){  
                                for(i=0;i<9;i++){
                                    printf("[ %c ] ",tab[i]);
                                    if((i+1)%3==0)  {
                                        printf("\n");
                                    }
                                }
                                pos=0;
                                while((pos>9) || (pos<1) || (tab[pos-1]!=' ')){
                                    scanf("%d",&pos);
                                    if(tab[pos-1]!=' '){
                                        if((pos>9) || (pos<1)){
                                            printf("Posição Invalida, digite novamente.\n");
                                        }
                                        else{
                                            printf("Posição ja esta ocupada, digite novamente.\n");
                                        }
                                    }
                                }
                                jogada.jogadas[jgds]=pos-1;
                                tab[pos-1]=peca[0];
                            }
                            else{
                                int aux;
                                int found=0;
                                if(peca[1]=='O')
                                    aux=1;
                                else
                                    aux=0;
                                
                                i=0;
                                while((pVetor[i]!=NULL) && (found==0)){//enquanto o vetor não for nulo e não encontrar uma jogada compativel,continuará o laço 
                                    if(pVetor[i]->jogo.venceu==aux){// se a jogada teve como ganhador na ordem que o computador está jogando, entrará na condiçao
                                        if(tab[pVetor[i]->jogo.jogadas[jgds]]==' '){// se o tabuleiro nessa casa estiver livre, marcará essa casa
                                            tab[pVetor[i]->jogo.jogadas[jgds]]=peca[1];
                                            found=1;
                                            jogada.jogadas[jgds]=pVetor[i]->jogo.jogadas[jgds];
                                        }
                                    }
                                    i++;  
                                }
                                if(found==0){ // jogada random, caso não encontre jogadas compativeis
                                    do{
                                       found=rand()%9;                                     
                                    }while(tab[found]!=' ');
                                    tab[found]=peca[1];
                                    jogada.jogadas[jgds]=found;
                                    }
                                
                                }
                         vez++;
                         jgds++;
                         venceu=vencer();
                        }while(venceu==0);
                        
                        for(i=0;i<9;i++){
                            printf("[ %c ] ",tab[i]);
                            if((i+1)%3==0)  {
                              printf("\n");
                            }
                        }
                            
                        if(venceu==1){
                            if(vez%2==0){
                                printf("O vencedor foi o Computador.\n");
                                if(peca[1]=='O')
                                    jogada.venceu=1;
                                else
                                    jogada.venceu=0;
                            }
                            else{
                                printf("O vencedor foi o Player.\n");
                                if(peca[0]=='O')
                                    jogada.venceu=1;
                                else
                                    jogada.venceu=0;
                            }
                        jogada.numjo=jgds;
                        FILE *arq;

                        arq=fopen("jogadas.txt","a");          

                        fprintf(arq,"%d\n",jogada.numjo);
                        fprintf(arq,"%d\n",jogada.venceu);
                        for(i=0;i<jgds;i++){
                            fprintf(arq,"%d ",jogada.jogadas[i]);
                        }
                        fprintf(arq,"\n");                       

                        fclose(arq);

                    }
                    else{
                        printf("O jogo empatou.\n");
                    }

                    int dnv;
                    printf("Digite 1 para jogar novamente, ou 0 para sair.\n");
                    scanf("%d",&dnv);
                    if(dnv==0){
                        op=0;
                        dificuldade=0;
                    }
                    else{
                        system("clear");
                    }                                                                                     
                               
            }            
            break;
            
        case 3:                              
            while((dificuldade>0) && (dificuldade<4)){
                printf("Escolha uma dificuldade.\n");
                printf("1 - Fácil.\n");
                printf("2 - Medio.\n");
                printf("3 - Dificil.\n");
                scanf("%d",&dificuldade);
                
                vez=0; 
                jgds=0;
                    
                for(i=0;i<100;i++){
                    pVetor[i]=NULL;
                }
                
                struct Nodo *pAux=hashtable[dificuldade-1];
                int cont=0;
                i=0;
                while((pAux != NULL) && (cont<100)){
                    pVetor[i]=pAux;
                    pAux=pAux->pProximo;
                    i++;
                    cont++;
                }
            
                int index=cont/2,aux,done;
                do{
                    done=0;
                    for(i=0;i<cont-index;i++){
			if(pVetor[i]->jogo.numjo > pVetor[i+index]->jogo.numjo){
                            aux=pVetor[i]->jogo.numjo;
                            pVetor[i]->jogo.numjo=pVetor[i+index]->jogo.numjo;
                            pVetor[i+index]->jogo.numjo=aux;
                            done=1;
			}
                    }
                if(index>1)
                    index/=2;
            
                }while(done==1);
                
                for(j=0;j<9;j++){
                        tab[j]=' ';
                } 

                do{                  
                   
                    char comp;
                    if(vez%2==0){
                        comp='O';
                    }
                    else{
                        comp='X';
                    }
                    int aux;
                    int found=0;
                  

                    if(vez%2==0)
                        aux=1;
                    else
                        aux=0;
                    
                    i=0;
                    while((i<cont) && (found==0)){
                        if(pVetor[i]->jogo.venceu==aux){
                            if(tab[pVetor[i]->jogo.jogadas[jgds]]==' '){
                                tab[pVetor[i]->jogo.jogadas[jgds]]=comp;
                                found=1;
                                jogada.jogadas[jgds]=pVetor[i]->jogo.jogadas[jgds];
                            }
                        }
                        i++;  
                        }
                    if(found==0){
                        do{
                            found=rand()%9;                                     
                        }while(tab[found]!=' ');
                        tab[found]=comp;
                        jogada.jogadas[jgds]=found;
                    }
                    
                    for(i=0;i<9;i++){
                      printf("[ %c ] ",tab[i]);
                      if((i+1)%3==0)  {
                        printf("\n");
                      }
                    }
                    printf("\n");
                    sleep(2);

                    vez++;
                    venceu=vencer();
                    jgds++;
                }while(venceu==0);
                
                jogada.numjo=jgds;
                if(venceu==1){
                    if(vez%2==0){
                        printf("O vencedor foi o Computador 2.\n");
                        jogada.venceu=0;

                    }
                    else{
                        printf("O vencedor foi o Computador 1.\n");
                        jogada.venceu=1;
                        }
                    FILE *arq;

                    arq=fopen("jogadas.txt","a");          

                    fprintf(arq,"%d\n",jogada.numjo);
                    fprintf(arq,"%d\n",jogada.venceu);
                    for(i=0;i<jgds;i++){                
                        fprintf(arq,"%d ",jogada.jogadas[i]);
                    }
                    fprintf(arq,"\n");


                    fclose(arq);

                }
                else{
                    printf("O jogo empatou.\n");
                }

                int dnv;
                printf("Digite 1 para jogar novamente, ou 0 para sair.\n");
                scanf("%d",&dnv);
                if(dnv==0){
                    op=0;
                    dificuldade=0;
                }
                else{
                    system("clear");
                }
            }
            break;
            
        case 4:
            for(i=0;i<3;i++){
                conte[i]=0;
                percent[i]=0;
            }
            for(i=0;i<3;i++){
                pNodo=hashtable[i];
                while(pNodo!=NULL){
                    if(pNodo->jogo.venceu == 1)
                        percent[i]++;
                    pNodo=pNodo->pProximo;
                    conte[i]++;
                }
            }
            printf("\nNúmero de jogadas do nivel fácil: %d",conte[0]);
            printf("\nO primeiro a jogar ganhou %d%% das vezes.",percent[0]*100/conte[0]);
            printf("\nO segundo a jogar ganhou %d%% das vezes.\n",100-(percent[0]*100/conte[0]));
            
            printf("\nNúmero de jogadas do nivel medio: %d",conte[1]);
            printf("\nO primeiro a jogar ganhou %d%% das vezes.",percent[1]*100/conte[1]);
            printf("\nO segundo a jogar ganhou %d%% das vezes.\n",100-(percent[1]*100/conte[1]));
            
            printf("\nNúmero de jogadas do nivel dificil: %d",conte[2]);
            printf("\nO primeiro a jogar ganhou %d%% das vezes.",percent[2]*100/conte[2]);
            printf("\nO segundo a jogar ganhou %d%% das vezes.\n",100-(percent[2]*100/conte[2]));
            
            
                printf("Digite 1 para voltar ao menu, ou 0 para sair.\n");
                scanf("%d",&dnv);
                if(dnv==0){
                    op=0;                    
                }
                else{
                    system("clear");
                }
            
            break;
        
    }
}while(op!=0);

struct Nodo *pAux,*pUltimo;
for(i=0;i<3;i++){
    pUltimo=hashtable[i];
    while(pUltimo!=NULL){
        pAux=pUltimo;
        pUltimo=pUltimo->pProximo;
        free(pAux);
    }
}
        
return 0;
}
