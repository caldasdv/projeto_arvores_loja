
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

    int opcao,op;
    do{
        printf("\n1 - Inserir produto\n");
        printf("2 - Remover produto\n");
        printf("3 - Buscar produto\n");
        printf("4 - Alterar produto\n");
        printf("5 - Imprimir todos os produtos\n");
        printf("6 - vender produto\n");
        printf("7 - relatorio de vendas\n");
        printf("8 - relatorio por tipo\n");
        printf("9 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("\n*Inserir produto*\n\n");
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                if (buscar(arvore.raiz, produto.matricula) == 1){
                    printf("Produto ja cadastrado!\n");
                    break;
                }
                printf("Digite o tipo do produto: ");
                scanf("%d", &produto.tipo);
                printf("Digite o preco do produto: ");
                scanf("%f", &produto.preco);
                printf("Digite a quantidade do produto: ");
                scanf("%d", &produto.quantidade);
                printf("Digite a quantidade vendida do produto: ");
                scanf("%d", &produto.vendido);              
                inserir(&arvore, produto);
                printf("Produto inserido com sucesso!\n");
                break;
            case 2:
                printf("\n*Remover produto*\n\n");
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                remover(arvore.raiz, produto.matricula);
                printf("Produto removido com sucesso!\n");
                break;
            case 3:
                printf("\n*Buscar produto*\n\n");
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                if(buscar(arvore.raiz, produto.matricula) == 1){
                    printf("Produto encontrado\n");
                    imprimirproduto(&arvore, produto.matricula);
                }else{
                    printf("Produto nao encontrado\n");
                }
                break;
            case 4: 
                printf("\n*Alterar produto*\n\n");
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
                    printf("Digite a quantidade vendida do produto: ");
                    scanf("%d", &produto.vendido);
                    alterar(arvore.raiz, produto.matricula, produto.tipo, produto.preco, produto.quantidade, produto.vendido);
                }else{
                    printf("Produto nao encontrado\n");
                }
                break;
            case 5:
                printf("\n*Imprimir todos os produtos*\n\n");
                imprimirArvore(&arvore);
                break;
            case 6:
                float valor,dinheiro;
                printf("\n*Vender produto*\n\n");
                printf("Digite a matricula do produto: ");
                scanf("%d", &produto.matricula);
                if(buscar(arvore.raiz, produto.matricula) == 1){
                    printf("Digite a quantidade de vendas: ");
                    scanf("%d", &produto.vendido);
                    valor = produto.preco * produto.quantidade;
                    printf("Valor total: %.2f\n", valor);
                    printf("Digite o dinheiro: ");
                    scanf("%f", &dinheiro);
                    if (dinheiro < valor)
                    {
                        printf("Dinheiro insuficiente\n");
                        break;
                    }
                    else
                    {
                        dinheiro = dinheiro - valor;
                        printf("Troco: %.2f\n", dinheiro);
                        produto.quantidade = produto.quantidade - produto.vendido;
                        venda(arvore.raiz, produto.matricula, produto.vendido);
                    }                            
                }
                break;
            case 7:
                printf("\n*Relatorio de vendas*\n\n");
                imprimirrelatoriovendas(&arvore);
                break;
            case 8: 

                printf("*Relatorio por tipo*\n\nDigite o tipo do produto: ");
                scanf("%d", &produto.tipo);
                imprimirrelatorioportipo(&arvore, produto.tipo);
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }
    while(opcao != 9);
    
    return 0;    
}
