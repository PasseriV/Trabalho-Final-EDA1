#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "structs_trabalho.h"

void tela_inicial();

void tela_editar_cliente(){
    Sleep(100);
    int opcao;
    int cpf;
    char nome[] = "Vinicius Passeri"; // Provisorio so para teste
    system("cls");
    printf("------Editar dados de Cliente------");
    printf("Digite o CPF do cliente: ");
    scanf("%d", &cpf);
    // Aqui vai vir funcao de busca
    printf("\nCliente %s encontrado.", nome);
    // Aqui vem algo para editar
    tela_inicial();
}

void tela_editar_produto(){
    Sleep(100);
    int opcao;
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
    system("cls");
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
    if(opcao == 1) return;
    else if(opcao == 2) return;
    else if(opcao == 3) return;
    else if(opcao == 4) tela_editar_cliente();
    else if(opcao == 5) return;
    else if(opcao == 6) tela_inicial();
    else{
        printf("Opcao invalida, tente novamente!\n");
        tela_cliente();
    }
}

void tela_produtos(){
    int opcao;
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
    if(opcao == 1) return;
    else if(opcao == 2) return;
    else if(opcao == 3) return;
    else if(opcao == 4) tela_editar_produto();
    else if(opcao == 5) return;
    else if(opcao == 6) tela_inicial();
    else{
        printf("Opcao invalida, tente novamente!\n");
        tela_produtos();
    }
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