#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <iostream>
using namespace std;


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
    else if(strcmp(no->nome, novoAluno->nome) < 0){
        no->dir = adicionarAluno(no->dir, novoAluno);
    }
    else{
        no->esq = adicionarAluno(no->esq, novoAluno);
    }

    atualizaAltura(no);
    
    int fb = fatorBalanceamento(no);
    // cout << fb << endl;
    // system("pause");
    
    if(fb > 1 && altura(no->esq->esq) - altura(no->esq->dir) > 0) {
        //positivo + esq positivo
        // cout << "RSD" << endl;
        return rotacaoSimplesDireita(no);
    }
    if(fb < -1 && altura(no->dir->esq) - altura(no->dir->dir) < 0) {
        // negativo + dir negativo
        // cout << "RSE" << endl;
        return rotacaoSimplesEsquerda(no);
        
    }
    if(fb > 1 && altura(no->esq->esq) - altura(no->esq->dir) < 0) {
        // positivo + esq negativo
        // cout << "RDD" << endl;
        return rotacaoDuplaDireita(no);
    }
    if(fb < -1 && altura(no->dir->esq) - altura(no->dir->dir) > 0) {
        // negativo + dir positivo RDE
        // cout << "RDE" << endl;
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
    arq = abrir_arquivo("../../textos/alunos_completos.csv", "r");

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

Aluno * pesquisar(char * nome, Aluno * raiz){
    if(raiz == NULL){
        return NULL;
    }

    int x = strcmp(nome, raiz->nome);

    if(x == 0){
        return raiz;
    }
    else if(x < 0){
        return pesquisar(nome, raiz->esq);
    }
    else{
        return pesquisar(nome, raiz->dir);
    }

}

void passarValorCasoExclusaoComDoisFilhos(Aluno * destino, Aluno * origem){
//                                        (     no     )(filho menor direita)
    /*
        Essa funcao e exclusivamente para copiar os valores
        do filho menor da direita para o no do pai

        nao foi o chat que fez julio kkkkkkkkkkk

        a funcao e necessaria pq eu nao sei fazer isso mudando o
        endereco de memoria, entao e mais facil fazer a troca
        dos dados
    */

    strcpy(destino->nome, origem->nome);
    strcpy(destino->cpf, origem->cpf);
    strcpy(destino->nome, origem->nome);
    destino->nota = origem->nota;
    destino->idade = origem->idade;
    strcpy(destino->curso, origem->curso);
    strcpy(destino->cidade, origem->cidade);

}

Aluno * excluirAluno(char * nome, Aluno *no){

    if(no == NULL){
        cout << "nome não encontrado" << endl;
        return NULL;
    }

    int comparacaoDosNomes = strcmp(nome, no->nome);

    if(comparacaoDosNomes == 0){

        Aluno *filhoEsq;

        if(no->dir == NULL && no->esq == NULL){
            // no folha
            return NULL;
        }
        else if(no->dir == NULL){
            // "lista encadeada"
            return no->esq;
        }
        else if(no->esq == NULL){
            // "lista encadeada"
            return no->dir;
        }
        else{
            // no tem dois filhos
            if(no->dir->esq == NULL && no->dir->dir == NULL){
                // a direita do no nao tem filho a esquerda
                no->dir->esq = no->esq;
                return no->dir;
            }
            else{
                filhoEsq = no->dir;
                while(filhoEsq->esq != NULL){
                    filhoEsq = filhoEsq->esq;
                }

                passarValorCasoExclusaoComDoisFilhos(no, filhoEsq);   
                no->dir = excluirAluno(filhoEsq->nome, no->dir);
                return no;                
            }
        }
    }
    else if(comparacaoDosNomes < 0){
        no->esq = excluirAluno(nome, no->esq);
    }
    else{
        no->dir = excluirAluno(nome, no->dir);
    }
    atualizaAltura(no);

    //agora faz o balanceamento
    int fb = fatorBalanceamento(no);
    
    if(fb > 1 && altura(no->esq->esq) - altura(no->esq->dir) > 0) {
        // cout << "RSD" << endl;
        return rotacaoSimplesDireita(no);
    }
    if(fb < -1 && altura(no->dir->esq) - altura(no->dir->dir) < 0) {
        // cout << "RSE" << endl;
        return rotacaoSimplesEsquerda(no);
    }
    if(fb > 1 && altura(no->esq->esq) - altura(no->esq->dir) < 0) {
        // cout << "RDD" << endl;
        return rotacaoDuplaDireita(no);
    }
    if(fb < -1 && altura(no->dir->esq) - altura(no->dir->dir) > 0) {
        // cout << "RDE" << endl;
        return rotacaoDuplaEsquerda(no);
    }

    return no;
}

int escolha(){
    
    int op;
    system("cls");
    printf("\t\tMENU\n\n");
    printf("1 - PESQUISAR\n");
    printf("2 - IMPRIMIR\n");
    printf("3 - EXCLUIR\n");
    printf("0 - SAIR\n\n");
    
    printf("Opcao: ");
    scanf("%d", &op);
    getchar();
    return op;
}

void menu(){
    int x;
    do
    {
        x = escolha();
        switch (x)
        {
        case 1:{

            char nome[40];
            cout << "nome a pesquisar: ";
            scanf("%250[^\n]s", nome);
            getchar();
            Aluno * resultadoDaPesquisa = pesquisar(nome, a.raiz);
            
            if(resultadoDaPesquisa != NULL){
                cout << "achei o(a): " << resultadoDaPesquisa->nome << endl;
            }
            else{
                cout << "nao achei o(a): " << nome << endl;
            }
            system("pause");
            break;
            }
        case 2:
            printAVL(a.raiz);
            break;
        case 3:{
            char nome[40];
            cout << "aluno a excluir: ";
            scanf("%250[^\n]s", nome);
            getchar();
            a.raiz = excluirAluno(nome, a.raiz);
            break;
        }
        case 0:
            break;
        default:
            printf("\n\nopcao inválida!!\n\n");
            system("pause");
            break;
        }
    } while (x != 0);
}

int main(){

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////PROCESSO DE LEITURA////////////////////////////////////////////////
    inicializa();
    
    time_t inicio, fim;
    
    inicio = clock();
    processoLeituraInsercao();
    fim = clock();
    
    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    printf("O tempo decorrido foi %lf segundos\n", tempo);
    system("pause");

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////MENU////////////////////////////////////////////////////////

    menu();

    return 0;
}