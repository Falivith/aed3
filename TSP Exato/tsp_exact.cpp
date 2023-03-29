#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#define NUM_NODOS 5

using namespace std;

int main() {

    SetConsoleOutputCP(65001);

    ifstream file("tsp0_x.txt");
    string line;

    int matriz[NUM_NODOS][NUM_NODOS];

    int index1, index2; 

    if(file.is_open()){
        while (getline(file, line))
        {
            line.substr(index1, index2);

        }
        file.close();
    }else{
        cout << "Error opening the file." << endl;
    }
    
    return 0;
}