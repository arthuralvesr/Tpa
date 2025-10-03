#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <locale>
#include <ctime>
#include <iostream>

using namespace std;

#define TAM 1000

//Matricula,CPF,Nome,Nota,Idade,Curso,Cidade
//A0000000,915.216.859-08,Wallace Sampaio,20.35,23,Direito,Rio de Janeiro

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *prox;
    Aluno *ante;
};


struct Alunos{
    Aluno *inicio;
    Aluno *fim;
    int quantidade;
};

Alunos als[TAM];

void inicializaHash(){
    
    for(int i = 0; i < TAM; i++){
        als[i].inicio = NULL;
        als[i].fim = NULL;
        als[i].quantidade = 0;
    }
}

bool insere(Aluno *aLido, int hash){
    Aluno *aux = als[hash].inicio;

    
    if(aLido == NULL) return false; // se leu errado

    if(als[hash].quantidade == 0){ // lista vazia
        als[hash].inicio = aLido;
        als[hash].fim = aLido;
        aLido->prox = NULL;
        aLido->ante = NULL;

        als[hash].quantidade++;
        return true;
    } 

    // so insere no fim, organiza dps
    als[hash].fim->prox = aLido;
    aLido->ante = als[hash].fim;
    aLido->prox = NULL;
    als[hash].fim = aLido;

    als[hash].quantidade++;
    return true;
}

int compara(const void* a, const void* b) {
    //comparar os dois nomes..
    Aluno **a1;
    Aluno **a2;
    a1 = (Aluno**)a;
    a2 = (Aluno**)b;
    int retorno = strcmp((*a1)->nome, (*a2)->nome);
    return retorno;
}


void ordena(int im){
    Aluno **v;
    Aluno *atual = als[im].inicio;
    v = new Aluno*[als[im].quantidade];

    printf("quantidade: %d\n",als[im].quantidade);

    for(int i=0; i < als[im].quantidade; i++){
        v[i] = atual;
        atual = atual->prox;
    }

    qsort(v,als[im].quantidade,sizeof(Aluno*),compara);

    als[im].inicio = v[0];
    als[im].inicio->ante = NULL;
    als[im].inicio->prox = v[1];
    atual = v[1];

    for(int i=1; i < als[im].quantidade-1; i++){
        atual->prox = v[i+1];
        atual->ante = v[i-1];
        atual = atual->prox;

    }

    als[im].fim = v[als[0].quantidade-1];
    als[im].fim->prox = NULL;
    als[im].fim->ante = v[als[0].quantidade-2];
}

int pegarHash(char *cpf) {
    if (strlen(cpf) != 14) return 0;

    char ultimos[5];

    ultimos[0] = cpf[9];   
    ultimos[1] = cpf[10];  
    ultimos[2] = cpf[12];  
    ultimos[3] = cpf[13]; 
    ultimos[4] = '\0';
  
    return atoi(ultimos);
}

Aluno *lerAluno(FILE *a) {
    Aluno *novoAl = new Aluno;
    char linha[256];
    char *sep;
    
    
    if (fgets(linha, 256, a) == NULL) { 
        return NULL; // final do arquivo
    }
    linha[strcspn(linha, "\n")] = '\0'; // procura o primeiro \n da string linha e troca por 0
    
    // leitura matricula
    sep = strtok(linha, ",");
    strcpy(novoAl->matricula, sep);
    
    // leitura cpf
    sep = strtok(NULL, ",");
    strcpy(novoAl->cpf, sep);

    // nome 
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

void listar(){
    
    printf("\n\n======| LISTAGEM |======\n\n");
    
    for(int i = 0; i < TAM; i++){
        Aluno *aux = als[i].inicio;

        while(aux != NULL) {
            printf("Matricula: %s\n" , aux->matricula);
            printf("CPF: %s\n" , aux->cpf);
            printf("Nome: %s\n" , aux->nome);
            printf("Nota: %.2f\n" , aux->nota);
            printf("Idade: %d\n" , aux->idade);
            printf("Curso: %s\n" , aux->curso);
            printf("Cidade: %s\n\n" , aux->cidade);
            
            aux = aux->prox;
        }
    }
}

int main() {
    inicializaHash();
    FILE *arq = fopen("alunos_completos.csv", "r");
    int cont = 0;

    time_t inicio, fim;
    inicio = time(NULL);

    if(arq == NULL){
        printf("Erro!");
        return 1;
    }

    // Ignora a primeira linha do csv
    char cabecalho[256];
    fgets(cabecalho, sizeof(cabecalho), arq);

    while (true){ 
        Aluno *alunoLido = lerAluno(arq);

        cout << "teste" << endl;

        if (alunoLido == NULL) {
            
            if (feof(arq)){
                break;
            } else {
                continue;
            }
        }  
        int hash = pegarHash(alunoLido->cpf);  
        insere(alunoLido, hash);
        cont++;

        if (cont == 10000000000) {
            break;
        }
    }

    for (int i = 0; i > TAM; i++) {
        ordena(i);
    }
    
    listar();
    // menu();
    fclose(arq);

    fim = time(NULL);
    time_t tempo;
    tempo = fim - inicio;
    printf("Leitura: %d segs\n" , (int)tempo);

    return 0;
}
