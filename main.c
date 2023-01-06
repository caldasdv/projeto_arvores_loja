
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto{
    int matricula;
    int tipo; 
    float preco;
}Produto;

typedef struct No{
    Produto produto;
    struct No *esq;
    struct No *dir;
}No;

typedef struct Arvore{
    No *raiz;
}Arvore;

void flush_in(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

void inicializar(Arvore *arvore){
    arvore->raiz = NULL;
}

No *criarNo(Produto produto){
    No *novo = (No*)malloc(sizeof(No));
    novo->produto = produto;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void inserir(Arvore *arvore, Produto produto){
    No *novo = criarNo(produto);
    if(arvore->raiz == NULL){
        arvore->raiz = novo;
    }else{
        No *atual = arvore->raiz;
        No *anterior;
        while(atual != NULL){
            anterior = atual;
            if(produto.matricula < atual->produto.matricula){
                atual = atual->esq;
            }else{
                atual = atual->dir;
            }
        }
        if(produto.matricula < anterior->produto.matricula){
            anterior->esq = novo;
        }else{
            anterior->dir = novo;
        }
    }
}

void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esq);
        printf("Matricula: %d", raiz->produto.matricula);
        printf("Tipo: %d", raiz->produto.tipo);
        printf("Preco: %.2f\n", raiz->produto.preco);
        imprimir(raiz->dir);
    }
}

void imprimirArvore(Arvore *arvore){
    imprimir(arvore->raiz);
}
int login(){

    char login[21], senha[21],c;
    int i,aux = 2;
    printf("Digite seu login: ");
    for(i=0; i<20; i++)
    {
        login[i] = getchar();
        
        if(login[i] == '\n')
        {
            login[i] = '\0';
            break;
        }
    }
  
    for (int i = 0; i < 20; i)
    {

        if (i <= 0){
            printf("\33[2K\rSenha: ");
            i = 0;
        }

        c = _getch();
        
        if(c == '\n' || c == '\r'){
            senha[i] = '\0';
            break;
        }

        else if (c == '\b'){
            printf("\033[D\033[K");
            i--;
            senha[i] = '\0';
        } 

        else{
            senha[i] = c;
            printf("*");
            i++;
        }
    }

    if(strcmp(login, "admin") == 0 && strcmp(senha, "admin") == 0)
    {
        printf("\nAcesso permitido!\n");
        aux = 1;
    }
    else
    {
        printf("\nAcesso negado!");
        aux = 0;
    }
    return aux;
}

int main(){

    if (login()!= 1)
    {
        return 0;
    }   

    Arvore arvore;
    inicializar(&arvore);
    Produto produto;
    produto.matricula = 1;
    produto.tipo = 1;
    produto.preco = 1.0;
    inserir(&arvore, produto);
    produto.matricula = 2;
    produto.tipo = 2;
    produto.preco = 2.0;
    inserir(&arvore, produto);
    produto.matricula = 3;
    produto.tipo = 3;
    produto.preco = 3.0;
    inserir(&arvore, produto);
    imprimirArvore(&arvore);
    return 0;
}
