
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

typedef struct Produto{
    int matricula;
    int tipo; 
    float preco;
    int quantidade;
    int vendido;
}Produto;

typedef struct No{
    Produto produto;
    struct No *esq;
    struct No *dir;
}No;

typedef struct Arvore{
    No *raiz;
    int tam;
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

int buscar(No *raiz, int matricula){
    if(raiz == NULL){
        return 0;
    }else{
        if(raiz->produto.matricula == matricula){
            return 1;
        }else{
            if(matricula < raiz->produto.matricula){
                return buscar(raiz->esq, matricula);
            }else{
                return buscar(raiz->dir, matricula);
            }
        }
    }
}

No * remover(No *raiz, int matricula){
    if(raiz == NULL){
        return NULL;
    }else{
        if(matricula < raiz->produto.matricula){
            raiz->esq = remover(raiz->esq, matricula);
        }else{
            if(matricula > raiz->produto.matricula){
                raiz->dir = remover(raiz->dir, matricula);
            }else{
                if(raiz->esq == NULL && raiz->dir == NULL){
                    free(raiz);
                    raiz = NULL;
                }else{
                    if(raiz->esq == NULL){
                        No *aux = raiz;
                        raiz = raiz->dir;
                        free(aux);
                    }else{
                        if(raiz->dir == NULL){
                            No *aux = raiz;
                            raiz = raiz->esq;
                            free(aux);
                        }else{
                            No *aux = raiz->dir;
                            while(aux->esq != NULL){
                                aux = aux->esq;
                            }
                            raiz->produto = aux->produto;
                            raiz->dir = remover(raiz->dir, aux->produto.matricula);
                        }
                    }
                }
            }
        }
        return raiz;
    }
}

void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esq);
        printf("Matricula: %d", raiz->produto.matricula);
        printf("Tipo: %d", raiz->produto.tipo);
        printf("Preco: %.2f\n", raiz->produto.preco);
        printf("Quantidade: %d", raiz->produto.quantidade);
        printf("Vendido: %d", raiz->produto.vendido);
        imprimir(raiz->dir);
    }
}

void imprimirArvore(Arvore *arvore){
    imprimir(arvore->raiz);
}

void relatoriovendas(No *raiz){
    if(raiz != NULL && raiz->produto.vendido >= 1){
        relatoriovendas(raiz->esq);
        printf("Matricula: %d", raiz->produto.matricula);
        printf("Tipo: %d", raiz->produto.tipo);
        printf("Vendido: %d", raiz->produto.vendido);
    }
}

void imprimirrelatoriovendas(Arvore *arvore){
    relatoriovendas(arvore->raiz);
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

        c = _getwch();
        
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

    int opcao;
    do{
        printf("1 - Inserir produto");
        printf("2 - Remover produto");
        printf("3 - Buscar produto");
        printf("4 - Alterar produto");
        printf("5 - Imprimir todos os produtos");
        printf("6 - vender produto");
        printf("7 - relatorio de vendas");
        printf("8 - Sair");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                printf("Digite o tipo do produto: ");
                scanf("%d", &produto.tipo);
                printf("Digite o preco do produto: ");
                scanf("%f", &produto.preco);
                printf("Digite a quantidade do produto: ");
                scanf("%d", &produto.quantidade);                
                inserir(&arvore, produto);
                break;
            case 2:
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                remover(arvore.raiz, produto.matricula);
                break;
            case 3:
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                if(buscar(arvore.raiz, produto.matricula) == 1){
                    printf("Produto encontrado\n");
                }else{
                    printf("Produto nao encontrado\n");
                }
                break;
            case 4: 
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                if(buscar(arvore.raiz, produto.matricula) == 1){
                    imprimirArvore(&arvore);
                    printf("Digite o tipo do produto: ");
                    scanf("%d", &produto.tipo);
                    printf("Digite o preco do produto: ");
                    scanf("%f", &produto.preco);
                    printf("Digite a quantidade do produto: ");
                    scanf("%d", &produto.quantidade);
                    remover(arvore.raiz, produto.matricula);
                    inserir(&arvore, produto);
                }else{
                    printf("Produto nao encontrado\n");
                }
                break;
            case 5:
                imprimirArvore(&arvore);
                break;
            case 6:
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                if(buscar(arvore.raiz, produto.matricula) == 1){
                    printf("Digite a quantidade de produtos: ");
                    scanf("%d", &produto.quantidade);
                    remover(arvore.raiz, produto.matricula);
                    produto.quantidade--;
                    produto.vendido++;
                    inserir(&arvore, produto);
                }else{
                    printf("Produto nao encontrado\n");
                }
                break;
            case 7:
                imprimirrelatoriovendas(&arvore);
                break;
            case 8:
                printf("Saindo...");
                break;
            default:
                printf("Opcao invalida");
                break;
        }
    }while(opcao != 8);
    
    return 0;
}
