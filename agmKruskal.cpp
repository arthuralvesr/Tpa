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
#include <algorithm>


using namespace std;
struct Vertice;

struct Vizinho {
    Vertice *vizinho;
    Vizinho *proximoVizinho;
    int peso;
};

struct Vertice {
    int id;
    Vizinho *vizinhos;
};

Vertice *grafo;
Vertice *grafoAgmPrim;

void inicializa(int tamanho){
    grafo = new Vertice[tamanho];

    for(int i = 0; i < tamanho; i++){
        grafo[i].id = i;
        grafo[i].vizinhos = NULL;
    }
}

Vertice* inicializaAgm(int vert) {
    Vertice *grafoMinimo = new Vertice[vert];

    for(int i = 0; i < vert; i++){
        grafoMinimo[i].id = i;
        grafoMinimo[i].vizinhos = NULL;
    }

    return grafoMinimo;
}

void adicionaVizinho(Vertice *a, Vertice *b, int peso){

    if (a == NULL || b == NULL)
        return;

        
    if (a->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
            
        temp->vizinho = b;
        temp->proximoVizinho = NULL;
        a->vizinhos = temp;
        a->vizinhos->peso = peso;
            
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
        aux->proximoVizinho->peso = peso;
    }

         
    if (b->vizinhos == NULL){
        Vizinho *temp = new Vizinho;
            
        temp->vizinho = a;
        temp->proximoVizinho = NULL;
        b->vizinhos = temp;
        b->vizinhos->peso = peso;
            
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
        aux->proximoVizinho->peso = peso;
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

    
    for (int i = 0; i < m * 2; i++) {
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

    for (int i = 0; i < a; i++) {
        int peso = rand() % 10;
        adicionaVizinho(&grafo[possibilidades[i].first], &grafo[possibilidades[i].second], peso);
    }

}

void criarArquivoAGM(int vert, Vertice *grafoAGM) {
    ofstream arquivo("grafoAGM.dot");
    arquivo << "graph GrafoAGM {\n";
    
    for(int i = 0; i < vert; i++){
        arquivo << "\t" << i << ";\n";
    }

    for(int i = 0; i < vert; i++) {
        
        Vizinho *aux = grafoAGM[i].vizinhos; 
        
        while (aux != NULL) {
    
            if (i < aux->vizinho->id) {
                
                arquivo << "\t" << i << " -- " << aux->vizinho->id << " [label=" << aux->peso << ", weight=" << aux->peso << "];\n"; 
            }
            
            aux = aux->proximoVizinho;
        }
    }

    arquivo << "}";
    arquivo.close();

    system("dot -Tpng grafoAGM.dot -o grafoAGM.png");
}

void criarArquivo(int v, int a) { 
    ofstream arquivo("grafo.dot");
    arquivo << "graph Grafo {\n";
    
    for(int i = 0; i < v; i++){
        arquivo << "\t" << i << ";\n";
    }

    for(int i = 0; i < v; i++) {
        
        Vizinho *aux = grafo[i].vizinhos;
        
        while (aux != NULL) {
            if(i > aux->vizinho->id) {
                arquivo << "\t" << i << " -- " << aux->vizinho->id << " [label=" << aux->peso << ", weight=" << aux->peso << "];\n";
            }
            
            aux = aux->proximoVizinho;
        }
    }

    arquivo << "}";
    arquivo.close();

    system("dot -Tpng grafo.dot -o grafo.png");
}

void listar(int v) {

    for(int i = 0; i < v; i++) {
        cout << grafo[i].id << endl;
        Vizinho *aux = grafo[i].vizinhos;

        while (aux != NULL) {
            cout << aux->vizinho->id << " - ";
            aux = aux->proximoVizinho;
        }
        cout << endl;
    }
}

void listarArestas(int vert, ){
    vector<tuple<int, Vertice, Vertice>> arestas;
    

    for (int i = 0; i < vert; i++) { // pega todas as arestas e coloca em um vetor
        Vizinho *aux = grafo[i].vizinhos;
        Vertice origem = grafo[i];

        while (aux->vizinho != NULL) {
            arestas.push_back(make_tuple(aux->peso, origem, *(aux->vizinho)));   
            aux = aux->proximoVizinho;
        }
    }
    
    sort( // ordena as arestas da menor pra maior
        arestas.begin(),
        arestas.end(),
        [](const auto &a, const auto &b) {
            return get<0>(a) < get<0>(b);
        }
    );

    vector<pair<int,Vertice>> subGrafos(vert);
    
    for (int i = 0; i < subGrafos.size(); i++) {
        subGrafos[i].first = i;
        subGrafos[i].second = grafo[i];
    }
    
    
    for (int i = 0; i < vert; i++) {
        pair<int, Vertice> menor = subGrafos[i];

        if (subGrafos[i].first =! menor.first) {

            subGrafos[menor.first].first = subGrafos[i].first;

            for (int i = 0; i < subGrafos.size(); i++) {

                if (menor.first == subGrafos[i].first) {
                    subGrafos[i].first = subGrafos[menor.first].first;
                }
            }

            adicionaVizinho();
        }
    }
}

void agmKruskal(int vert) {
    Vertice *grafoKruskal = inicializaAgm(vert);

    listarArestas(vert, grafoKruskal);

    bool *caminho = new bool[vert];
    
    for(int i = 0; i < vert; i++) { // deixa vetor de visita como falso
        caminho[i] = false;
    }
    
    caminho[0] = true;

    Vertice *vertOrigemVizinho;
    Vertice *vertDestVizinho;
    int menorVizinho;
    int vertVisitados = 1;
    
    while(vertVisitados < vert) { // arvore geradora minima precisa de todos os vertices
        menorVizinho = 11;
        
        for(int i = 0; i < vert; i++) { // encontro o menor vizinho de todos os verts já visitados
            if(caminho[i]){
                Vizinho *aux = grafo[i].vizinhos;

                while(aux != NULL) {
                    
                    if(aux->peso < menorVizinho && caminho[aux->vizinho->id] == false){
                        menorVizinho = aux->peso;
                        
                        vertOrigemVizinho = &grafo[i];
                        vertDestVizinho = aux->vizinho;
                    }
                
                    aux = aux->proximoVizinho;
                }

            }
        }

        caminho[vertDestVizinho->id] = true;
        adicionaVizinho(&grafoKruskal[vertOrigemVizinho->id], &grafoKruskal[vertDestVizinho->id], menorVizinho);
        vertVisitados++;
    }

    criarArquivoAGM(vert, grafoKruskal);
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
    agmKruskal(vertices);
}

void menu(){
    int op;
        
    do {
        cout << "\tGrafos | AGM Kruskal:\n\n";
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