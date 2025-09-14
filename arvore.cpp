#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <locale>
#include <ctime>
#include <iostream>

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


bool insere(Aluno *aLido, Aluno *raiz){

    if (raiz == NULL){
        raiz = aLido;
        aLido->esq = NULL;
        aLido->dir = NULL;

    } else { 
        if (strcmp(aLido->nome, raiz->nome) < 0) {
            insere(aLido, raiz->esq);
        } else {
            insere(aLido, raiz->dir);
        }
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
    Aluno *raiz = als.head;
    FILE *arq = fopen("../alunos_completos.csv", "r");
    int cont = 0;

    if(arq == NULL){
        printf("Erro!");
        return 1;
    }

    char cabecalho[256];
    fgets(cabecalho, sizeof(cabecalho), arq);

    while (true){ 
        Aluno *alunoLido = lerAluno(arq);

        if (alunoLido == NULL) {
            
            if (feof(arq)){
                break;
            } else {
                continue;
            }
        }        

        insere(alunoLido, raiz);
        cont++;

        if (cont == 10) {
            break;
        }
    }
    
    // menu();
    fclose(arq);
    system("pause");
    return 0;
}

