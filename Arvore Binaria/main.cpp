#include <iostream>
#include <cstdio> 
using namespace std;
#include <cstdlib>
#include <ctype.h>
#include <cstring>
#include <ctime>


struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[70];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *dir;
    Aluno *esq;
};

#define CARGA_MAXIMA 0.6
#define TAMANHO_HASH_INICIAL 1021

struct NO{
    Aluno *raiz;
};

NO a;

void inicializa(){
    a.raiz = NULL;    
}

//declaracao de funcoes
Aluno *lerAluno();
FILE * abrir_arquivo( const char * arquivo, const char * modo);
void processoLeituraInsercao();
bool inserirNaArvore(Aluno * atual, Aluno * no);
void imprimirArvore(Aluno *no, int nivel);
bool buscaPorNome(char * nome, Aluno * no);
void pesquisa();

//============================================================================================

// funcoes

Aluno *lerAluno(){
    Aluno *b = new Aluno;
    b->dir = NULL;
    b->esq = NULL;
    return b;
}

FILE * abrir_arquivo(const char * arquivo, const char * modo){

	FILE * arq;
	arq = fopen(arquivo, modo);
    if (arq == NULL){
        printf("Erro ao abrir o arquivo\n");
    }
	return arq;
}

void processoLeituraInsercao(){
    FILE * arq;
    arq = abrir_arquivo("../../textos/alunos_completos.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
        inserirNaArvore(c, a.raiz);
    }
    fclose(arq);
}

bool inserirNaArvore(Aluno * atual, Aluno * no){

    // printf("\nvou imprimir %s\n", atual->nome);
    // system("pause");
    if(no == NULL){
        a.raiz = atual;
        return true;
    }

    if (strcmp(atual->nome, no->nome) == 0)  {
        //sao iguais
        if(no->esq == NULL){
            //insere
            no->esq = atual;
            return true;
        }
        else{
            //faca com que o no fique logo encima
            atual->esq = no->esq;
            no->esq = atual->esq;
            return true;
        }
    }
    else if(strcmp(atual->nome, no->nome) < 0){
        //atual-> nome vem antes no alfabeto ou seja, ficara na direita
        if(no->dir == NULL){
            //insere
            no->dir = atual;
            return true;
        }
        else{
            inserirNaArvore(atual, no->dir);
        }
    }
    else{
        //atual-> nome vem depois no alfabeto ou seja, ficara na esquerda
        if(no->esq == NULL){
            //insere
            no->esq = atual;
            return true;
        }
        else{
            inserirNaArvore(atual, no->esq);
            return true;
        }

    }
    return true;
    
}

void imprimirArvore(Aluno *no, int nivel) {
    if (no != NULL) {
        // primeiro imprime a subárvore da direita
        imprimirArvore(no->dir, nivel + 1);

        // imprime os espaços de acordo com o nível
        for (int i = 0; i < nivel; i++) {
            printf("   "); // 3 espaços por nível
        }

        // imprime o valor do nó
        printf("%s\n", no->nome);

        // depois imprime a subárvore da esquerda
        imprimirArvore(no->esq, nivel + 1);
    }
}

bool buscaPorNome(char * nome, Aluno * no){
    if(strcmp(nome, no->nome) == 0){
        return true;
    }
    else if(strcmp(nome, no->nome) < 0){
        //vai para a direita
        buscaPorNome(nome, no->dir);
        return true;
    }
    else{
        // vai para esquerda
        buscaPorNome(nome, no->esq);
        return true;
    }
}

void pesquisa(){
    char nome[70];
    cout << "\n\nDigite o nome que deseja buscar: ";
    cin >> nome;
    if(buscaPorNome(nome, a.raiz) == true){
        cout << "\n\nachei" << endl;
    }
    else{
        cout << "\n\nnao achei" << endl;
    }
}

int main() {

    clock_t inicio = clock();

    inicializa();
    processoLeituraInsercao();

    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "\nTempo decorrido: " << tempo << " segundos" << endl;

    pesquisa();

    return 0;
}