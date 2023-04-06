#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <windows.h>
#include <time.h>

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

struct resposta
{
  vector<int> caminho;
  int distancia_total;
};

class aproximativos {

public:

  string nearest_neighbor(int matriz_adj[n_nodos][n_nodos], int num_nodos, bool tOpt) {

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
    
    if(tOpt){
      twoOpt(percorridos, matriz_adj);
      peso_total = custo(percorridos, matriz_adj);
    }
    
    // Por fim, soma-se o peso do último nodo da permutação até o nodo inicial, fechando o ciclo hamiltoniano.
    peso_total += matriz_adj[percorridos.back()][inicio];
    percorridos.push_back(inicio);

    resposta r;
    r.caminho = percorridos;
    r.distancia_total = peso_total;
    resposta_format(r);

    return resposta_format(r);
  }

  string farthest_insertion(int matriz_adj[n_nodos][n_nodos], int num_nodos, bool tOpt) {

    vector<int> nodos(num_nodos);
    vector<int> percorridos;

    for (int i = 0; i < num_nodos; i++)
        nodos[i] = i;

    int inicio = 0;
    int n = nodos.size();
    int peso_total = 0;
    int nodo_atual = inicio;
    int prox_nodo = 0;

    // Adiciona o nodo inicial à lista de nodos percorridos.
    percorridos.push_back(nodo_atual);

    // Encontra o nodo mais distante do nodo inicial.
    for (int i = 1; i < n; i++) {
        if (matriz_adj[nodo_atual][nodos[i]] > matriz_adj[nodo_atual][prox_nodo])
            prox_nodo = nodos[i];
    }

    // Adiciona o nodo mais distante à lista de nodos percorridos.
    percorridos.push_back(prox_nodo);

    // Atualiza a distância total percorrida.
    peso_total += matriz_adj[nodo_atual][prox_nodo];
    
    while (percorridos.size() < n) {

        // Inicializa o menor custo de inserção com um valor muito grande.
        int menor_custo = INT_MAX;
        int pos_insercao;

        // Para cada par de nodos (i, j), onde i pertence à lista de nodos percorridos e j não pertence:
        for (int i = 0; i < percorridos.size(); i++) {
            for (int j = 0; j < n; j++) {
                if (find(percorridos.begin(), percorridos.end(), j) == percorridos.end()) {
                    int custo_insercao = matriz_adj[percorridos[i]][j] + matriz_adj[j][percorridos[(i+1)%percorridos.size()]] - matriz_adj[percorridos[i]][percorridos[(i+1)%percorridos.size()]];

                    if (custo_insercao < menor_custo) {
                        menor_custo = custo_insercao;
                        pos_insercao = i + 1;
                        prox_nodo = j;
                    }
                }
            }
        }

        // Insere o nodo mais próximo ao ciclo hamiltoniano.
        percorridos.insert(percorridos.begin()+pos_insercao, prox_nodo);

        // Atualiza a distância total percorrida.
        peso_total += menor_custo;
    }

    // Adiciona o nodo inicial para fechar o ciclo hamiltoniano.
    percorridos.push_back(inicio);
    peso_total += matriz_adj[percorridos.back()][inicio];

    cout << peso_total << endl;

    // Aplica a heurística de 2-opt, se necessário.
    if (tOpt) {
        twoOpt(percorridos, matriz_adj);
        peso_total = custo(percorridos, matriz_adj);
    }

    cout << peso_total << endl; 
    // Retorna a solução como uma string formatada.

    resposta r;
    r.caminho = percorridos;
    r.distancia_total = custo(percorridos, matriz_adj);
    resposta_format(r);

    return resposta_format(r);
}
  // Função auxiliar pra calcular o custo de uma rota dentro da matriz de adjacência

private:

  int custo(vector<int> &route, int matriz_adj[][n_nodos]) {
    int c = matriz_adj[route[n_nodos-1]][route[0]];
    for (int i = 0; i < n_nodos - 1; i++) {
        c += matriz_adj[route[i]][route[i + 1]];
    }
    return c;
  }

  void twoOpt(vector<int> &route, int matriz_adj[][n_nodos]) {
      int n = route.size();
      bool improved = true;
      while (improved) {
          improved = false;
          for (int i = 0; i < n - 1; i++) {
              for (int j = i + 1; j < n; j++) {
                  int a = route[i];
                  int b = route[(i + 1) % n];
                  int c = route[j];
                  int d = route[(j + 1) % n];
                  int delta = matriz_adj[a][c] + matriz_adj[b][d] - matriz_adj[a][b] - matriz_adj[c][d];
                  if (delta < 0) {
                      reverse(route.begin() + i + 1, route.begin() + j + 1);
                      improved = true;
                  }
              }
          }
      }
  }

  string resposta_format(resposta r){
    string resposta = to_string(r.distancia_total);
    string solucao = "[";

    for (int i = 0; i < r.caminho.size(); i++) {
      r.caminho[i]++;
      solucao += to_string(r.caminho[i]) + " ";
    }

    solucao.pop_back();
    solucao += "]";
    resposta = "Os nodos percorridos foram: " + solucao + "\n" "O peso total do caminho é: " + resposta; 

    return resposta;
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

  cout << endl;
  cout << "| --------------- Vizinho mais próximo --------------- |" << endl;
  cout << endl;

  aproximativos instancia;

  DWORD start = clock();
  cout << instancia.nearest_neighbor(matriz_adj, n_nodos, false) << endl;
  DWORD end = clock();

  cout << "Tempo de execução: " << ((double) (end - start)) / CLOCKS_PER_SEC << " ms" << endl;

  ///////////////////////////////////////////////////////////////////////

  cout << endl;
  cout << "| --------------- Vizinho mais próximo (C/2-OPT) --------------- |" << endl;
  cout << endl;

  start = clock();
  cout << instancia.nearest_neighbor(matriz_adj, n_nodos, true) << endl;
  end = clock();

  cout << "Tempo de execução: " << end - start << " ms" << endl;

  ///////////////////////////////////////////////////////////////////////

  cout << endl;
  cout << "| --------------- Farthest Insertion --------------- |" << endl;
  cout << endl;

  start = clock();
  cout << instancia.farthest_insertion(matriz_adj, n_nodos, false) << endl;
  end = clock();

  cout << "Tempo de execução: " << end - start << " ms" << endl;

    ///////////////////////////////////////////////////////////////////////

  cout << endl;
  cout << "| --------------- Farthest Insertion (C/2 - OPT) --------------- |" << endl;
  cout << endl;

  start = clock();
  cout << instancia.farthest_insertion(matriz_adj, n_nodos, true) << endl;
  end = clock();

  cout << "Tempo de execução: " << end - start << " ms" << endl;
  cout << endl << "| -------------------------- |" << endl << endl;
  
  return 0;
}
