#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>


using namespace std;
struct Vertice;

struct Vizinho {
    Vertice *vizinho;
    Vizinho *proximoVizinho;
};

struct Vertice {
    int id;
    Vizinho *vizinhos;
};

Vertice *grafo;

void inicializa(int tamanho){
    grafo = new Vertice[tamanho];

    for(int i = 0; i < tamanho; i++){
        grafo[i].id = i;
        grafo[i].vizinhos = NULL;
    }
}

void adicionaVizinho(Vertice *a, Vertice *b){

    if (a == NULL || b == NULL)
        return;

        
    if (a->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
            
        temp->vizinho = b;
        temp->proximoVizinho = NULL;
        a->vizinhos = temp;
            
    } else {
        Vizinho *aux;
        aux = a->vizinhos;
        
        while (aux->proximoVizinho != NULL){
            aux = aux->proximoVizinho;
        }
        
        Vizinho *temp = new Vizinho;
        
        temp->vizinho = b;
        temp->proximoVizinho = NULL;
        aux->proximoVizinho = temp;
    }

    // preciso colocar o b como vizinho de a também
    // grafo aqui é não direcionado
}

void possibilidades(int a, int t){
    vector<pair<int,int>> possibilidades(a);
    int cont = 0;
    int sort1, sort2;

    for (int i = 0; i < t; i++) {
        for (int j = i + 1; i < t; j++) {
            possibilidades[cont].first = i;
            possibilidades[cont].second = j;
            cont++;
        }
    }

    for (int i = 0; i xx; i++) {
        sort1 = rand() % a;
        sort2 = rand() % a;


    }

    for(int i = 0; i < a; i++) {
        adicionaVizinho(&grafo[possibilidades[i].first], &grafo[possibilidades[i].second]);
    }
}

void criarGrafo(){
    int vertices;
    int arestas;
    int porcentagem;
    int maxDirecionado;
    
    cout << "Insira quantidade de vertices : ";
    cin >> vertices; 

    inicializa(vertices);
    
    maxDirecionado = vertices * (vertices - 1);

    cout << "Insira a porcentagem de arestas: ";
    cin >> porcentagem; 

    arestas = (porcentagem / 100.0) * maxDirecionado;
    
    cout << arestas << "\n";

    srand(time(NULL));

    possibilidades(arestas, t);
    listar(vertices);
    criarArquivo(vertices, arestas);
    
    if (conexidade(vertices)){
        cout << "O grafo gerado é conexo!\n";
    } else {
        cout << "O grafo gerado é desconexo!\n";
    }
}


void menu(){
    int op;
        
    do {
        cout << "\tGrafos:\n\n";
        cout << "1 - Ler grafo\n";
        cout << "2 - Criar grafo\n";
        cout << "3 - Sair\n";
        cout << "Digite uma opcao: ";
        cin >> op;

    } while (op != 1 && op != 2 && op != 3);

    switch (op) {
    case 1:
        lerGrafo();
        break;
    case 2:
        criarGrafo();
    case 3: 
        system("close");
    default:
        break;
    }

}

int main() {
    
    main();

}