//David Osvaldo Caldas Pereira
#include "projetoarvores.h"

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

void alterar(No *raiz, int matricula, int tipo, float preco, int quantidade, int vendido){
    if(raiz != NULL){
        if(raiz->produto.matricula == matricula){
            raiz->produto.tipo = tipo;
            raiz->produto.preco = preco;
            raiz->produto.quantidade = quantidade;
            raiz->produto.vendido = vendido;
        }else{
            if(matricula < raiz->produto.matricula){
                alterar(raiz->esq, matricula, tipo, preco, quantidade, vendido);
            }else{
                alterar(raiz->dir, matricula, tipo, preco, quantidade, vendido);
            }
        }
    }
}

void venda(No *raiz, int matricula, int vendido){
    if(raiz != NULL){
        if(raiz->produto.matricula == matricula){
            raiz->produto.quantidade -= vendido;
            raiz->produto.vendido += vendido;
        }else{
            if(matricula < raiz->produto.matricula){
                venda(raiz->esq, matricula, vendido);
            }else{
                venda(raiz->dir, matricula, vendido);
            }
        }
    }
}

void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esq);
        printf("\nMatricula: %d\n", raiz->produto.matricula);
        printf("Tipo: %d\n", raiz->produto.tipo);
        printf("Preco: %.2f\n", raiz->produto.preco);
        printf("Quantidade: %d\n", raiz->produto.quantidade);
        printf("Vendido: %d\n\n", raiz->produto.vendido);
        imprimir(raiz->dir);
    }
}

void imprimirArvore(Arvore *arvore){
    imprimir(arvore->raiz);
}

void iproduto(No * raiz, int i){
    if (raiz == NULL)
    {
        return;
    }
    
    if (raiz != NULL && raiz->produto.matricula == i){    
        printf("\nMatricula: %d\n", raiz->produto.matricula);
        printf("Tipo: %d\n", raiz->produto.tipo);
        printf("Preco: %.2f\n", raiz->produto.preco);
        printf("Quantidade: %d\n", raiz->produto.quantidade);
        printf("Vendido: %d\n\n", raiz->produto.vendido);

    }
    if (raiz->produto.matricula < i)
    {
        iproduto(raiz->dir, i);
    }
    if (raiz->produto.matricula > i)
    {
        iproduto(raiz->esq, i);
    }
    
}

void imprimirproduto(Arvore * arvore, int i){
    iproduto(arvore->raiz, i);
}

void relatoriovendas(No *raiz){
    if (raiz == NULL)
    {
        return;
    }
    
    if(raiz != NULL && raiz->produto.vendido >= 1){
        relatoriovendas(raiz->esq);
        printf("\nMatricula: %d\n", raiz->produto.matricula);
        printf("Tipo: %d\n", raiz->produto.tipo);
        printf("Vendido: %d\n\n", raiz->produto.vendido);
        relatoriovendas(raiz->dir);
    }
}

void imprimirrelatoriovendas(Arvore *arvore){
    relatoriovendas(arvore->raiz);
}

void relatorioportipo(No *raiz, int i){
    if (raiz == NULL)
    {
        return;
    }
    
    if(raiz != NULL && raiz->produto.tipo == i){
        relatorioportipo(raiz->esq, i);
        printf("\nMatricula: %d\n", raiz->produto.matricula);
        printf("Tipo: %d\n", raiz->produto.tipo);
        printf("Preco: %.2f\n", raiz->produto.preco);
        printf("Quantidade: %d\n", raiz->produto.quantidade);
        printf("Vendido: %d\n\n", raiz->produto.vendido);
        relatorioportipo(raiz->dir, i);
    }
}

void imprimirrelatorioportipo(Arvore *arvore, int i){
    relatorioportipo(arvore->raiz, i);
}

int login(){
    char user[20], pass[20], user2[20], pass2[20];
    int i=0;
    FILE *fp;
    fp = fopen("login.txt", "r");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    printf("*Login*\n");
    printf("Usuario: ");
    scanf("%s", user);
    printf("Senha: ");
    scanf("%s", pass);
    while(!feof(fp)){
        fscanf(fp, "%s %s", user2, pass2 );
        if(strcmp(user, user2) == 0 && strcmp(pass, pass2) == 0){
            printf("\nLogin efetuado com sucesso!\n");
            i++;
        }
    }
    if(i == 0){
        printf("Usuario ou senha incorretos!\n");
        return 0;
    }
    fclose(fp);
    return 1;
}
