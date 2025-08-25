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

Alunos als[100];

void inicializaHash(){
    
    for(int i = 0; i < 100; i++){
        als[i].inicio = NULL;
        als[i].fim = NULL;
        als[i].quantidade = 0;
    }
}

bool procDup(char *mat, char *cpf){
    
    if(mat == NULL || cpf == NULL){ // se teve falha no ler aluno
        printf("Erro, linha não copiada!");
        return false;
    }
    
    
    for(int i = 1; i < 100; i++){
        Aluno *aux = als[i].inicio;
        
        while(aux != NULL) { // itera procurando dup
            
            if((strcmp(mat, aux->matricula) == 0) || (strcmp(cpf, aux->cpf) == 0)){
                printf("Duplicada");
                return false;
            }

            aux = aux->prox;
        }

    }

    return true;
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

    if (strcmp(aLido->nome, als[hash].inicio->nome) < 0) { // começo
        aLido->prox = als[hash].inicio;
        als[hash].inicio->ante = aLido;
        aLido->ante = NULL;
        als[hash].inicio = aLido;

        als[hash].quantidade++;
        return true;
    }

    while (aux != NULL) { // meio 

        if (strcmp(aux->nome, aLido->nome) > 0) {

            aLido->ante = aux->ante;
            aux->ante->prox = aLido;
            aLido->prox = aux;
            aux->ante = aLido;

            als[hash].quantidade++;
            return true;
        }

        aux = aux->prox;
    }

    // fim
    als[hash].fim->prox = aLido;
    aLido->ante = als[hash].fim;
    aLido->prox = NULL;
    als[hash].fim = aLido;

    als[hash].quantidade++;
    return true;
}

int pegarHash(char *cpf){
    char *hash = strrchr(cpf, '-');

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
    
    // leitura matricula
    sep = strtok(linha, ",");
    strcpy(novoAl->matricula, sep);

    // leitura cpf
    sep = strtok(NULL, ",");
    strcpy(novoAl->cpf, sep);
    
    if (procDup(novoAl->matricula, novoAl->cpf) == false){

        delete novoAl;
        return NULL;
    }

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
    
    for(int i = 0; i < 100; i++){
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
        
        int hash = pegarHash(alunoLido->cpf);  

        insere(alunoLido, hash);
        cont++;

        if (cont == 100) {
            break;
        }
    }
    

    listar();
    // menu();
    fclose(arq);
    system("pause");
    return 0;
}
