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
    int nivel;
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
bool inserirArvore(Aluno * alunoParaInserir);
void imprimirArvore();
void imprimirRec(int i, int espacos, int n);
//============================================================================================

// funcoes

Aluno *lerAluno(){
    Aluno *b = new Aluno;
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
        if(!inserirArvore(c)) break;;
    }
    fclose(arq);
}

void imprimirArvore(){
    for (int i = 0; i < TAMANHO; i++)
    {
        if(a.raiz[i] != NULL){
            cout << a.raiz[i]->nome << endl;
        }
    }
}

bool inserirArvore(Aluno * alunoParaInserir){
    for (int i = 0; i < TAMANHO; i++)
    {
        if(i > TAMANHO){
            cout << "Chegou no limite";
            return false;
        }
        if(a.raiz[i] == NULL && i == 0){
            //aqui eu insiro
            a.raiz[i] = alunoParaInserir;
            a.insercoes++;
            return true;
        }
        else if(strcmp(a.raiz[i]->nome, alunoParaInserir->nome) < 0) {
            //vai para a direita +2
            if(a.raiz[2 * i + 2] == NULL){
                a.raiz[2 * i + 2] = alunoParaInserir;
                a.insercoes++;
                return true;
            }
            else{
                i = (2 * i + 2) - 1;
            }
        }
        else{
            //vai para a esquerda +1
            if(a.raiz[2 * i + 1] == NULL){
                a.raiz[2 * i + 1] = alunoParaInserir;
                a.insercoes++;
                return true;
            }
            else{
                i = (2 * i + 1) - 1;
            }
        }
    }
    return true;
}

void imprimirRec(int i, int espacos, int n) {
    if (i >= n || a.raiz[i] == nullptr) return;

    int dir = 2 * i + 2;
    int esq = 2 * i + 1;

    // imprime primeiro o da direita
    imprimirRec(dir, espacos + 5, n);

    // imprime o atual
    for (int j = 0; j < espacos; j++) cout << " ";
    cout << a.raiz[i]->nome << "\n";

    // depois o da esquerda
    imprimirRec(esq, espacos + 5, n);
}

void imprimirArvore(int n) {
    if (n == 0 || a.raiz[0] == nullptr) {
        cout << "Árvore vazia!\n";
        return;
    }
    imprimirRec(0, 0, n);
}


int main() {

    clock_t inicio = clock();
    system("cls");
    inicializa();
    processoLeituraInsercao();
    // imprimirArvore(30);

    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "\nTempo decorrido: " << tempo << " segundos" << endl;
    cout << "o numero de insercoes foi: " << a.insercoes << endl;


    return 0;
}