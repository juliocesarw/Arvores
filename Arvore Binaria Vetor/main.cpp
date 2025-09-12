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
};

NO a;

void inicializa(){
    a.raiz = new Aluno*[TAMANHO]();    
}

//declaracao de funcoes
Aluno *lerAluno();
FILE * abrir_arquivo( const char * arquivo, const char * modo);
void processoLeituraInsercao();
bool inserirArvore(Aluno * alunoParaInserir);

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
    arq = abrir_arquivo("../../textos/alunos_completos.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
    }
    fclose(arq);
}

bool inserirArvore(Aluno * alunoParaInserir){
    for (int i = 0; i < TAMANHO; i++)
    {
    }
    return true;
}

int main() {

    clock_t inicio = clock();

    inicializa();
    processoLeituraInsercao();

    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "\nTempo decorrido: " << tempo << " segundos" << endl;


    return 0;
}