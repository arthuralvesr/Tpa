#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

int direcionado(int vertices) {
    int esc;
    int preenchimento;

    do {
        cout << "1 - Direcionados\n";
        cout << "2 - Não direcionados\n";
        cin >> esc;

    } while (esc != 1 && esc != 2);

    if (esc == 1) {
        preenchimento = vertices * (vertices - 1); 
    } else {
        preenchimento = (vertices * (vertices - 1)) / 2;
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

bool conexidade(bool **m, int v) { // ta errado
    bool *caminho = new bool[v];
    
    for(int i = 0; i < v; i++) { // deixa vetor de visita como falso
        caminho[i] = false;
    }
    
    caminho[0] = true;

    for(int i = 0; i < v; i++) { // verificação se já foi visitado
        
        if(caminho[i]){
            for (int j = 0; j < v; j++){
                
                if (m[i][j] == true) {
                    caminho[j] = true;
                }            
            }
        }
    }

    for(int i = 0; i < v; i++){ // percorrer vetor
        if(caminho[i] == false){
            return false;
        }
    }

    return true;
}

void listar(bool **m, int v){

    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++){
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
    int vertices;
    int d;
    int arestas;
    int porcentagem;
    int maxDirecionado;
    
    cout << "Insira quantidade de vertices : ";
    cin >> vertices; 
    
    bool **matriz = new bool*[vertices];
    
    for(int i = 0; i < vertices; i++) {
        matriz[i] = new bool[vertices];
    }
    
    // d = direcionado(vertices);

    maxDirecionado = vertices * (vertices - 1);

    cout << "Insira a porcentagem de arestas: ";
    cin >> porcentagem; 

    arestas = (porcentagem / 100.0) * maxDirecionado;
    
    cout << arestas << "\n";

    srand(time(NULL));

    preencherMatriz(matriz, arestas, vertices);
    listar(matriz, vertices);
    criarArquivo(matriz, vertices, arestas);
    
    if (conexidade(matriz, vertices)){
        cout << "O grafo gerado é conexo!\n";
    } else {
        cout << "O grafo gerado é desconexo!\n";
    }
}

void lerGrafo(){
    ifstream arquivo;
    string linha;
    int vertices;


    cout << "Insira quantidade de vertices : ";
    cin >> vertices; 
    
    bool **matriz = new bool*[vertices];
    
    for(int i = 0; i < vertices; i++) {
        matriz[i] = new bool[vertices];
    }


    arquivo.open("grafo.dot");

    if (!arquivo.is_open()) {
        cout << "falha na leitura";
    }

    while (getline(arquivo, linha)) {
        if (linha.find("--") != string::npos) {
            stringstream ss(linha);
            int v1, v2;
            char lixo; // para descartar os hífens

            ss >> v1 >> lixo >> lixo >> v2; // lê "1 -- 0;" ignorando os '-'

            matriz[v1][v2] = true;
            matriz[v2][v1] = true;
        } else {
            continue;
        }
    }

    arquivo.close();
    listar(matriz, vertices);
    
    if (conexidade(matriz, vertices)){
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
    
    menu();
}