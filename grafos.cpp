#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <locale>
#include <ctime>
#include <iostream>

using namespace std;

int preenchimento(int tam) {
    int esc;
    int preenchimento;

    do {
        cout << "1 - 100%";
        cout << "2 - 50%";
        cin >> esc;

    } while (esc != 1 && esc != 2);

    if (esc == 1) {
        preenchimento = tam *(tam - 1); 
    } else {
        preenchimento = (tam * (tam - 1)) / 2;
    }

    return preenchimento;
}

void criarMatriz(bool matriz){
    // preencher matriz
}

int main() {
    int tam;
    int dir;
    int arestas;
    
    cout << "Insira o tamanho da matriz: ";
    cin >> tam; 
    
    bool **matriz = new bool*[tam];
    
    for(int i = 0; i < tam; i++) {
        matriz[i] = new bool[tam];
    }

    arestas = preenchimento(tam);

    criarMatriz(matriz);
        
}