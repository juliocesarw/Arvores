#include <iostream>
#include <cstdio> 
using namespace std;
#include <cstdlib>
#include <ctype.h>
#include <cstring>

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
    arq = abrir_arquivo("../textos/teste.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
        inserirNaArvore(c, a.raiz);
    }
    fclose(arq);
}

bool inserirNaArvore(Aluno * atual, Aluno * no){

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
        //atual-> nome vem antes no alfabeto ou seja, ficara na esquerda
        if(no->esq == NULL){
            //insere
            no->esq = atual->esq;
            return true;
        }
        else{
            inserirNaArvore(atual, no->esq);
        }

    }
    else{
        //atual-> nome vem depois no alfabeto ou seja, ficara na direita
        if(no->dir == NULL){
            //insere
            no->dir = atual->esq;
            return true;
        }
        else{
            inserirNaArvore(atual, no->dir);
        }
    }
    return true;
    
}

int main() {

    inicializa();
    processoLeituraInsercao();
    return 0;
}