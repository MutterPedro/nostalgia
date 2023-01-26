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

dados entrada;

typedef struct{
        int dist;
        char cor;
        int adj[2];
        int ant;
}No;

void buscaLargura(No vertices[]){
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
        for (int j = 0; j < 2; j++){
          if(vertices[vertices[i].adj[j]].cor == 'B'){
           vertices[vertices[i].adj[j]].ant = i;
           vertices[vertices[i].adj[j]].cor = 'C';
           vertices[vertices[i].adj[j]].dist = vertices[i].dist+1;
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

    if((entrada.inicio < 1) || (entrada.local > 100)
                ||  (entrada.qtdAndares > 100)
                || (entrada.inicio > entrada.qtdAndares)
                || (entrada.up < 0) || (entrada.down > 100)) {

                    cout << "Valores invalidos." << endl;
                    exit(EXIT_FAILURE);
            }


    No listaAdj[entrada.qtdAndares];
    listaAdj[0].ant = -1;
    //lista de adjascência
            for(int i=0;i<entrada.qtdAndares;i++){
                if(i == entrada.inicio-1){
                    listaAdj[i].cor = 'C';
                    listaAdj[i].dist = 0;
                }
                else{
                    listaAdj[i].cor = 'B',
                    listaAdj[i].dist = INFINITO;
                }
                if((i-entrada.down) < 0){
                    listaAdj[i].adj[0] = i + entrada.up;
                    listaAdj[i].adj[1] = 101;
                }
                else if((entrada.up+i )>= entrada.qtdAndares){
                    listaAdj[i].adj[0] = i - entrada.down;
                    listaAdj[i].adj[1] = 101;
                }

                else{
                     listaAdj[i].adj[0] = i + entrada.up;
                     listaAdj[i].adj[1] = i - entrada.down;
                }

                //cout << "["<<i+1<<"]"<< "-->" << "["<< listaAdj[i].adj[0]+1 <<"]"<< "-->" << "["<<listaAdj[i].adj[1] +1<<"]"<< endl;
            }

            buscaLargura(listaAdj);

            int arestas = listaAdj[entrada.local-1].dist;
           int verticeAtual = entrada.inicio-1;
           int caminho[arestas+1];

           cout << arestas << endl;
           caminho[0] = entrada.local-1;
           caminho[arestas] = entrada.inicio-1;

           for(int i=1;i<arestas;i++){
                caminho[i] = listaAdj[caminho[i-1]].ant;
           }

           for(int i=arestas;i>=0;i--)
                cout << caminho[i]+1 << " ";
          cout << endl;

    return 0;
}
