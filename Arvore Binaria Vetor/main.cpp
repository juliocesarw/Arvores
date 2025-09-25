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
bool insereComFor(Aluno * alunoParaInserir);
//============================================================================================
int maiorIndice = 0;

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
    int contador = 0;
    FILE * arq;
    arq = abrir_arquivo("../../textos/alunos_completos.csv", "r");

    while(!feof(arq)){
        Aluno *c = lerAluno();
        fscanf(arq, "%[^,], %[^,], %[^,] , %lf, %d, %[^,], %[^,\n] ", c->matricula, c->cpf, c->nome, &c->nota, &c->idade, c->curso, c->cidade);
        if(insereComFor(c) == false){
            break;
        } 
        contador++;
        if(contador % 100000 == 0){
            cout << "ja coloquei um monte: " << contador << endl;
            system("pause");
        }
    }
    fclose(arq);
}

bool insereComFor(Aluno * alunoParaInserir){
    int indice = 0;
    bool limite = true;
    for (int i = 0; i < TAMANHO; i++)
    {

        
        //para vazamentos
        if(2 * indice + 1  >= TAMANHO || 2 * indice + 2  >= TAMANHO){
            cout << "chegou ao limite\n" << endl;
            cout << "indice: " << indice << endl;
            system("pause");
            limite = false; 
            break;
        }

        //para o maior indice
        if(indice > maiorIndice){
            maiorIndice = indice;
        }
        
        if(a.raiz[indice] == NULL){
            a.raiz[indice] = alunoParaInserir;
            a.insercoes++;
            break;
        }
        else if(strcmp(a.raiz[indice]->nome, alunoParaInserir->nome) < 0){
            //vai para a direita
            indice = 2 * indice + 2;
        }
        else{
            //vai para a esquerda
            indice = 2 * indice + 1;
        }
    }//for
    if(limite == true){
        return true;
    }
    else{
        return false;
    }
    
}


int main() {

    cout << TAMANHO;

    clock_t inicio = clock();
    system("cls");
    inicializa();
    processoLeituraInsercao();
        
    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "\nTempo decorrido: " << tempo << " segundos" << endl;
    cout << "o numero de insercoes foi: " << a.insercoes << endl;
    cout << "ultimo indice: " << maiorIndice << endl;

    //////////////////////////////////////////////////////////////
    /*
    
    O limite foi: 701023
    O numero de insercoes foi: 908
    ultimo indice foi: 701023
    o tempo foi de: 14 segundos
    
    */

    return 0;
}