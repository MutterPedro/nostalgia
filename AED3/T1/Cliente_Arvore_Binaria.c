#include "Item.h"
#include "Dicionario.h"

int main(int argc, char **argv)
{
	Dicionario D = DIC_Inicializa();
        FILE *arq;
        
        arq = fopen(argv[1],"r");
        while (!feof(arq)) {
            Registro* i = malloc(sizeof(Registro));
            char* pointer;
            fscanf(arq, "%s", i->c);
            pointer = strtok(i->c, "!?.,:;+-*/^~<>=()[]{}\\|_'\"@#$%&");

            while (pointer != NULL) {
                strcpy(i->c, pointer);                
                pointer = strtok(NULL, "!?.,:;+-*/^~<>=()[]{}\\|_'\"@#$%&");
            }           
            Insere_ou_Processa(D,i);
        }
        fclose(arq);
        DIC_Mais_Repete(D);
        
        
        return 0;
}
