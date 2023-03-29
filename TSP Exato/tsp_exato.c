#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_NODOS 11

int main(){

    SetConsoleOutputCP(65001);

    /*
     * Abertura do arquivo para abrir um arquivo
     * diferente, basta alterar o parâmetro do fopen();
     */

    FILE *fptr;
    fptr = fopen("tsp1_253.txt", "r");

    int matriz_adj[NUM_NODOS][NUM_NODOS];
    int buffer;

    for(int i = 0; i < NUM_NODOS; i++){
        for(int j = 0; i<NUM_NODOS; j++){
            fscanf(fptr, "%d", &buffer);
            matriz_adj[i][j] = buffer; 
        }
    }


    printf("Hello World ã");
    return 0;
}
