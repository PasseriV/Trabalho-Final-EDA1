#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "structs_trabalho.h"
#include "funcoes_trabalho.h"

void tela_inicial();

Cliente* criar_cliente(){
    Cliente *cli = malloc(sizeof(Cliente));
    if (cli == NULL) return NULL;

    cli ->cpf =  malloc(17 * sizeof(char));
    cli ->email = malloc(100 * sizeof(char));
    cli ->nome = malloc(100 * sizeof(char));
    cli ->nascimento =  malloc(15 * sizeof(char));
    cli ->prox = NULL;

    return cli;

}

Produto* criar_produto(){
    Produto *prod = malloc(sizeof(Produto));
    if (prod == NULL) return NULL;

    prod ->codigo =  0;
    strcpy(prod->nome, ""); 
    prod ->preco = 0.0;
    prod ->quantidade =  0;
    prod ->prox = NULL;

    return prod;

}

ListaCliente* create_list() {
    ListaCliente *L = malloc(sizeof(ListaCliente));
    L->head = NULL;
    L->size = 0;

    return L;
}

ListaProdutos* create_list_prod() {
    ListaProdutos *L = malloc(sizeof(ListaProdutos));
    L->head = NULL;
    L->size = 0;

    return L;
}

void tela_cadastrar_cliente(ListaCliente *L) {
    int qtde_cli = 0;
    
    printf("Quantos clientes voce deseja cadastrar?\n");
    scanf("%d", &qtde_cli);
    getchar();

    for(int i = 0; i< qtde_cli; i++){
        printf("\n ----- Cliente ----- %d \n", i+1);

        Cliente *novo_cli = criar_cliente();
        
        if (novo_cli == NULL) {
        printf("Erro: não foi possível criar cliente!\n");
        return;
        }

        printf("\n CPF: ");
        scanf(" %[^\n]", novo_cli->cpf);
        getchar();

        printf("Nome: ");
        fgets(novo_cli->nome, 100, stdin);
       

        printf("\n Email: ");
        fgets(novo_cli->email, 100, stdin);
        

        printf("\n Data de nascimento: ");
        fgets(novo_cli->nascimento, 15, stdin);
       

        novo_cli->prox = L->head;
        L->head = novo_cli;
        L->size++;

    }

    printf("\nCadastro concluido! Pressione enter para voltar ao menu\n");
    getchar();
}

void tela_cadastrar_produto(ListaProdutos *L) {
    int qtde_prod = 0;
    
    printf("Quantos produtos voce deseja cadastrar?\n");
    scanf("%d", &qtde_prod);
    getchar();  

    for(int i = 0; i < qtde_prod; i++) {
        printf("\n  Produto  %d \n", i+1);

        Produto *novo_prod = criar_produto();

        //verif se há memoria para alocar
        if (novo_prod == NULL) {
            printf("Erro: não foi possível criar produto!\n");
            return;
        }

        printf("Codigo: ");
        scanf("%d", &novo_prod->codigo);
        getchar();

        printf("Nome: ");
        fgets(novo_prod->nome, 100, stdin);
        
        printf("Preco: ");
        scanf("%f", &novo_prod->preco);
        getchar();

        printf("Quantidade: ");
        scanf("%d", &novo_prod->quantidade);
        getchar();

        novo_prod->prox = L->head;
        L->head = novo_prod;
        L->size++;
    }

    printf("\nCadastro concluido! Pressione enter para voltar ao menu\n");
    getchar();
}

void listar_clientes(ListaCliente *L){
    system("cls");

    if (L->head == NULL) {
        printf("\n Nao ha clientes cadastrados!\n");
        return;

    }

    Cliente *atual = L->head;
    int i = 1;
    printf("\n-----------Lista de Clientes------------\n");

    while(atual != NULL){
        printf("\n Cliente %d:\n ", i);
        printf("Nome: %s | CPF: %s | Email: %s | Data de nascimento: %s\n",atual->nome, atual->cpf, atual->email,atual->nascimento);
        atual = atual->prox;
        i++;
    }
}

void listar_produtos(ListaProdutos *L){
    system("cls");

    if (L->head == NULL) {
        printf("\n Nao ha clientes cadastrados!\n");
        return;

    }

    Produto *atual = L->head;
    int i = 1;
    printf("\n-----------Lista de Produtos------------\n");

    while(atual != NULL){
        printf("\n Produto %d:\n ", i);
        printf("Nome: %s | codigo: %d | preco: %.2f | quantidade: %d\n",atual->nome, atual->codigo, atual->preco, atual->quantidade);
        atual = atual->prox;
        i++;
    }
}


