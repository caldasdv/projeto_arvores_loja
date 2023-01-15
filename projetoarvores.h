// ALUNO: DAVID OSVALDO CALDAS PEREIRA

#ifndef PROJETOARVORES_H
#define PROJETOARVORES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void inicializar(Arvore *arvore);
No *criarNo(Produto produto);
void inserir(Arvore *arvore, Produto produto);
int buscar(No *raiz, int matricula);
No * remover(No *raiz, int matricula);
void alterar(No *raiz, int matricula, int tipo, float preco, int quantidade, int vendido);
void venda(No *raiz, int matricula, int vendido);
void imprimir(No *raiz);
void imprimirArvore(Arvore *arvore);
void iproduto(No * raiz, int i);
void imprimirproduto(Arvore * arvore, int i);
void relatoriovendas(No *raiz);
void imprimirrelatoriovendas(Arvore *arvore);
void relatorioportipo(No *raiz, int i);
void imprimirrelatorioportipo(Arvore *arvore, int i);
int login();


#endif // PROJETOARVORES_H