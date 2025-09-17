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
bool inserirArvore(Aluno * alunoParaInserir, int indice, int i);
// void imprimirIndices(int n);
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
        if(!inserirArvore(c, 0, 0)) break;;
    }
    fclose(arq);
}

int maiorIndice = 0;

bool inserirArvore(Aluno * alunoParaInserir, int indice, int i){

    if(indice > maiorIndice){
        maiorIndice = indice;
    }
    
    if(a.raiz[indice] == NULL){
        a.raiz[indice] = alunoParaInserir;
        a.insercoes++;
        return true;
    }
    else{
        int comp = strcmp(a.raiz[indice]->nome, alunoParaInserir->nome);
        if( comp < 0){
            // menor que zero
            indice = 2 * i + 2;
            return inserirArvore(alunoParaInserir, indice, ++i);
        }   
        else{
            // maior que zero
            indice = 2 * i + 1;
            return inserirArvore(alunoParaInserir, indice , ++i);
        }
    }
    return true;
}

bool insereComFor(Aluno * alunoParaInserir){
    int indice = 0;
    for (int i = 0; i < TAMANHO; i++)
    {
        if(a.raiz[indice] == NULL){
            a.raiz[indice] = alunoParaInserir;
        }
        else if(strcmp(){

        }
    }
    
}

bool buscar(char * nome){
    
    bool achei = false;
    int indice = 0;
    int i = 0;
    int comp;
    do
    {
        comp = strcmp(a.raiz[indice]->nome, nome); 
        if (comp == 0){
            achei = true;
        }
        else if(achei < 0){
            indice = 2 * i++ + 2;
        }
        else{
            indice = 2 * i++ + 1;
        }

    } while ((!achei) || indice >= maiorIndice);
    
    return achei;
}





// void imprimirIndices(int n) {
//     if (n == 0 || a.raiz[0] == nullptr) {
//         cout << "Árvore vazia!\n";
//         return;
//     }

//     for (int i = 0; i < n; i++) {
//         cout << i << ": ";
//         if (a.raiz[i] != NULL) {
//             cout << a.raiz[i]->nome;
//         } else {
//             cout << "(vazio)";
//         }
//         cout << "\n";
//     }
// }


int main() {

    clock_t inicio = clock();
    system("cls");
    inicializa();
    processoLeituraInsercao();
    // imprimirIndices(12);

    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "\nTempo decorrido: " << tempo << " segundos" << endl;
    cout << "o numero de insercoes foi: " << a.insercoes << endl;
    cout << "o maior indice foi: " << maiorIndice << endl;

    // só insere


    return 0;
}