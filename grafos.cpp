#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

int direcionado(int tam) {
    int esc;
    int preenchimento;

    do {
        cout << "1 - Direcionados\n";
        cout << "2 - Não direcionados\n";
        cin >> esc;

    } while (esc != 1 && esc != 2);

    if (esc == 1) {
        preenchimento = tam * (tam - 1); 
    } else {
        preenchimento = (tam * (tam - 1)) / 2;
    }

    return preenchimento;
}

void preencherMatriz(bool **matriz, int a, int t){
    int l, c;

    for(int i = 0; i < a; i++){
        
        do {
            l = rand() % t;
            c = rand() % t;

        } while (matriz[l][c] == 1 || l == c);

        matriz[l][c] = 1;
        matriz[c][l] = 1;
    }
}

void listar(bool **m, int t){

    for(int i = 0; i < t; i++) {
        for(int j = 0; j < t; j++){
           cout << m[i][j] << " ";
        }
        cout << endl;
    }    
}

void criarArquivo(bool **m, int t, int a) { 
    ofstream arquivo("grafo.dot");
    arquivo << "graph Grafo {\n";
    
    for(int i = 0; i < a; i++){
        arquivo << "\t" << i << ";\n";
    }

    for(int i = 0; i < t; i++) {
        for(int j = i + 1; j < t; j++){
            if (m[i][j]){
                arquivo << "\t" << i << " -- " << j << ";\n";
            }
        }
    }

    arquivo << "}";
    arquivo.close();

    system("dot -Tpng grafo.dot -o grafo.png");
}

void criarGrafo(){
    int tam;
    int d;
    int arestas;
    int porcentagem;
    int maxDirecionado;
    
    cout << "Insira quantidade de vertices : ";
    cin >> tam; 
    
    bool **matriz = new bool*[tam];
    
    for(int i = 0; i < tam; i++) {
        matriz[i] = new bool[tam];
    }
    
    // d = direcionado(tam);

    maxDirecionado = tam * (tam - 1);

    cout << "Insira a porcentagem de arestas: ";
    cin >> porcentagem; 

    arestas = (porcentagem / 100.0) * maxDirecionado;
    
    cout << arestas << "\n";

    srand(time(NULL));

    preencherMatriz(matriz, arestas, tam);
    listar(matriz, tam);
    criarArquivo(matriz, tam, arestas);
}

bool lerGrafo(){
    ifstream arquivo("grafoLer.dot");
    bool **matriz;

    if (!arquivo.is_open()) {
        cout << "falha na leitura";
    }

    

    arquivo.close();
    return matriz;
}


void menu(){
    int op;
    bool plotar;
    
    do {
        cout << "\tGrafos:\n\n";
        cout << "1 - Ler grafo\n";
        cout << "2 - Criar grafo\n";
        cin >> op;
    } while (op != 1 && op != 2);

    switch (op) {
    case 1:
        plotar = lerGrafo();
        break;
    case 2:
        criarGrafo();
    default:
        break;
    }

}

int main() {
    
    menu();
}