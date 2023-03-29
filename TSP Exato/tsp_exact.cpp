#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#define NUM_NODOS 5

using namespace std;

int main() {

    SetConsoleOutputCP(65001);

    ifstream file("tsp0_x.txt");
    string line;

    int matriz[NUM_NODOS][NUM_NODOS];

    int index1, index2;

    cout << "ALO";
    
    return 0;
}