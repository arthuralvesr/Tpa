#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <locale>
#include <ctime>
#include <iostream>

using namespace std;

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *esq;
    Aluno *dir;
};


struct Alunos{
    Aluno *head;
    int altura;
};

Alunos als;

void inicializar() {
    als.head = NULL;
}

void insere(Aluno *aLido){

    if (als.head == NULL){
        als.head = aLido;
        
    } 
    Aluno *atual = als.head;
    Aluno *pai = NULL;
    
    while (atual != NULL) {
        pai = atual;

        if (strcmp(aLido->nome, atual->nome) < 0) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (strcmp(aLido->nome, pai->nome) < 0) {
        pai->esq = aLido;
    } else {
        pai->dir = aLido;
    }
    
}

void listar(Aluno *raiz){

    if(raiz != NULL) {
        cout << "nome: " << raiz->nome << "\n";
        listar(raiz->esq);
        listar(raiz->dir);
    } 
}

Aluno *lerAluno(FILE *a) {
    Aluno *novoAl = new Aluno;
    char linha[256];
    char *sep;
    
    
    if (fgets(linha, 256, a) == NULL) { 
        return NULL; // final do arquivo
    }
    linha[strcspn(linha, "\n")] = '\0'; // procura o primeiro \n da string linha e troca por 0
    
    sep = strtok(linha, ",");
    strcpy(novoAl->matricula, sep);
    
    sep = strtok(NULL, ",");
    strcpy(novoAl->cpf, sep);

    sep = strtok(NULL, ",");
    strcpy(novoAl->nome, sep);

    sep = strtok(NULL, ",");
    novoAl->nota = atof(sep);
    
    sep = strtok(NULL, ",");
    novoAl->idade = atoi(sep);

    sep = strtok(NULL, ",");
    strcpy(novoAl->curso, sep);

    sep = strtok(NULL, "\n");
    strcpy(novoAl->cidade, sep);

    return novoAl;
}

int main() {
    FILE *arq = fopen("alunos_completos.csv", "r");
    int cont = 0;

    if(arq == NULL){
        printf("Erro!");
        return 1;
    }
    
    char cabecalho[256];
    fgets(cabecalho, sizeof(cabecalho), arq);

    inicializar();

    while (true){ 
        Aluno *alunoLido = lerAluno(arq);

        if (alunoLido == NULL) {
            
            if (feof(arq)){
                break;
            } else {
                continue;
            }
        }        

        insere(alunoLido);
        cont++;

        if (cont == 10) {
            break;
        }
    }
    
    listar(als.head);
    fclose(arq);
    return 0;
}