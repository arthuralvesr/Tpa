#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <locale>


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

Alunos als[99];

void inicializaHash(){
    
    for(int i = 0; i < 99; i++){
        als[i].inicio = NULL;
        als[i].fim = NULL;
        als[i].quantidade = 0;
    }
}

bool iteraMat(char *busca){
    Aluno *aux = als[0].inicio;

    if(busca == NULL){ // se teve falha no ler aluno
        printf("Erro, linha não copiada!");
        return false;
    }

    while(aux != NULL) { // itera procurando dup
        
        if(strcmp(busca, aux->matricula) == 0){
            printf("Matricula duplicada: %s\n" , busca);
            return false;
        }
        aux = aux->prox;
    }

    return true;
}

bool iteraCpf(char *busca){
    Aluno *aux = als[0].inicio;

    if(busca == NULL){ // se teve falha no ler aluno
        printf("Erro, linha não copiada!");
        return false;
    }

    while(aux != NULL) { // itera procurando dup

        if(strcmp(busca, aux->cpf) == 0){
            printf("CPF duplicado: %s\n" , busca);
            return false;
        }
        aux = aux->prox;
    }

    return true;
}

int pegarHash(char *cpf){
    char *hash = strrchr(cpf, '-');
    int teste;

    if (hash != NULL) {
        return atoi(hash + 1);
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

    if(sep == NULL) { // se der erro na leitura do arq
        printf("Erro na leitura da matricula\n");
        delete novoAl;
        return NULL;
    }

    if (iteraMat(sep) == true) { // verificação de duplicada da matricula
        strcpy(novoAl->matricula, sep);
    } else {

        delete novoAl;
        return NULL;
    }

    sep = strtok(NULL, ",");
    if(sep == NULL) { // erro na leitura do arquivo
        printf("Erro na leitura do CPF\n");
        delete novoAl;
        return NULL;
    }

    int hash = pegarHash(sep);
    printf("%d" , hash);

    // if (iteraCpf(sep) == true){

    //     strcpy(novoAl->cpf, sep);
    // } else {

    //     delete novoAl;
    //     return NULL;
    // }
    

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
    inicializaHash();
    FILE *arq = fopen("../alunos_completos.csv", "r");
    int cont = 0;

    if(arq == NULL){
        printf("Erro!");
        return 1;
    }

    // Ignora a primeira linha do csv
    char cabecalho[256];
    fgets(cabecalho, sizeof(cabecalho), arq);

    while (true){ 
        Aluno *alunoLido = lerAluno(arq);

        if (alunoLido == NULL) {
            
            if (feof(arq)){
                printf("teste");
                break;
            } else {
                continue;
            }
        }

        // insere(alunoLido);
        cont++;

        if (cont == 1) {
            break;
        }
    }
    

    // listar();
    // menu();
    fclose(arq);
    system("pause");
    return 0;
}
