
#include "projetoarvores.c"

int main(){

    if (login()!= 1)
    {
       return 0;
    }   
    Arvore arvore;
    inicializar(&arvore);
    Produto produto;
   int opcao,aux;
    do{
        printf("\n*Menu - Sistema loja*\n");
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
                aux = (rand() % 100);  //numero randomico de 0 a 99.
                produto.matricula = aux;
                if (buscar(arvore.raiz, produto.matricula) == 1){
                    printf("Produto ja cadastrado!\n");
                    break;
                }
                printf("Matricula: %d\n",produto.matricula);
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
