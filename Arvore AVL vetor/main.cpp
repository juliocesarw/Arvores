#include <iostream>
#include <cstdio> 
using namespace std;
#include <cstdlib>
#include <ctype.h>
#include <cstring>
#include <ctime>

#define TAMANHO 1048576

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[70];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    int altura;
};

struct NO{
    Aluno **raiz;
    int insercoes;
};

NO a;

void inicializa(){
    a.raiz = new Aluno*[TAMANHO]();  
    a.insercoes = 0;  
}

//declaracao de funcoes
Aluno *lerAluno();
FILE * abrir_arquivo( const char * arquivo, const char * modo);
void processoLeituraInsercao();
Aluno* adicionarAluno(Aluno * alunoParaInserir, int indice);
int altura(Aluno* no);
int atualizaAltura(int indice);
//============================================================================================
int maiorIndice = 0;

// funcoes

Aluno *lerAluno(){
    Aluno *b = new Aluno;
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
        a.raiz[0] = adicionarAluno(c, 0);
        cout << "a raiz atual e: " << a.raiz[0]->nome << endl;
        system("pause");
    }
    fclose(arq);
    
}

int altura(Aluno* no){
    if(no == NULL) return -1;
    return no->altura;
}

int atualizaAltura(int indice){
    int altEsq = altura(a.raiz[2 * indice + 1]);
    int altDir = altura(a.raiz[2 * indice + 2]);
    int altura_nova = altEsq > altDir ? altEsq : altDir;
    
    return 1 + altura_nova;  
}

Aluno* rotacaoSimplesEsquerda(int indice){

    a.raiz[2 * (2 * indice + 2) + 1] = a.raiz[indice];  

    return a.raiz[2 * indice + 2];
}

Aluno* rotacaoSimplesDireita(int indice){
    a.raiz[2 * (2 * indice + 1) + 2] = a.raiz[indice];
    return a.raiz[2 * indice + 1];
}

Aluno* adicionarAluno(Aluno * alunoParaInserir, int indice){
    
    if(a.raiz[indice] == NULL){
        return alunoParaInserir;
    }
    else{
        int comp = strcmp(a.raiz[indice]->nome, alunoParaInserir->nome);
        if(comp > 0){
            a.raiz[(2 * indice + 1)] = adicionarAluno(alunoParaInserir, (2 * indice + 1));
        }
        else{
            a.raiz[(2 * indice + 2)] = adicionarAluno(alunoParaInserir, (2 * indice + 2));
        } 
    }

    a.raiz[indice]->altura = atualizaAltura(indice);

    int fb = altura(a.raiz[2 * indice + 1]) - altura(a.raiz[2 * indice + 2]);
    // cout << "fator de balanceamento do(a) " << a.raiz[indice]->nome << " e: "<< fb << endl;

    if(fb < -1 && (altura(a.raiz[2 *(2 * indice + 2) + 1]) - altura(a.raiz[2 *(2 * indice + 2) + 2])) < 0){
        cout << "RSE" << endl;
        a.raiz[indice] =  rotacaoSimplesEsquerda(indice);

    }
    else if(fb > 1 && (altura(a.raiz[2 *(2 * indice + 1) + 1]) - altura(a.raiz[2 *(2 * indice + 1) + 2])) > 0){
        cout << "RSD" << endl;
        a.raiz[indice] =  rotacaoSimplesDireita(indice);
    }

    return a.raiz[indice];


}

int main() {

    // cout << TAMANHO;

    // clock_t inicio = clock();
    system("cls");
    inicializa();
    processoLeituraInsercao();
        
    // clock_t fim = clock();
    // double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    // cout << "\nTempo decorrido: " << tempo << " segundos" << endl;
    // cout << "o numero de insercoes foi: " << a.insercoes << endl;
    // cout << "ultimo indice: " << maiorIndice << endl;

    //////////////////////////////////////////////////////////////

    // cout << "altura do filho da esquerda: " << altura(a.raiz[1]) << endl;
    // cout << "altura do filho da direita: " << altura(a.raiz[2]) << endl;
    // cout << "a altura da raiz e: " << a.raiz[0]->altura;

    cout << "filho da esquerda: " << a.raiz[2 * 0 + 1]->nome << endl;
    cout << "filho da direita: " << a.raiz[2 * 0 + 2]->nome << endl;





    return 0;
}