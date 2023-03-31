#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <vector>
#include <windows.h>

#define n_nodos 15
using namespace std;

class brute_force {
public:
  int shortest_path_sum(int edges_list[n_nodos][n_nodos], int num_nodes) {
    int source = 0;
    vector<int> nodes;
    for (int i = 0; i < num_nodes; i++) {
      if (i != source) {
        nodes.push_back(i);
      }
    }
    int n = nodes.size();
    int shortest_path = INT_MAX;
    while (next_permutation(nodes.begin(), nodes.end())) {
      int path_weight = 0;

      int j = source;
      for (int i = 0; i < n; i++) {
        path_weight += edges_list[j][nodes[i]];
        j = nodes[i];
      }
      path_weight += edges_list[j][source];

      shortest_path = min(shortest_path, path_weight);
    }
    return shortest_path;
  }
};

int main() {

  SetConsoleOutputCP(65001);

  cout << "Matriz de Adjacência" << endl << "--------------------" << endl;

  ifstream inputFile("tsp3_1194.txt");

  int adj_matrix[n_nodos][n_nodos];

  for (int i = 0; i < n_nodos; i++) {
    for (int j = 0; j < n_nodos; j++) {
      inputFile >> adj_matrix[i][j];
      cout << adj_matrix[i][j] << " ";
    }
    cout << endl;
  }

  cout << "--------------------" << endl;

  cout << endl << endl;
  brute_force approach1;
  cout << approach1.shortest_path_sum(adj_matrix, n_nodos) << endl;
}
