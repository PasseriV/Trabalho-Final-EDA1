#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "structs_trabalho.h"
#include "funcoes_trabalho.h"

void remover_produto(int codigo, ListaProdutos *lista){
    Produto *p_anterior = lista->head;
    Produto *lixo = NULL;

    printf("Buscando produto de codigo: %d...\n", codigo);

    if (p_anterior->codigo == codigo) {
        printf("Removendo produto do sistema...\n");
        lixo = p_anterior;             
        lista->head = lixo->prox;      
        free(lixo);
        return;
    }

    lixo = p_anterior->prox;

    while(lixo != NULL && lixo->codigo != codigo){
        p_anterior = lixo;
        lixo = lixo->prox;
    }

    if(lixo != NULL){
        printf("Removendo produto do sistema...\n");
        p_anterior->prox = lixo->prox;  
        free(lixo);
    }
    else{
        printf("Produto de codigo %d nao cadastrado!", codigo);
        return;
    }
}

void tela_remover_produto(ListaProdutos *lista){
    int codigo;
    if (lista->head == NULL) {
        printf("Ainda nao ha produtos cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("Digite o codigo do produto que deseja remover do sistema: ");
    scanf("%d", &codigo);
    remover_produto(codigo,lista);
}



void remover_cliente(char cpf[], ListaCliente *lista){
    Cliente *p_anterior = lista->head;
    Cliente *lixo = NULL;

    printf("Buscando cliente de CPF: %s...\n", cpf);

    if (strcmp(p_anterior->cpf, cpf) == 0) {
        printf("Removendo cliente do sistema...\n");
        lixo = p_anterior;             
        lista->head = lixo->prox;      
        free(lixo);
        return;
    }

    lixo = p_anterior->prox;

    while(lixo != NULL && strcmp(lixo->cpf, cpf) != 0){
        p_anterior = lixo;
        lixo = lixo->prox;
    }

    if(lixo != NULL){
        printf("Removendo cliente do sistema...\n");
        p_anterior->prox = lixo->prox;  
        free(lixo);
    }
    else{
        printf("Cliente de CPF %s nao cadastrado!", cpf);
        return;
    }
}


void tela_remover_cliente(ListaCliente *lista){
    char cpf[18];
    if (lista->head == NULL) {
        printf("Ainda nao ha clientes cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("Digite o CPF do cliente que deseja remover do sistema: ");
    scanf("%s", cpf);
    remover_cliente(cpf,lista);
}

void editar_produto(Produto *produto){
    free(produto->nome);
    produto -> nome = malloc(100*sizeof(char));
    printf("Digite novos dados do produto: ");

    printf("Codigo: ");
    scanf("%d", &produto->codigo);
    getchar();

    printf("Nome: ");
    fgets(produto->nome, 100, stdin);
    
    printf("Preco: ");
    scanf("%f", &produto->preco);
    getchar();

    printf("Quantidade: ");
    scanf("%d", &produto->quantidade);
    getchar();
}

void tela_editar_produto(ListaProdutos *lista){
    int codigo;
    if (lista->head == NULL) {
        printf("Ainda nao ha produtos cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("Digite o codigo do produto que deseja editar as informacoes: ");
    scanf("%d", &codigo);
    Produto* produto = buscar_por_codigo(codigo, lista);
    if(produto) editar_produto(produto);
    else{
        printf("Produto de codigo %d nao cadastrado!", codigo);
        return;
    }
}

void editar_cliente(Cliente *cliente){
    free(cliente ->cpf);
    free(cliente ->email);
    free(cliente->nome);
    free(cliente->nascimento);
    cliente ->cpf =  malloc(17 * sizeof(char));
    cliente ->email = malloc(100 * sizeof(char));
    cliente ->nome = malloc(100 * sizeof(char));
    cliente ->nascimento =  malloc(15 * sizeof(char));
    printf("Digite novos dados do cliente: ");

    printf("\nCPF: ");
    scanf(" %[^\n]", cliente->cpf);
    getchar();

    printf("Nome: ");
    fgets(cliente->nome, 100, stdin);

    printf("Email: ");
    fgets(cliente->email, 100, stdin);
    
    printf("Data de nascimento: ");
    fgets(cliente->nascimento, 15, stdin);
}

void tela_editar_cliente(ListaCliente *lista){
    char cpf[18];
    if (lista->head == NULL) {
        printf("Ainda nao ha clientes cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("Digite o CPF do cliente que deseja editar as informacoes: ");
    scanf("%s", cpf);
    Cliente* cliente = buscar_por_cpf(cpf, lista);
    if(cliente) editar_cliente(cliente);
    else{
        printf("Cliente de CPF %s nao cadastrado!", cpf);
        return;
    }
}

Produto* buscar_por_codigo(int codigo, ListaProdutos *lista){
    Produto *p_aux = lista->head;
    printf("Buscando produto de codigo: %d...\n", codigo);
    while(p_aux != NULL && codigo != p_aux->codigo)
        p_aux = p_aux->prox;

    return p_aux;
}

void busca_produto(ListaProdutos *lista){
    int codigo;
    if (lista->head == NULL) {
        printf("Ainda nao ha produtos cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    Produto* produto = buscar_por_codigo(codigo, lista);
    if(produto){
        printf("Produto encontrado!\n");
        printf("Nome: %s | codigo: %d | preco: %.2f | quantidade: %d\n",produto->nome, produto->codigo, produto->preco, produto->quantidade);
        return;
    }
    else{
        printf("Produto de codigo %d nao cadastrado!", codigo);
        return;
    }
}


Cliente* buscar_por_cpf(char *cpf, ListaCliente *lista){
    Cliente *p_aux = lista->head;
    printf("Buscando cliente de CPF: %s...\n", cpf);
    while(p_aux != NULL && strcmp(p_aux->cpf, cpf))
        p_aux = p_aux->prox;
    return p_aux;
}

void busca_cliente(ListaCliente *lista){
    char cpf[18];
    if (lista->head == NULL) {
        printf("Ainda nao ha clientes cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);
    Cliente *cliente =  buscar_por_cpf(cpf, lista);
    if(cliente){
        printf("Cliente encontrado!\n");
        printf("Nome: %s | CPF: %s | Email: %s | Data de nascimento: %s\n",cliente->nome, cliente->cpf, cliente->email,cliente->nascimento);
        return;
    }
    else{
        printf("Cliente de CPF %s nao cadastrado!", cpf);
        return;
    }
}

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
    prod->nome = malloc(100 * sizeof(char)); 
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
        printf("\n ----- Cliente [%d] ----- \n", i+1);

        Cliente *novo_cli = criar_cliente();
        
        if (novo_cli == NULL) {
        printf("Erro: não foi possível criar cliente!\n");
        return;
        }

        printf("\nCPF: ");
        scanf(" %[^\n]", novo_cli->cpf);
        getchar();

        printf("Nome: ");
        fgets(novo_cli->nome, 100, stdin);

        printf("Email: ");
        fgets(novo_cli->email, 100, stdin);
        
        printf("Data de nascimento: ");
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
        printf("\n Nao ha produtos cadastrados!\n");
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

void tela_cliente(){
    Sleep(100);
    system("cls");
    int opcao;
    ListaCliente *lista = NULL;
    lista = create_list();

do{
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
        system("cls");
        break;
    case 3:
        busca_cliente(lista);
        printf("\nPressione ENTER para voltar ao menu");
        getchar();
        getchar();
        system("cls");
        break;
    case 4:
        tela_editar_cliente(lista);
        printf("\nPressione ENTER para voltar ao menu");
        getchar();
        getchar();
        system("cls");
        break;  
    case 5:
        tela_remover_cliente(lista);
        printf("\nPressione ENTER para voltar ao menu");
        getchar();
        getchar();
        system("cls");
        break;
    case 6:
        printf("Voltando para tela inicial.\n");
        tela_inicial();
        break;
    default:
        printf("Opcao invalida, tente novamente!\n");
        Sleep(1000);
        system("cls");
        getchar();
        break;
    }
    
 }while(opcao != 6);

}

void tela_produtos() {
    Sleep(100);
    system("cls");
    int opcao;
    ListaProdutos *lista = create_list_prod(); 

    do {
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
                system("cls");
                break;
            case 3:
                busca_produto(lista);
                printf("\nPressione ENTER para voltar ao menu");
                getchar();
                getchar();
                system("cls");
                break;
            case 4:
                tela_editar_produto(lista);
                printf("\nPressione ENTER para voltar ao menu");
                getchar();
                getchar();
                system("cls");
                break;  
            case 5:
                tela_remover_produto(lista);
                printf("\nPressione ENTER para voltar ao menu");
                getchar();
                getchar();
                system("cls");
                break;
            case 6:
               printf("Voltando para tela inicial.\n");
                tela_inicial();
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
                Sleep(1000);
                getchar();
                getchar();
                system("cls");
                break;
        }

    } while(opcao != 6);
}


void tela_compra(){

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
        Sleep(1000);
        getchar();
        tela_compra();
    }
}

void tela_inicial(){
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
        Sleep(1000);
        getchar();
        tela_inicial();
    }
}