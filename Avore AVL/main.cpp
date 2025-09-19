//Exemplo da estrutura de arvore
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string.h>

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

void atualizaAltura(Aluno *no){
    no->esq->altura > no->dir->altura ? no->altura = no->esq->altura + 1 : no->altura = no->dir->altura + 1;
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

    if(strcmp(no->nome, novoAluno->nome) < 0){
        no->dir = adicionarAluno(no->dir, novoAluno);
    }
    else{
        no->esq = adicionarAluno(no->esq, novoAluno);
    }

    atualizaAltura(no);

    int balanceamento;

    if(no->dir == NULL && no->esq == NULL) balanceamento = 0;
    else if(no->esq == NULL){
        balanceamento = 0 - (no->dir->altura + 1);
    } 
    else if(no->dir == NULL){ 
        balanceamento = (no->esq->altura + 1) - 0;
    }
    else{ 
        balanceamento = no->esq->altura - no->dir->altura;
    }



    //Como aplicar as rotações?
    //Aplica rotações conforme o caso
    if(balanceamento > 1 && no->esq->altura > 0) {
        //positivo + esq positivo
        return rotacaoSimplesDireita(no);
    }
    if(balanceamento < -1 && no->dir->altura < 0) {
        // negativo + dir negativo
        return rotacaoSimplesEsquerda(no);
    }
    if(balanceamento > 1 && no->esq->altura < 0) {
        // positivo + esq negativo
        return rotacaoDuplaDireita(no);
    }
    if(balanceamento < -1 && no->dir->altura > 0) {
        // negativo + dir positivo RDE
        return rotacaoDuplaEsquerda(no);
    }

    return no;
}



// Função para ler arquivo CSV
void lerArquivoCSV(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    
    printf("Iniciando leitura do arquivo CSV...\n");
    
    // Pular a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }
    // Ler cada linha usando fscanf diretamente na struct
    Aluno* novo;
    while ((novo = new Aluno) != NULL) {
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {
            

            // Inicializar ponteiros da lista
            novo->dir = NULL;
            novo->esq = NULL;
            novo->altura = 0;
            //pega o endereço que deve ser inserido no vetor de alunos
            adicionarAluno(a.raiz,novo);
            //printf("Aluno adicionado: %s - %s\n", novo->matricula, novo->nome);
            // Consumir a quebra de linha restante
            //fgetc(arquivo);
        } else {
            // Se não conseguiu ler todos os campos, liberar memória e sair
            delete novo;
            break;
        }
    }
    
    fclose(arquivo);
    printf("Leitura concluida. Total de alunos: %d\n", a.quantidade);
}

void printAVL(Aluno* raiz, int espaco = 0, int indent = 6) {
    if (raiz == NULL)
        return;

    espaco += indent;

    // Primeiro imprime o filho da direita
    printAVL(raiz->dir, espaco);

    // Imprime o nó atual (nome do aluno), com espaçamento
    printf("\n%*s\n", espaco, raiz->nome);

    // Depois imprime o filho da esquerda
    printAVL(raiz->esq, espaco);
}

int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    //.....
    time_t inicio, fim;
    inicio = clock();
    // Ler arquivo CSV (você pode alterar o nome do arquivo) Essa função já cria a lista dinâmica com os alunos
    lerArquivoCSV("../../textos/teste.csv");
    printAVL(a.raiz);
    fim = clock();
    //se eu quiser pegar como inteiro o valor do tempo

    double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
    printf("O tempo decorrido foi %lf segundos\n", tempo);

    system("pause");


    return 0;
}