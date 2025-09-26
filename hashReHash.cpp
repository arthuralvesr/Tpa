//Exemplo de código para utilizar contagem de tempo em execução de funções ou trechos de código
//Neste exemplo também teremos leitura de arquivos CSV e manipulação de strings
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <math.h>
#include <iostream>


using namespace std;


//Exemplo do arquivo CSV que será lido
//Matricula,CPF,Nome,Nota,Idade,Curso,Cidade
//A0000000,915.216.859-08,Wallace Sampaio,20.35,23,Direito,Rio de Janeiro

#define CARGA_MAXIMA 0.6
#define TAMANHO_HASH_INICIAL 1021

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[40];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
};

struct Alunos{
    Aluno **hash;
    bool *hashOcupada;
    bool *hashRemovido;
    int tamanhoAtual;
    int quantidade;
};

Alunos a;

void inicializa(){
    a.tamanhoAtual = TAMANHO_HASH_INICIAL;
    a.quantidade = 0;
    a.hash = new Aluno*[a.tamanhoAtual];
    a.hashOcupada = new bool[a.tamanhoAtual];
    a.hashRemovido = new bool[a.tamanhoAtual];

    for (int i=0; i<a.tamanhoAtual; i++){
        a.hashOcupada[i] = false;
        a.hashRemovido[i] = false;
    }

}

void inicializaExpandido(Alunos *hashExp, int tam){
    
    hashExp->tamanhoAtual = tam;
    hashExp->quantidade = 0;
    hashExp->hash = new Aluno*[tam];
    hashExp->hashOcupada = new bool[tam];
    hashExp->hashRemovido = new bool[tam];

    for (int i = 0; i < hashExp->tamanhoAtual; i++){
        hashExp->hashOcupada[i] = false;
        hashExp->hashRemovido[i] = false;
    }
}

int primo(int n) {
    if (n & 1)
        n -= 2;
    else
        n--;

    int i, j;
    for (i = n; i >= 2; i -= 2) {
        if (i % 2 == 0)
            continue;
        for (j = 3; j <= sqrt(i); j += 2) {
            if (i % j == 0)
                break;
        }
        if (j > sqrt(i))
            return i;
    }

    return 2;
}

void expandirHash() {
    int tamNovo = primo(a.tamanhoAtual * 2);

    Alunos *hashExpandida = new Alunos; 
    inicializaExpandido(hashExpandida, tamNovo); 

    for (int i = 0; i < a.tamanhoAtual; i++) {
        if(a.hashOcupada[i] == true) {
            inserirExpandido(hashExpandida, i);
        }
    }

    delete[] a.hash;
    delete[] a.hashOcupada;
    delete[] a.hashRemovido;

    a.hash = hashExpandida->hash;
    a.hashOcupada = hashExpandida->hashOcupada;
    a.hashRemovido = hashExpandida->hashRemovido;
}

int calculoHash(int calcHash) {
    return (calcHash * calcHash * calcHash) % a.tamanhoAtual;
}

int calculoReHash(int calcReHash) {
    return 1 + (calcReHash % (a.tamanhoAtual - 1));
}


void inserir(Aluno *aLido){
    if ((a.quantidade / a.tamanhoAtual) > CARGA_MAXIMA) {
        expandirHash();
    }

    int soma = 0;
    for (char c : aLido->nome) {
        soma += static_cast<int>(c); // converte o char para inteiro (valor ASCII)
    }
    int calc = calculoHash(soma);
    int calc2 = -1;
    
    while (a.hashOcupada[calc]) {
        if(strcmp(aLido->nome, a.hash[calc]->nome) == 0) {
            printf("Nomes repetidos");
            return;
        }

        if (calc2 == -1) {
            calc2 = calculoReHash(calc);
        }

        calc = (calc + calc2) % a.tamanhoAtual; 
    }

    a.hash[calc] = aLido;
    a.quantidade++;
    a.hashOcupada[calc] = true;
    a.hashRemovido[calc] = false;
    
}

void inserirExpandido(Alunos *hashExp, int i) {
    
    int soma = 0;
    for (char c : a.hash[i]->nome) {
        soma += static_cast<int>(c); // converte o char para inteiro (valor ASCII)
    }
    int calc = calculoHash(soma);
    int calc2 = -1;
    
    while (hashExp->hashOcupada[calc]) {
        if (calc2 == -1) {
            calc2 = calculoReHash(calc);
        }

        calc = (calc + calc2) % a.tamanhoAtual; 
    }

    hashExp->hash[calc] = a.hash[i];
    hashExp->quantidade++;
    hashExp->hashOcupada[calc] = true;
    hashExp->hashRemovido[calc] = false;
}

// Função para ler arquivo CSV
void lerArquivoCSV(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    
    printf("Iniciando leitura do arquivo CSV...\n");
    
    // Pular a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }
    
    // Ler cada linha usando fscanf diretamente na struct
    Aluno* novo;
    while ((novo = new Aluno) != NULL) {

        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
            novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            
            //pega o endereço que deve ser inserido no vetor de alunos
            inserir(novo);
        } else {
            // Se não conseguiu ler todos os campos, liberar memória e sair
            delete novo;
            break;
        }
    }
    
    fclose(arquivo);
    // printf("Leitura concluida. Total de alunos: %d\n", a[0].quantidade);
}

void exibirAlunos() {
    printf("\n=== LISTA DE ALUNOS ===\n");
    
    for (int i = 0; i < a.tamanhoAtual; i++) {
        if(a.hashOcupada[i]) {
            printf ("  Matricula: %s\n", a.hash[i]->matricula);
            printf ("  CPF: %s\n", a.hash[i]->cpf);
            printf ("  Nome: %s\n", a.hash[i]->nome);
            printf ("  Nota: %.2f\n", a.hash[i]->nota);
            printf ("  Idade: %d\n", a.hash[i]->idade);
            printf ("  Curso: %s\n", a.hash[i]->curso);
            printf ("  Cidade: %s\n", a.hash[i]->cidade);
            printf ("  ---\n");
        }  
        
    }
    printf("Total: %d alunos\n\n", a.quantidade);
}

void buscar() {
    char nome[40];

    cout << "Digite o nome do aluno a ser buscado: ";
    scanf(" %39[^\n]", nome);

    // Calcula soma ASCII
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += static_cast<int>(nome[i]);
    }

    int calc = calculoHash(soma);
    int passoRehash = calculoReHash(calc);

    int tentativas = 0;
    bool encontrado = false;

    while ((a.hashOcupada[calc] || a.hashRemovido[calc]) && tentativas < a.tamanhoAtual) {
        if (a.hashOcupada[calc] && strcmp(a.hash[calc]->nome, nome) == 0) {
            cout << "Aluno encontrado: " << a.hash[calc]->nome << endl;
            encontrado = true;
            break;
        }
        calc = (calc + passoRehash) % a.tamanhoAtual;
        tentativas++;
    }

    if (!encontrado) {
        cout << "Aluno nao encontrado." << endl;
    }
}


int main() {
    clock_t inicio, fim;

    inicializa();

    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");

    inicio = clock();
    lerArquivoCSV("alunos_completos.csv");
    fim = clock();

    printf("Tempo de leitura: %d milissegundos\n", (int)(fim - inicio));

    exibirAlunos();
    return 0;
}
