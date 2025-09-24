//Exemplo da estrutura de arvore
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <iostream>
using namespace std;

// using namespace std;

//Exemplo do arquivo CSV que será lido
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
    Aluno* esq;
    Aluno* dir;
    int altura;
};

struct Alunos{
    Aluno *raiz;
    int quantidade;
    int tamanhoAtual;
};

Alunos a;

void inicializa(){
    a.quantidade = 0;
    a.tamanhoAtual = 0;
    a.raiz = NULL;
}

int altura(Aluno *no) {
    if (no == NULL) return -1; // ou 0, depende da sua convenção
    return no->altura;
}

void atualizaAltura(Aluno *no) {
    if (no != NULL) {
        int altEsq = altura(no->esq);
        int altDir = altura(no->dir);
        no->altura = 1 + (altEsq > altDir ? altEsq : altDir);
    }
}

int fatorBalanceamento(Aluno *no){
    return altura(no->esq) - altura(no->dir);
}

Aluno* rotacaoSimplesDireita(Aluno *x) {
    Aluno * y = x->esq;
    Aluno * y2 = y->dir;

    y->dir = x;
    x->esq = y2;

    atualizaAltura(x);
    atualizaAltura(y);

    return y;

}

Aluno* rotacaoSimplesEsquerda(Aluno *x) {
    Aluno *y = x->dir;
    Aluno *T2 = y->esq;

    // Executa a rotação
    y->esq  = x;
    x->dir = T2;

    // Atualiza alturas
    atualizaAltura(x);
    atualizaAltura(y);

    // Novo nó raiz
    return y;
}

Aluno* rotacaoDuplaEsquerda(Aluno *z) { //Direita-Esquerda
    // Primeiro uma rotação simples à direita em z->dir
    z->dir = rotacaoSimplesDireita(z->dir);
    // Depois rotação simples à esquerda em z
    return rotacaoSimplesEsquerda(z);
}

Aluno* rotacaoDuplaDireita(Aluno *z) { //Esquerda-Direita
    
    z->esq = rotacaoSimplesEsquerda(z->esq);

    return rotacaoSimplesDireita(z);
}

Aluno* adicionarAluno(Aluno *no, Aluno *novoAluno){
    if(no == NULL){
        a.quantidade++;
        return no = novoAluno;
    }

    if(strcmp(no->nome, novoAluno->nome) == 0){
        no->esq = adicionarAluno(no->esq, novoAluno);
    }
    else if(strcmp(no->nome, novoAluno->nome) < 0){
        no->dir = adicionarAluno(no->dir, novoAluno);
    }
    else{
        no->esq = adicionarAluno(no->esq, novoAluno);
    }

    atualizaAltura(no);

    int fb = fatorBalanceamento(no);
    
    //Como aplicar as rotações?
    //Aplica rotações conforme o caso
    if(fb > 1 && (altura(no->esq) - altura(no->dir)) >= 0) {
        //positivo + esq positivo
        return rotacaoSimplesDireita(no);
    }
    if(fb < -1 && (altura(no->esq) - altura(no->dir)) <= 0) {
        // negativo + dir negativo
        return rotacaoSimplesEsquerda(no);
         
    }
    if(fb > 1 && (altura(no->esq) - altura(no->dir)) < 0) {
        // positivo + esq negativo
        return rotacaoDuplaDireita(no);
    }
    if(fb < -1 && (altura(no->esq) - altura(no->dir)) > 0) {
        // negativo + dir positivo RDE
        return rotacaoDuplaEsquerda(no);
    }

    return no;
}

Aluno *lerAluno(){
    Aluno *b = new Aluno;
    b->dir = NULL;
    b->esq = NULL;
    b->altura = 0;
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
    arq = abrir_arquivo("../../textos/teste.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
        a.raiz = adicionarAluno(a.raiz, c);
    }
    fclose(arq);
}

void printAVL(Aluno *raiz, int nivel = 0) {
    if (raiz == NULL) return;

    // imprime primeiro o lado direito
    printAVL(raiz->dir, nivel + 1);

    // indentação conforme o nível da árvore
    for (int i = 0; i < nivel; i++) {
        printf("    "); // 4 espaços por nível
    }

    // imprime o nome do aluno e a altura do nó
    printf("%s (h=%d)\n", raiz->nome, raiz->altura);

    // imprime o lado esquerdo
    printAVL(raiz->esq, nivel + 1);
}


int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    //.....
    time_t inicio, fim;
    inicio = clock();
    processoLeituraInsercao();
    system("cls");
    printAVL(a.raiz);
    
    system("pause");
    fim = clock();
    //se eu quiser pegar como inteiro o valor do tempo

    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    printf("O tempo decorrido foi %lf segundos\n", tempo);

    system("pause");


    return 0;
}