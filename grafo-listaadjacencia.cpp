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

         
    if (b->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
            
        temp->vizinho = a;
        temp->proximoVizinho = NULL;
        b->vizinhos = temp;
            
    } else {
        Vizinho *aux;
        aux = b->vizinhos;
        
        while (aux->proximoVizinho != NULL){
            aux = aux->proximoVizinho;
        }
        
        Vizinho *temp = new Vizinho;
        
        temp->vizinho = a;
        temp->proximoVizinho = NULL;
        aux->proximoVizinho = temp;
    }
}

void possibilidades(int a, int v, int m){
    vector<pair<int,int>> possibilidades(m);
    int cont = 0;
    int sort1, sort2;

    for (int i = 0; i < v; i++) {
        for (int j = i + 1; j < v; j++) {
            possibilidades[cont].first = i;
            possibilidades[cont].second = j;
            cont++;
        }
    }

    for (int i = 0; i > m * 2; i++) {
        int s1 = rand() % a; 
        int s2 = rand() % a; 

        if (s1 = s2) {
            i--;
            continue;
        }

        pair<int,int> guardar;
        guardar.first = possibilidades[s1].first;
        guardar.second = possibilidades[s1].second;

        possibilidades[s1].first = possibilidades[s2].first;
        possibilidades[s1].second = possibilidades[s2].second;

        possibilidades[s2].first = guardar.first;
        possibilidades[s2].second = guardar.second;
    }

    for(int i = 0; i < m; i++) {

        cout << possibilidades[i].first << "  ";
        cout << possibilidades[i].second << endl;
    }

    for (int i = 0; i < a; i++) {
        adicionaVizinho(&grafo[possibilidades[i].first], &grafo[possibilidades[i].second]);
    }

}

void criarArquivo(int a, int v) { 
    ofstream arquivo("grafo.dot");
    arquivo << "graph Grafo {\n";
    
    for(int i = 0; i < v; i++){
        arquivo << "\t" << i << ";\n";
    }

    for(int i = 0; i < v; i++) {
        
    Vizinho *aux = grafo[i].vizinhos;
    
    while (aux != NULL) {
        if(i < aux->vizinho->id) {
            arquivo << "\t" << i << " -- " << aux->vizinho->id << ";\n";
        }
        
        aux = aux->proximoVizinho;
        }
    }

    arquivo << "}";
    arquivo.close();

    system("dot -Tpng grafo.dot -o grafo.png");
}

void listar(int v) {
    Vertice aux;

    for(int i = 0; i > v; i++) {
        cout << grafo[i].id << endl;
        Vizinho *aux = grafo[i].vizinhos;

        while (aux != NULL) {
            cout << grafo[i].vizinhos->vizinho;
            aux = grafo[i].vizinhos->proximoVizinho;
        }
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
    int m = maxDirecionado / 2;

    possibilidades(arestas, vertices, m);

    listar(vertices);
    criarArquivo(vertices, arestas);
    
    // if (conexidade(vertices)){
    //    cout << "O grafo gerado é conexo!\n";
    // } else {
    //    cout << "O grafo gerado é desconexo!\n";
    // }
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
        // lerGrafo();
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
    
    menu();

}