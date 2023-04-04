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

#define n_nodos 29
using namespace std;

class aproximativos {

public:

  string vizinho_mais_proximo(int matriz_adj[n_nodos][n_nodos], int num_nodos) {

    vector<int> nodos;
    vector<int> percorridos;

    for (int i = 0; i < num_nodos; i++)
      nodos.push_back(i);

    int inicio = 0;

    int n = nodos.size();
    
    int peso_total = 0; 
    int peso_aresta_atual;
    int nodo_atual;
    int menor_vizinho;

    // O nodo inicial já consta como percorrido.
    percorridos.push_back(inicio); 

    for (int i = 0; i < n - 1; i++)
    {
      peso_aresta_atual = INT_MAX;
      nodo_atual = percorridos.back(); 

      for (int j = 0; j < n; j++){

        // Garante que o nodo não foi visitado ainda
        if( find(begin(percorridos), end(percorridos), j) == end(percorridos) ){
          if(matriz_adj[nodo_atual][j] < peso_aresta_atual){
            peso_aresta_atual = matriz_adj[nodo_atual][j];
            menor_vizinho = j;
          }
        }
      }

      percorridos.push_back(menor_vizinho);
      peso_total += matriz_adj[nodo_atual][menor_vizinho];
    }
    
    // Por fim, soma-se o peso do último nodo da permutação até o nodo inicial, fechando o ciclo hamiltoniano.
    peso_total += matriz_adj[percorridos.back()][inicio];


    // Abaixo é só feita a formatação da String de resposta.
    
    string resposta = to_string(peso_total);
    string solucao = "[";
    percorridos.push_back(inicio);

    for (int i = 0; i < percorridos.size(); i++) {
      percorridos[i]++;
      solucao += to_string(percorridos[i]) + " ";
    }

    solucao.pop_back();
    solucao += "]";

    resposta = "Os nodos percorridos foram: " + solucao + "\n" "O peso total do caminho é: " + resposta; 

    return resposta;
  }

  string outracoisa(int matriz_adj[n_nodos][n_nodos], int num_nodos) {
  }
};

int main() {

  SetConsoleOutputCP(65001);
  ifstream inputFile("tsp5_27603.txt");
  int matriz_adj[n_nodos][n_nodos];

  for (int i = 0; i < n_nodos; i++) {
    for (int j = 0; j < n_nodos; j++) {
      inputFile >> matriz_adj[i][j];
    }
  }

  cout << endl << endl;
  aproximativos instancia;

  DWORD start = GetTickCount();
  cout << instancia.vizinho_mais_proximo(matriz_adj, n_nodos) << endl;
  DWORD end = GetTickCount();

  cout << "Tempo de execução: " << end - start << " ms" << std::endl;
  
  return 0;
}
