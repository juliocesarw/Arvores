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
    int nivel;
};

struct NO{
    Aluno *raiz;
    int altura;
};

NO a;

void inicializa(){
    a.raiz = NULL;    
}

//declaracao de funcoes
Aluno *lerAluno();
FILE * abrir_arquivo( const char * arquivo, const char * modo);
void processoLeituraInsercao();
void imprimirArvore(Aluno *no, int nivel);
bool inserirArvore(Aluno * alunoParaInserir, Aluno * noRaiz, int nivel);
bool buscaPeloNome(char * nome, Aluno * noRaiz);
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
        inserirArvore(c, a.raiz, 0);
    }
    fclose(arq);
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

bool inserirArvore(Aluno * alunoParaInserir, Aluno * noRaiz, int nivel){
    
    if(++nivel > a.altura){
        a.altura = nivel;
    }
    
    if(alunoParaInserir == NULL){
        return false;
    }
    
    if(noRaiz == NULL){
        a.raiz = alunoParaInserir;
        return true;
    }
    else{
        if(strcmp(noRaiz->nome, alunoParaInserir->nome) == 0){
            if(noRaiz->esq == NULL){
                noRaiz->esq = alunoParaInserir;
                return true;
            }
            else{
                return inserirArvore(alunoParaInserir, noRaiz->esq, nivel);
            }
        }
        else if(strcmp(noRaiz->nome, alunoParaInserir->nome) < 0){
            if(noRaiz->dir == NULL){
                noRaiz->dir = alunoParaInserir;
                return true;
            }
            else{
                return inserirArvore(alunoParaInserir, noRaiz->dir, nivel);
            }
        }
        else{
            if(noRaiz->esq == NULL){
                noRaiz->esq = alunoParaInserir;
                return true;
            }
            else{
                return inserirArvore(alunoParaInserir, noRaiz->esq, nivel);
                }
            }
    }
    return true;
}

bool buscaPeloNome(char * nome, Aluno * noRaiz){
    if(noRaiz == NULL) return false;
    if(strcmp(noRaiz->nome, nome) == 0){
        cout << "\nachei: " << noRaiz->nome << endl;
        system("pause");
        return true;
    }
    else if(strcmp(noRaiz->nome, nome) < 0){
        return buscaPeloNome(nome, noRaiz->dir);
    }
    else{
        return buscaPeloNome(nome, noRaiz->esq);
    }
    return false;
}

void pesquisa(){
    char nome[70];
    printf("\n\nDigite o nome para buscar: ");
    fgets(nome, sizeof(nome), stdin);

    // Remove o '\n' do final, se houver
    nome[strcspn(nome, "\n")] = '\0';


    if(buscaPeloNome(nome, a.raiz) == true){
        cout << "\nachei" << endl;
    }
    else{
        cout << "\nnao acheiieieei" << endl;
    }

}

int main() {

    clock_t inicio = clock();

    inicializa();
    processoLeituraInsercao();

    clock_t fim = clock();
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "\nTempo decorrido: " << tempo << " segundos" << endl;
    cout << "\nA altura da arvore e: " << a.altura << endl;

    // imprimirArvore(a.raiz, 0);

    pesquisa();

    return 0;
}