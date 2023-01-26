#include <iostream>
#include <stdlib.h>
#define INFINITO 99999
using namespace std;

typedef struct
{
	int qtdAndares; //f
	int inicio;//s
	int local;//g
	int up;//u
	int down;//d
}dados;

typedef struct{
        int dist;
        char cor;
        int ant;
}No;

dados entrada;

void buscaLargura(No vertices[],int** matrizAdj){
    int cont = 0;
    do{
        int i =0;
        while(vertices[i].cor != 'C' && i < entrada.qtdAndares){
            i++;
        }
        if(i == entrada.qtdAndares){
            cout << "Use as escadas." << endl;
            exit(EXIT_FAILURE);
        }
        vertices[i].cor = 'P';
        cont++;

        for(int j=0;j<entrada.qtdAndares;j++){
            if(matrizAdj[i][j]==1 && vertices[j].cor == 'B'){
                vertices[j].ant = i;
                vertices[j].cor = 'C';
                vertices[j].dist = vertices[i].dist+1;
            }
        }
    }while(cont < entrada.qtdAndares);
}

int main(){

	cin>>entrada.qtdAndares;
	cin>>entrada.inicio;
	cin>>entrada.local;
	cin>>entrada.up;
	cin>>entrada.down;

            int **matriz;

            if((entrada.inicio < 1) || (entrada.local > 100)
                || (entrada.qtdAndares > 100)
                || (entrada.inicio > entrada.qtdAndares)
                || (entrada.up < 0) || (entrada.down > 100)) {

                    cout << "Valores invalidos." << endl;
                    exit(EXIT_FAILURE);
            }

            matriz = (int**)malloc(entrada.qtdAndares*sizeof(int*));
            for(int i = 0; i<entrada.qtdAndares; i++){
                 matriz[i] = (int*)malloc(entrada.qtdAndares*sizeof(int));
            }

           No vertices[entrada.qtdAndares];

	for(int i=0; i <entrada.qtdAndares; i++){
		for (int j= 0; j <entrada.qtdAndares; j++){
	               matriz[i][j]=0;
		}
                       if(i==entrada.inicio-1){
                            vertices[i].cor = 'C';
                            vertices[i].dist = 0;
                            vertices[i].ant = -1;
                      }
                        else{
                            vertices[i].dist = INFINITO;
                            vertices[i].cor = 'B';
                      }
	}

	int a,b;
	for(int i=0; i < entrada.qtdAndares; i++){
		matriz[i][i] = 2;
		a = i + entrada.up;// posição a frente
		b = i-entrada.down; // abaixo
                      if( a <entrada.qtdAndares ){
                         matriz[i][a] = 1;
                      }
                      if(b>=0  ){
                        matriz[i][b] = 1;
                       }
	}

           /* for(int i=0;i<entrada.qtdAndares;i++){
                for (int j= 0; j < entrada.qtdAndares; j++)
                {
                    cout << matriz[i][j] << " " ;
                }
                cout<< endl;
            }*/

           buscaLargura(vertices,matriz);

           int arestas = vertices[entrada.local-1].dist;
           int verticeAtual = entrada.inicio-1;
           int caminho[arestas+1];

           cout << arestas << endl;
           caminho[0] = entrada.local-1;
           caminho[arestas] = entrada.inicio-1;

           for(int i=1;i<arestas;i++){
                caminho[i] = vertices[caminho[i-1]].ant;
           }

           for(int i=arestas;i>=0;i--)
                cout << caminho[i]+1 << " ";
          cout << endl;

	return 0;



}