/*
void tela_editar_cliente(){
    Sleep(100);
    int opcao;
    int cpf; //(declarei como string no cadastro)
    char nome[] = "Vinicius Passeri"; // Provisorio so para teste
    system("cls");
    printf("------Editar dados de Cliente------");
    printf("Digite o CPF do cliente: ");
    scanf("%d", &cpf);//(declarei como string no cadastro)
    // Aqui vai vir funcao de busca
    printf("\nCliente %s encontrado.", nome);
    // Aqui vem algo para editar
    tela_inicial();
}
    */

void tela_editar_produto(){
    Sleep(100);
    //int opcao;
    int codigo;
    char nome[] = "Arroz"; // Provisorio so para teste
    system("cls");
    printf("------Editar informacoes de produto------");
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    // Aqui vai vir funcao de busca
    printf("\nCliente %s encontrado.", nome);
    // Aqui vem algo para editar
    tela_inicial();
}


void tela_cliente(){
    Sleep(100);
    int opcao;
    ListaCliente *lista = NULL;
    lista = create_list();

do{
    //system("cls");
    printf("------Gerenciamento de clientes------\n");
    printf("Opcoes:\n");
    printf("1- Cadastrar cliente\n");
    printf("2- Listar todos os clientes\n");
    printf("3- Buscar cliente\n");
    printf("4- Editar dados de um cliente\n");
    printf("5- Remover cliente\n");
    printf("6- Retornar para tela inicial\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        tela_cadastrar_cliente(lista);
        break;
    case 2:
        listar_clientes(lista);
        printf("\nPressione ENTER para voltar ao menu");
        getchar();
        getchar();
        break;
    case 3:
        break;
    case 4:
        //tela_editar_cliente();
        printf("nao\n");
        break;  
    case 5:
        printf("nao\n");
        break;
    case 6:
        printf("Voltando para tela inicial.\n");
        tela_inicial();
         break;
    default:
         printf("Opcao invalida, tente novamente!\n");
        break;
    }
    
 }while(opcao != 6);

}

void tela_produtos() {
    Sleep(100);
    int opcao;
    ListaProdutos *lista = create_list_prod(); 

    do {
        system("cls");
        printf("------Gerenciamento de produtos------\n");
        printf("Opcoes:\n");
        printf("1- Cadastrar produto\n");
        printf("2- Listar todos os produtos\n");
        printf("3- Buscar produto\n");
        printf("4- Editar dados de um produto\n");
        printf("5- Remover produto\n");
        printf("6- Retornar para tela inicial\n");
        printf("Escolha a opcao desejada: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                tela_cadastrar_produto(lista);
                break;
            case 2:
                listar_produtos(lista);
                printf("\nPressione ENTER para voltar ao menu");
                getchar();
                break;
            case 3:
                //buscar_produto(lista);
                //printf("\nPressione ENTER para voltar ao menu");
                //getchar();
                break;
            case 4:
                //tela_editar_produto(lista);
                break;  
            case 5:
               // remover_produto(lista);
                break;
            case 6:
               printf("Voltando para tela inicial.\n");
                tela_inicial();
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
                Sleep(1000);
                break;
        }

    } while(opcao != 6);
}


void tela_compra(){

    Sleep(100);
    int opcao;
    system("cls");
    printf("------Modo Compra------");
    printf("Opcoes: \n");
    printf("1- Adicionar produtos ao carrinho\n");
    printf("2- Listar produtos do carrinho\n");
    printf("3- Retirar produtos do carrinho\n");
    printf("4- Retornar para tela inicial\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &opcao);
    if(opcao == 1) return;
    else if(opcao == 2) return;
    else if(opcao == 3) return;
    else if(opcao == 4) tela_inicial();
    else{
        printf("Opcao invalida, tente novamente!\n");
        tela_compra();
    }
}

void tela_inicial(){
    Sleep(100);
    int opcao;
    system("cls");
    printf("====================================================================\n");
    printf("Bem-vindo ao sistema de gerenciamento de clientes e produtos\n");
    printf("====================================================================\n");
    printf("------Opcoes:------\n");
    printf("1- Gerenciamente de Clientes\n");
    printf("2- Gerenciamento de Produtos\n");
    printf("3- Modo Compra\n");
    printf("4- Sair\n");
    printf("Escolha a opcao desejada: ");
    scanf("%d", &opcao);
    printf("\n");

    if(opcao == 1){ 
        tela_cliente();
        getchar();
    }

    else if(opcao == 2) tela_produtos();

    else if(opcao == 3) tela_compra();

    else if(opcao == 4) return;

    else{
        printf("Opcao invalida, tente novamente!\n");
        tela_inicial();
    }
}