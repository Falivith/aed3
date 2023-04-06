#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <windows.h>

/* Contagem de Nodos
 *  TSP 0: 5
 *  TSP 1: 11
 *  TSP 2: 6
 *  TSP 3: 15
 *  TSP 4: 44
 *  TSP 5: 29
 */

#define n_nodos 11
using namespace std;

class bruteforce {

public:

  string menor_caminho_soma(int matriz_adj[n_nodos][n_nodos], int num_nodos) {

    vector<int> nodos;
    vector<int> percorridos;

    int inicio = 0;

    // Armazena no ArrayList todos nodos exceto o inicial (por padrão 0, ou nodo 1)

    for (int i = 0; i < num_nodos; i++) {
      if (i != inicio) {
        nodos.push_back(i);
      }
    }

    int n = nodos.size();
    int menor_caminho = INT_MAX;

    // Todas as permutações desse vetor vão ser testadas a partir do nodo início (tanto faz o nodo início)


    do {
      //for (int i = 0; i < nodos.size(); i++) { cout << nodos[i] << " "; } cout << endl;

      int soma_peso = 0;
      int nodo_atual = inicio;

      /* Cálculo do peso do caminho:
       * São somados os pesos das arestas
       * referentes a permutação atual do
       * grafo. Se numa matriz [5][5] temos 
       * a permutação 1 3 2 4, saímos do 0
       * e somamos o peso de 0 com 1, 1 com 3,
       * 3 com 2 e 2 com 4. Assim temos o
       * resultado da permutação. */

      for (int i = 0; i < n; i++) {
        soma_peso += matriz_adj[nodo_atual][nodos[i]];
        nodo_atual = nodos[i];
      }

      // Por fim, soma-se o peso do último nodo da permutação até o nodo inicial, fechando o ciclo hamiltoniano.
      soma_peso += matriz_adj[nodo_atual][inicio];

      if(soma_peso < menor_caminho){
        percorridos = nodos;
        menor_caminho = soma_peso;
      }
        

    } while (next_permutation(nodos.begin(), nodos.end()));

    string resposta = to_string(menor_caminho);
    string solucao = "[";

    percorridos.push_back(inicio);
    percorridos.insert(percorridos.begin(), inicio);

    for (int i = 0; i < percorridos.size(); i++) {
      percorridos[i]++;
      solucao += to_string(percorridos[i]) + " ";
    }
    
    solucao.pop_back();
    solucao += "]";

    resposta = "Os nodos percorridos foram: " + solucao + ", e o peso total do caminho é: " + resposta; 

    return resposta;
  }
};

int main() {

  SetConsoleOutputCP(65001);
  ifstream inputFile("tsp6_x.txt");
  int matriz_adj[n_nodos][n_nodos];

  for (int i = 0; i < n_nodos; i++) {
    for (int j = 0; j < n_nodos; j++) {
      inputFile >> matriz_adj[i][j];
    }
  }

  cout << endl << endl;
  bruteforce instancia;

  DWORD start = clock();
  cout << instancia.menor_caminho_soma(matriz_adj, n_nodos) << endl;
  DWORD end = clock();

  cout << "Tempo de execução: " << end - start << " ms" << std::endl;
  
  return 0;
}
