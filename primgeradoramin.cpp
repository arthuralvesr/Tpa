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
    int peso;
    Vertice *vizinho;
    Vizinho *proximoVizinho;
};

struct Vertice {
    int id;
    Vizinho *vizinhos;
};

Vertice *grafo;