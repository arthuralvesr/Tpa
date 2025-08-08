#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

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

Alunos als;

void inicializa(){
    als.inicio = NULL;
    als.fim = NULL;
    als.quantidade = 0;
}

bool iteraMat(char *busca){
    Aluno *aux = als.inicio;

    if(busca == NULL){ // se teve falha no ler aluno
        printf("Erro, linha não copiada!");
        return false;
    }

    if (als.inicio == NULL) { // primeiro termo
        return true;
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
    Aluno *aux = als.inicio;

    if(busca == NULL){ // se teve falha no ler aluno
        printf("Erro, linha não copiada!");
        return false;
    }

    if (als.inicio == NULL) { // primeiro termo
        return true;
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

bool iteraCpf(char *busca){
    Aluno *aux = als.inicio;

    if(busca == NULL){ // se teve falha no ler aluno
        printf("Erro, linha não copiada!");
        return false;
    }

    if (als.inicio == NULL) { // primeiro termo
        return true;
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

Aluno *iteraNome(char *busca){
    Aluno *aux = als.inicio;

    while(true){

        if(aux->nome > busca) {
            aux = aux->prox;
            return aux;
        } else {
            return aux->ante;
        }
    }
}

bool insere(Aluno *aLido){
    Aluno *aux;

    if(aLido == NULL) return false; // se leu errado

    if(als.quantidade == 0){ // lista vazia
        als.inicio = aLido;
        als.fim = aLido;
        aLido->prox = NULL;
        aLido->ante = NULL;


    } else { // demais termos
        
        // ordem alfabetica
        aux = iteraNome(aLido->nome);
        // parei aqui no ordem alfabetica
        // aux é o ponteiro pra onde preciso adicionar
        
        aLido->prox = NULL;
        aLido->ante = als.fim;
    } 
    
    als.quantidade++;
    return true;
}

Aluno *lerAluno(FILE *a) {
    Aluno *novoAl = new Aluno;
    char linha[80];
    char *sep;
    
    if (fgets(linha, 80, a) == NULL) { 
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

    if (iteraCpf(sep) == true){

        strcpy(novoAl->cpf, sep);
    } else {

        delete novoAl;
        return NULL;
    }

    sep = strtok(NULL, ",");
    strcpy(novoAl->nome, sep);
    

    return novoAl;
}


void listar(){
    Aluno *aux = als.inicio;

    printf("\n\n======| LISTAGEM |======\n\n");

    while(aux != NULL) {
        printf("Matricula: %s\n" , aux->matricula);
        printf("CPF: %s\n" , aux->cpf);
        printf("Nome: %s\n\n" , aux->nome);
        
        aux = aux->prox;
    }
}

void buscarCpf(){
    char cpfBuscado[15];

    printf("Insira o CPF a ser buscado: ");
    scanf("%s" , cpfBuscado);
    iteraCpf(cpfBuscado);

    // continuar
}

void buscarMatricula(){
    char matBuscado[15];

    printf("Insira o MATRICULA a ser buscado: ");
    scanf("%s" , matBuscado);
    iteraCpf(matBuscado);

    // continuar
}

void menu(){
    int op;

    printf("\n\n======| MENU |======\n\n");

    printf("1 - Buscar por Matricula\n");
    printf("2 - Buscar por CPF\n");
    printf("3 - Listar\n");
    printf("0 - Sair\n");
    
    printf("Insira uma opção: ");
    scanf("%d" , &op);

    switch (op) {
    case 1:
        buscarMatricula();
        break;
    case 2:
        buscarCpf();
        break;
    case 3:
        listar();
        break;    
    default:
        break;
    }
}

int main() {
    inicializa();
    FILE *arq = fopen("../teste.csv", "r");

    if(arq == NULL){
        printf("Erro!");
        return 1;
    }

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
    }
    

    // listar();
    menu(){

    }

    system("pause");
    return 0;
}

