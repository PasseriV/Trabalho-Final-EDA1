#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include "structs_trabalho.h"
#include "funcoes_trabalho.h"

void carregar_dados_txt(ListaCliente*lista_cli, ListaProdutos *lista_prod){
    printf("\033[33m[AVISO]\033[0m Carregando dados do .txt!\n");
    FILE *p_arquivo = fopen("clientes_produtos.txt", "r");
    if(p_arquivo == NULL){
        printf("\033[31m[ERRO]\033[0m Arquivo .txt nao encontrado!\n");
        printf("Para tentar novamente, renicialize o sistema.\n");
        Sleep(1000);
        return;
    }
    int numero, quantidade;
    float num_float;
    fscanf(p_arquivo, "%d", &quantidade);
    lista_cli->size = quantidade;
    for(int i = 1; i <= quantidade; i++){
        Cliente *cliente_cadastrado = criar_cliente();
        fscanf(p_arquivo, " %[^\n]", cliente_cadastrado->cpf);
        fscanf(p_arquivo, " %[^\n]", cliente_cadastrado->nome);
        fscanf(p_arquivo, " %[^\n]", cliente_cadastrado->email);
        fscanf(p_arquivo, " %[^\n]", cliente_cadastrado->telefone);
        fscanf(p_arquivo, " %[^\n]", cliente_cadastrado->nascimento);
        cliente_cadastrado->prox = lista_cli->head;
        lista_cli->head = cliente_cadastrado;
    }
    fscanf(p_arquivo, "%d", &quantidade);
    lista_prod->size = quantidade;
    for(int i = 1; i <= quantidade; i++){
        Produto *produto_cadastrado = criar_produto();
        fscanf(p_arquivo, "%d", &numero);
        produto_cadastrado->codigo = numero;
        fscanf(p_arquivo, " %[^\n]", produto_cadastrado->nome);
        fscanf(p_arquivo, "%f", &num_float);
        produto_cadastrado->preco = num_float;
        fscanf(p_arquivo, "%d", &numero);
        produto_cadastrado->quantidade = numero;
        produto_cadastrado->prox = lista_prod->head;
        lista_prod->head = produto_cadastrado;
    }
    printf("\033[33m[AVISO]\033[0m %d clientes e %d produtos carregados para o sistema!\n", lista_cli->size, lista_prod->size);
    Sleep(1000);
    fclose(p_arquivo);
}

void salvar_dados_txt(ListaCliente*lista_cli, ListaProdutos *lista_prod){
    printf("\033[33m[AVISO]\033[0m Salvando %d clientes e %d produtos!\n", lista_cli->size, lista_prod->size);
    FILE *p_arquivo = fopen("clientes_produtos.txt", "w");
    Cliente *p_aux_cli = lista_cli->head;
    Produto *p_aux_prod = lista_prod->head;
    fprintf(p_arquivo, "%d\n", lista_cli->size);
    while(p_aux_cli != NULL){
        fprintf(p_arquivo, "%s\n", p_aux_cli->cpf);
        fprintf(p_arquivo, "%s\n", p_aux_cli->nome);
        fprintf(p_arquivo, "%s\n", p_aux_cli->email);
        fprintf(p_arquivo, "%s\n", p_aux_cli->telefone);
        fprintf(p_arquivo, "%s\n", p_aux_cli->nascimento);
        p_aux_cli=p_aux_cli->prox;
    }
    fprintf(p_arquivo, "%d\n", lista_prod->size);
    while(p_aux_prod != NULL){
        fprintf(p_arquivo, "%d\n", p_aux_prod->codigo);
        fprintf(p_arquivo, "%s\n", p_aux_prod->nome);
        fprintf(p_arquivo, "%f\n", p_aux_prod->preco);
        fprintf(p_arquivo, "%d\n", p_aux_prod->quantidade);
        p_aux_prod=p_aux_prod->prox;
    }
    fclose(p_arquivo);
}

void listar_produtos_car(ListaCarrinho* lista_car){
    int quantidade_total = 0;
    float preco_total = 0;

    if(lista_car->head==NULL){
        printf("\033[33m[AVISO]\033[0m O carrinho esta vazio.\n");
        return;
    }

    printf("\n\033[1;36m============================== CARRINHO DE COMPRAS =============================\033[0m\n");
    printf("Cliente: \033[1m%s\033[0m\n", lista_car->cliente->nome);

    printf("\033[36m%-30s | %-12s | %-10s\033[0m\n", "PRODUTO", "PRECO (UN)", "QTD");
    printf("\033[36m--------------------------------------------------------------------------------\033[0m\n");

    for(ItemCarrinho*p_aux=lista_car->head; p_aux!=NULL; p_aux = p_aux->prox){
        printf("%-30s | R$ %8.2f | %-10d\n",
               p_aux->produto->nome, p_aux->produto->preco, p_aux->quantidade);

        preco_total+=p_aux->produto->preco*p_aux->quantidade;
        quantidade_total+=p_aux->quantidade;
    }

    printf("\033[36m--------------------------------------------------------------------------------\033[0m\n");
    printf("\033[32m[OK]\033[0m Total: \033[1mR$%.2f\033[0m, %d itens\n", preco_total, quantidade_total);
}

void adicionar_produtos_car(int codigo, ListaCarrinho* lista_car, ListaProdutos* lista_prod){
    Produto* produto = buscar_por_codigo(codigo, lista_prod);

    if(produto == NULL){
        printf("\033[31m[ERRO]\033[0m Produto de codigo %d nao cadastrado!\n", codigo);
        return;
    }
    if(produto->quantidade == 0){
        printf("\033[33m[AVISO]\033[0m Produto esgotado!\n");
        return;
    }

    int quantidade;
    printf("\033[36mDisponivel\033[0m [%d]. Quantos do produto \033[1m%s\033[0m deseja comprar? ",
           produto->quantidade, produto->nome);
    scanf("%d", &quantidade);
    getchar();

    if(quantidade > produto->quantidade){
        printf("\033[31m[ERRO]\033[0m Quantidade pedida maior que o estoque!\n");
        Sleep(1000);
        return;
    }

    ItemCarrinho* item = cria_item();
    item->produto = produto;
    item->prox = lista_car->head;
    lista_car->head = item;
    lista_car->size++;
    item->quantidade += quantidade;

    printf("\033[32m[OK]\033[0m %d unidade(s) de \033[1m%s\033[0m adicionada(s) ao carrinho.\n",
           item->quantidade, item->produto->nome);
}

void tela_adicionar_produtos(ListaCarrinho* lista_car, ListaCliente* lista_cli, ListaProdutos* lista_prod){
    char cpf[18];
    int codigo;

    printf("\033[1;36m=========================== CRIAR / EDITAR CARRINHO ===========================\033[0m\n");
    printf("\033[36mInforme o CPF do cliente para vincular o carrinho.\033[0m\n\n");
    printf("Para criar o carrinho, digite o CPF do cliente: ");

    if (lista_cli->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Ainda nao ha clientes cadastrados!\n");
        Sleep(1000);
        return;
    }
    if(lista_prod->head == NULL){
        printf("\033[33m[AVISO]\033[0m Ainda nao ha produtos cadastrados!\n");
        Sleep(1000);
        return;
    }

    scanf("%s", cpf);
    getchar();
    ajusta_cpf(cpf);

    Cliente* cliente = buscar_por_cpf(cpf, lista_cli);
    if(cliente == NULL){
        printf("\033[31m[ERRO]\033[0m Cliente de CPF %s nao cadastrado!\n", cpf);
        return;
    }

    lista_car->cliente = cliente;

    printf("\n\033[32m[OK]\033[0m Carrinho vinculado ao cliente: \033[1m%s\033[0m\n", lista_car->cliente->nome);
    printf("\033[36m--------------------------------------------------------------------------------\033[0m\n");

    printf("------Carrinho de %s------\n", lista_car->cliente->nome);

    do{
        printf("\nDigite o codigo do produto que deseja adicionar ao carrinho \033[36m(0 para sair)\033[0m: ");
        scanf("%d", &codigo);
        getchar();

        adicionar_produtos_car(codigo, lista_car, lista_prod);

    }while(codigo!=0);

    printf("\n\033[32m[OK]\033[0m Retornando ao menu do Modo Compra...\n");
}

void retirar_produto_carrinho(ListaCarrinho* lista_car, ListaProdutos* lista_prod){
    int codigo;

    if (lista_car->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Nao ha produtos no carrinho!\n");
        Sleep(1000);
        return;
    }

    ItemCarrinho *atual = lista_car->head;

    int i = 1;
    printf("\n\033[1;36m========================== PRODUTOS NO CARRINHO ==========================\033[0m\n");

    while(atual != NULL){
        printf("\n\033[36m[%d]\033[0m ", i);
        printf("Nome: \033[1m%s\033[0m | Codigo: \033[1m%d\033[0m | Quantidade: \033[1m%d\033[0m\n",
               atual->produto->nome, atual->produto->codigo, atual->quantidade);
        atual = atual->prox;
        i++;
    }

    printf("\n\033[36m-------------------------------------------------------------------------\033[0m\n");
    printf("Insira o codigo do produto que deseja remover: ");
    scanf("%d", &codigo);
    while(getchar() != '\n');

    Produto* produto = buscar_por_codigo(codigo, lista_prod);
    if(produto == NULL){
        printf("\033[31m[ERRO]\033[0m Produto de codigo %d nao cadastrado!\n", codigo);
        return;
    }

    ItemCarrinho* anterior = NULL;
    atual = lista_car->head;

    while (atual != NULL && atual->produto->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\033[31m[ERRO]\033[0m Produto de codigo %d nao esta no carrinho!\n", codigo);
        return;
    }

    if (anterior == NULL) {
        lista_car->head = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    printf("\033[33m[AVISO]\033[0m Removendo produto '\033[1m%s\033[0m' do carrinho...\n", atual->produto->nome);
    free(atual);
    printf("\033[32m[OK]\033[0m Produto removido do carrinho.\n");
}

ListaCarrinho* create_carrinho() { 
    ListaCarrinho* L = malloc(sizeof(ListaCarrinho)); 
    L->cliente = malloc(sizeof(Cliente)); 
    L->head = NULL; 
    L->size = 0; 
    return L; 
}

ItemCarrinho* cria_item(){
    ItemCarrinho *item = malloc(sizeof(ItemCarrinho));
    item->produto = malloc(sizeof(Produto));
    item->quantidade = 0;
    item->prox = NULL;

    return item;
}

void remover_produto(int codigo, ListaProdutos *lista){
    Produto *p_anterior = lista->head;
    Produto *lixo = NULL;

    printf("\033[36m[INFO]\033[0m Buscando produto de codigo: \033[1m%d\033[0m...\n", codigo);

    if (p_anterior->codigo == codigo) {
        printf("\033[33m[AVISO]\033[0m Removendo produto do sistema...\n");
        lixo = p_anterior;             
        lista->head = lixo->prox;      
        free(lixo);
        printf("\033[32m[OK]\033[0m Produto removido com sucesso.\n");
        return;
    }

    lixo = p_anterior->prox;

    while(lixo != NULL && lixo->codigo != codigo){
        p_anterior = lixo;
        lixo = lixo->prox;
    }

    if(lixo != NULL){
        printf("\033[33m[AVISO]\033[0m Removendo produto do sistema...\n");
        p_anterior->prox = lixo->prox;  
        free(lixo);
        printf("\033[32m[OK]\033[0m Produto removido com sucesso.\n");
    }
    else{
        printf("\033[31m[ERRO]\033[0m Produto de codigo \033[1m%d\033[0m nao cadastrado!\n", codigo);
        return;
    }
}

void tela_remover_produto(ListaProdutos *lista){
    int codigo;

    if (lista->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Ainda nao ha produtos cadastrados!\n");
        Sleep(1000);
        return;
    }

    printf("\033[1;36m============================= REMOVER PRODUTO =============================\033[0m\n");
    printf("Digite o codigo do produto que deseja remover do sistema: ");

    scanf("%d", &codigo);
    getchar();
    remover_produto(codigo, lista);
}

void ajusta_cpf(char *cpf_digitado){
    int i;
    int j=0;
     for(i=0; cpf_digitado[i] != '\0'; i++){
        if(isdigit((unsigned char)cpf_digitado[i])){ cpf_digitado[j++]=cpf_digitado[i];}
    }
     cpf_digitado[j]= '\0';
}

void remover_cliente(char cpf[], ListaCliente *lista){
    Cliente *p_anterior = lista->head;
    Cliente *lixo = NULL;

    printf("\033[36m[INFO]\033[0m Buscando cliente de CPF: \033[1m%s\033[0m...\n", cpf);

    if (strcmp(p_anterior->cpf, cpf) == 0) {
        printf("\033[33m[AVISO]\033[0m Removendo cliente do sistema...\n");
        lixo = p_anterior;             
        lista->head = lixo->prox;      
        free(lixo);
        printf("\033[32m[OK]\033[0m Cliente removido com sucesso.\n");
        return;
    }

    lixo = p_anterior->prox;

    while(lixo != NULL && strcmp(lixo->cpf, cpf) != 0){
        p_anterior = lixo;
        lixo = lixo->prox;
    }

    if(lixo != NULL){
        printf("\033[33m[AVISO]\033[0m Removendo cliente do sistema...\n");
        p_anterior->prox = lixo->prox;  
        free(lixo);
        printf("\033[32m[OK]\033[0m Cliente removido com sucesso.\n");
    }
    else{
        printf("\033[31m[ERRO]\033[0m Cliente de CPF \033[1m%s\033[0m nao cadastrado!\n", cpf);
        return;
    }
}

void tela_remover_cliente(ListaCliente *lista){
    char cpf[18];

    if (lista->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Ainda nao ha clientes cadastrados!\n");
        Sleep(1000);
        return;
    }

    printf("\033[1;36m============================= REMOVER CLIENTE =============================\033[0m\n");
    printf("Digite o CPF do cliente que deseja remover do sistema: ");

    scanf("%s", cpf);
    getchar();
    ajusta_cpf(cpf);

    remover_cliente(cpf, lista);
}

void editar_produto(Produto *produto){
    free(produto->nome);
    produto->nome = malloc(100*sizeof(char));

    printf("\n\033[1;36m=========================== ATUALIZAR DADOS DO PRODUTO ===========================\033[0m\n");
    printf("\033[36mPreencha os novos dados abaixo:\033[0m\n\n");

    printf("\033[1mCodigo:\033[0m ");
    scanf("%d", &produto->codigo);
    getchar();

    printf("\033[1mNome:\033[0m ");
    scanf(" %[^\n]", produto->nome);
    getchar();
    
    printf("\033[1mPreco:\033[0m ");
    scanf("%f", &produto->preco);
    getchar();

    printf("\033[1mQuantidade (estoque):\033[0m ");
    scanf("%d", &produto->quantidade);
    getchar();

    printf("\n\033[32m[OK]\033[0m Produto atualizado com sucesso.\n");
}

void tela_editar_produto(ListaProdutos *lista){
    int codigo;

    if (lista->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Ainda nao ha produtos cadastrados!\n");
        Sleep(1000);
        return;
    }

    printf("\033[1;36m============================= EDITAR PRODUTO =============================\033[0m\n");
    printf("Digite o codigo do produto que deseja editar as informacoes: ");

    scanf("%d", &codigo);
    getchar();
    Produto* produto = buscar_por_codigo(codigo, lista);

    if(produto) editar_produto(produto);
    else{
        printf("\033[31m[ERRO]\033[0m Produto de codigo \033[1m%d\033[0m nao cadastrado!\n", codigo);
        return;
    }
}

void editar_cliente(Cliente *cliente){
    free(cliente->cpf);
    free(cliente->email);
    free(cliente->nome);
    free(cliente->telefone);
    free(cliente->nascimento);

    cliente->cpf =  malloc(17 * sizeof(char));
    cliente->email = malloc(100 * sizeof(char));
    cliente->nome = malloc(100 * sizeof(char));
    cliente->telefone = malloc(25 * sizeof(char));
    cliente->nascimento =  malloc(15 * sizeof(char));

    printf("\n\033[1;36m=========================== ATUALIZAR DADOS DO CLIENTE ===========================\033[0m\n");
    printf("\033[36mPreencha os novos dados abaixo:\033[0m\n");

    printf("\n\033[1mCPF:\033[0m ");
    scanf(" %[^\n]", cliente->cpf);
    ajusta_cpf(cliente->cpf);
    getchar();

    printf("\033[1mNome:\033[0m ");
    scanf(" %[^\n]", cliente->nome);
    getchar();

    printf("\033[1mEmail:\033[0m ");
    scanf(" %[^\n]", cliente->email);
    getchar();

    printf("\033[1mTelefone:\033[0m ");
    scanf(" %[^\n]", cliente->telefone);
    getchar();
    
    printf("\033[1mData de nascimento:\033[0m ");
    scanf(" %[^\n]", cliente->nascimento);
    getchar();

    printf("\n\033[32m[OK]\033[0m Cliente atualizado com sucesso.\n");
}

void tela_editar_cliente(ListaCliente *lista){
    char cpf[18];

    if (lista->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Ainda nao ha clientes cadastrados!\n");
        Sleep(1000);
        return;
    }

    printf("\033[1;36m============================= EDITAR CLIENTE =============================\033[0m\n");
    printf("Digite o CPF do cliente que deseja editar as informacoes: ");

    scanf("%s", cpf);
    getchar();
    ajusta_cpf(cpf);
    int i, j =0;

    for(i=0; cpf[i] != '\0'; i++){
        if(isdigit((unsigned char)cpf[i])){ cpf[j++]=cpf[i];}
    }
    cpf[j]= '\0';

    Cliente* cliente = buscar_por_cpf(cpf, lista);

    if(cliente) editar_cliente(cliente);
    else{
        printf("\033[31m[ERRO]\033[0m Cliente de CPF \033[1m%s\033[0m nao cadastrado!\n", cpf);
        return;
    }
}

Produto* buscar_por_codigo(int codigo, ListaProdutos *lista){
    Produto *p_aux = lista->head;

    printf("\033[36m[INFO]\033[0m Verificando se existe produto de codigo: \033[1m%d\033[0m...\n", codigo);

    while(p_aux != NULL && codigo != p_aux->codigo)
        p_aux = p_aux->prox;

    return p_aux;
}

void busca_produto(ListaProdutos *lista){
    int codigo;
    if (lista->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Ainda nao ha produtos cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("\033[1mDigite o codigo do produto:\033[0m ");
    scanf("%d", &codigo);
    getchar();

    Produto* produto = buscar_por_codigo(codigo, lista);
    if(produto){
        printf("\033[32m[OK]\033[0m Produto encontrado!\n");
        printf("\033[36mNome:\033[0m %s | \033[36mCodigo:\033[0m %d | \033[36mPreco:\033[0m R$%.2f | \033[36mEstoque:\033[0m %d\n",
               produto->nome, produto->codigo, produto->preco, produto->quantidade);
        return;
    }
    else{
        printf("\033[31m[ERRO]\033[0m Produto de codigo %d nao cadastrado!\n", codigo);
        return;
    }
}

Cliente* buscar_por_cpf(char cpf[], ListaCliente *lista){
    Cliente *p_aux = lista->head;

    printf("\033[36m[INFO]\033[0m Verificando se existe cliente de CPF: \033[1m%s\033[0m...\n", cpf);

    while(p_aux != NULL && strcmp(p_aux->cpf, cpf))
        p_aux = p_aux->prox;

    return p_aux;
}

void busca_cliente(ListaCliente *lista){
    char cpf[18];
    if (lista->head == NULL) {
        printf("\033[33m[AVISO]\033[0m Ainda nao ha clientes cadastrados!\n");
        Sleep(1000);
        return;
    }
    printf("\033[1mDigite o CPF do cliente:\033[0m ");
    scanf("%s", cpf);
    getchar();
    ajusta_cpf(cpf);

    Cliente *cliente =  buscar_por_cpf(cpf, lista);
    if(cliente){
        printf("\033[32m[OK]\033[0m Cliente encontrado!\n");
        printf("\033[36mNome:\033[0m %s | \033[36mCPF:\033[0m %s | \033[36mEmail:\033[0m %s | \033[36mTelefone:\033[0m %s | \033[36mNascimento:\033[0m %s\n",
               cliente->nome, cliente->cpf, cliente->email, cliente->telefone, cliente->nascimento);
        return;
    }
    else{
        printf("\033[31m[ERRO]\033[0m Cliente de CPF %s nao cadastrado!\n", cpf);
        return;
    }
}

Cliente* criar_cliente(){
    Cliente *cli = malloc(sizeof(Cliente));
    if (cli == NULL) return NULL;

    cli ->cpf =  malloc(17 * sizeof(char));
    cli ->email = malloc(100 * sizeof(char));
    cli ->nome = malloc(100 * sizeof(char));
    cli ->telefone = malloc(25 * sizeof(char));
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

    printf("\033[1;36m============================= CADASTRO DE CLIENTES =============================\033[0m\n");
    printf("Quantos clientes voce deseja cadastrar? ");
    scanf("%d", &qtde_cli);
    getchar();

    for(int i = 0; i< qtde_cli; i++){
        printf("\n\033[36m------------------------------ CLIENTE [%d/%d] ------------------------------\033[0m\n", i+1, qtde_cli);

        Cliente *novo_cli = criar_cliente();

        printf("\033[1mCPF:\033[0m ");
        scanf(" %[^\n]", novo_cli->cpf);
        ajusta_cpf(novo_cli->cpf);
        getchar();
        Cliente *Existe_cli = buscar_por_cpf(novo_cli->cpf, L);
        
        if(Existe_cli != NULL){
            printf("\033[31m[ERRO]\033[0m CPF ja cadastrado! Pressione Enter para retornar ao gerenciamento de clientes\n");
            getchar();
            return;
        }

        printf("\033[1mNome:\033[0m ");
        scanf(" %[^\n]", novo_cli->nome);
        getchar();

        printf("\033[1mEmail:\033[0m ");
        scanf(" %[^\n]", novo_cli->email);
        getchar();

        printf("\033[1mTelefone:\033[0m ");
        scanf(" %[^\n]", novo_cli->telefone);
        getchar();
        
        printf("\033[1mData de nascimento:\033[0m ");
        scanf(" %[^\n]", novo_cli->nascimento);
        getchar();

        novo_cli->prox = L->head;
        L->head = novo_cli;
        L->size++;
    }

    printf("\n\033[32m[OK]\033[0m Cadastro concluido! Pressione ENTER para voltar ao menu.\n");
    getchar();
}

void tela_cadastrar_produto(ListaProdutos *L) {
    int qtde_prod = 0;
    
    printf("\033[1;36m============================= CADASTRO DE PRODUTOS =============================\033[0m\n");
    printf("Quantos produtos voce deseja cadastrar? ");
    scanf("%d", &qtde_prod);
    getchar();  

    for(int i = 0; i < qtde_prod; i++) {
        printf("\n\033[36m------------------------------ PRODUTO [%d/%d] ------------------------------\033[0m\n", i+1, qtde_prod);

        Produto *novo_prod = criar_produto();

        if (novo_prod == NULL) {
            printf("\033[31m[ERRO]\033[0m Nao foi possivel criar produto!\n");
            return;
        }

        printf("\033[1mCodigo:\033[0m ");
        scanf("%d", &novo_prod->codigo);
        getchar();

        Produto *Existe_prod = buscar_por_codigo(novo_prod->codigo, L);
        
        if(Existe_prod != NULL){
            printf("\033[31m[ERRO]\033[0m Codigo ja cadastrado! Pressione Enter para retornar ao gerenciamento de produtos\n");
            getchar();
            return;
        }

        printf("\033[1mNome:\033[0m ");
        scanf(" %[^\n]", novo_prod->nome);
        getchar();
        
        printf("\033[1mPreco:\033[0m ");
        scanf("%f", &novo_prod->preco);
        getchar();

        printf("\033[1mQuantidade (estoque):\033[0m ");
        scanf("%d", &novo_prod->quantidade);
        getchar();

        novo_prod->prox = L->head;
        L->head = novo_prod;
        L->size++;
    }

    printf("\n\033[32m[OK]\033[0m Cadastro concluido! Pressione ENTER para voltar ao menu.\n");
    getchar();
}

void listar_clientes(ListaCliente *L){

    if (L->head == NULL) {
        printf("\n\033[33m[AVISO]\033[0m Nao ha clientes cadastrados!\n");
        return;
    }

    Cliente *atual = L->head;
    int i = 1;

    printf("\n\033[1;36m============================== LISTA DE CLIENTES ==============================\033[0m\n");
    printf("\033[36m%-3s | %-26s | %-14s | %-22s | %-14s | %-12s\033[0m\n",
           "#", "NOME", "CPF", "EMAIL", "TELEFONE", "NASC.");
    printf("\033[36m--------------------------------------------------------------------------------\033[0m\n");

    while(atual != NULL){
        printf("%-3d | %-26s | %-14s | %-22s | %-14s | %-12s\n",
               i, atual->nome, atual->cpf, atual->email, atual->telefone, atual->nascimento);
        atual = atual->prox;
        i++;
    }
}

void listar_produtos(ListaProdutos *L){
    system("cls");

    if (L->head == NULL) {
        printf("\n\033[33m[AVISO]\033[0m Nao ha produtos cadastrados!\n");
        return;
    }

    Produto *atual = L->head;
    int i = 1;

    printf("\n\033[1;36m============================== LISTA DE PRODUTOS ==============================\033[0m\n");
    printf("\033[36m%-3s | %-30s | %-6s | %-10s | %-10s\033[0m\n",
           "#", "NOME", "COD", "PRECO", "ESTOQUE");
    printf("\033[36m--------------------------------------------------------------------------------\033[0m\n");

    while(atual != NULL){
        printf("%-3d | %-30s | %-6d | R$ %7.2f | %-10d\n",
               i, atual->nome, atual->codigo, atual->preco, atual->quantidade);
        atual = atual->prox;
        i++;
    }
}

void tela_cliente(ListaCliente* lista){
    Sleep(100);
    int opcao;

    do{
        system("cls");

        printf("\033[1;36m======================================================================\033[0m\n");
        printf("\033[1;36m   GERENCIAMENTO DE CLIENTES\033[0m\n");
        printf("\033[1;36m======================================================================\033[0m\n\n");

        printf("\033[1mSelecione uma opcao:\033[0m\n");
        printf("  \033[36m[1]\033[0m Cadastrar cliente\n");
        printf("  \033[36m[2]\033[0m Listar todos os clientes\n");
        printf("  \033[36m[3]\033[0m Buscar cliente\n");
        printf("  \033[36m[4]\033[0m Editar dados de um cliente\n");
        printf("  \033[36m[5]\033[0m Remover cliente\n");
        printf("  \033[36m[6]\033[0m Voltar\n");
        printf("\033[36m----------------------------------------------------------------------\033[0m\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        while(getchar() != '\n');

        printf("\n");

        switch (opcao)
        {
        case 1:
            tela_cadastrar_cliente(lista);
            break;

        case 2:
            listar_clientes(lista);
            printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
            break;

        case 3:
            busca_cliente(lista);
            printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
            break;

        case 4:
            tela_editar_cliente(lista);
            printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
            break;  

        case 5:
            tela_remover_cliente(lista);
            printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
            break;

        case 6:
            printf("\033[32m[OK]\033[0m Voltando para a tela inicial...\n");
            Sleep(500);
            return;

        default:
            printf("\033[31m[ERRO]\033[0m Opcao invalida! Tente novamente.\n");
            Sleep(900);
            break;
        }
        
    }while(opcao != 6);
}

void tela_produtos(ListaProdutos* lista) {
    Sleep(100);
    int opcao;

    do {
        system("cls");

        printf("\033[1;36m======================================================================\033[0m\n");
        printf("\033[1;36m   GERENCIAMENTO DE PRODUTOS\033[0m\n");
        printf("\033[1;36m======================================================================\033[0m\n\n");

        printf("\033[1mSelecione uma opcao:\033[0m\n");
        printf("  \033[36m[1]\033[0m Cadastrar produto\n");
        printf("  \033[36m[2]\033[0m Listar todos os produtos\n");
        printf("  \033[36m[3]\033[0m Buscar produto\n");
        printf("  \033[36m[4]\033[0m Editar dados de um produto\n");
        printf("  \033[36m[5]\033[0m Remover produto\n");
        printf("  \033[36m[6]\033[0m Voltar\n");
        printf("\033[36m----------------------------------------------------------------------\033[0m\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        while(getchar() != '\n'); 

        printf("\n");

        switch (opcao) {
            case 1:
                tela_cadastrar_produto(lista);
                break;

            case 2:
                listar_produtos(lista);
                printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 3:
                busca_produto(lista);
                printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 4:
                tela_editar_produto(lista);
                printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 5:
                tela_remover_produto(lista);
                printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 6:
                printf("\033[32m[OK]\033[0m Voltando para a tela inicial...\n");
                Sleep(500);
                return;

            default:
                printf("\033[31m[ERRO]\033[0m Opcao invalida! Tente novamente.\n");
                Sleep(900);
                break;
        }

    } while (opcao != 6);
}

void tela_compra(ListaCarrinho* lista_car, ListaCliente* lista_cli, ListaProdutos* lista_prod){
    Sleep(100);
    int opcao;

    do {
        system("cls");

        printf("\033[1;36m======================================================================\033[0m\n");
        printf("\033[1;36m   MODO COMPRA\033[0m\n");
        printf("\033[1;36m======================================================================\033[0m\n\n");

        printf("\033[1mSelecione uma opcao:\033[0m\n");
        printf("  \033[36m[1]\033[0m Adicionar produtos ao carrinho\n");
        printf("  \033[36m[2]\033[0m Listar produtos do carrinho\n");
        printf("  \033[36m[3]\033[0m Retirar produtos do carrinho\n");
        printf("  \033[36m[4]\033[0m Voltar\n");
        printf("\033[36m----------------------------------------------------------------------\033[0m\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        while(getchar() != '\n');

        printf("\n");

        switch (opcao) {
            case 1:
                tela_adicionar_produtos(lista_car, lista_cli, lista_prod);
                printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 2:
                listar_produtos_car(lista_car);
                printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 3:
                retirar_produto_carrinho(lista_car, lista_prod);
                printf("\n\033[36m----------------------------------------------------------------------\033[0m\n");
                printf("Pressione ENTER para voltar ao menu...");
                getchar();
                break;

            case 4:
                printf("\033[32m[OK]\033[0m Voltando para a tela inicial...\n");
                Sleep(500);
                return;

            default:
                printf("\033[31m[ERRO]\033[0m Opcao invalida! Tente novamente.\n");
                Sleep(900);
                break;
        }

    } while (opcao != 4);
}

void tela_inicial(){
    int opcao;
    char escolha_salvar;
    ListaCarrinho *lista_car = create_carrinho();
    ListaProdutos *lista_prod = create_list_prod();
    ListaCliente *lista_cli = create_list();
    printf("Deseja carregar dados salvos no .txt \033[36m[Y]/[N]\033[0m?\n");
    scanf("%c", &escolha_salvar);
    if(escolha_salvar == 'Y') carregar_dados_txt(lista_cli, lista_prod);

    do {
        system("cls");

        printf("\033[1;36m======================================================================\033[0m\n");
        printf("\033[1;36m   SISTEMA - GERENCIAMENTO DE CLIENTES, PRODUTOS E MODO COMPRA\033[0m\n");
        printf("\033[1;36m======================================================================\033[0m\n\n");

        printf("\033[1mSelecione uma opcao:\033[0m\n");
        printf("  \033[36m[1]\033[0m Gerenciamento de Clientes\n");
        printf("  \033[36m[2]\033[0m Gerenciamento de Produtos\n");
        printf("  \033[36m[3]\033[0m Modo Compra\n");
        printf("  \033[36m[4]\033[0m Sair\n");
        printf("\033[36m----------------------------------------------------------------------\033[0m\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        while(getchar() != '\n'); 

        printf("\n");

        switch (opcao) {
            case 1:
                tela_cliente(lista_cli);
                break;

            case 2:
                tela_produtos(lista_prod);
                break;

            case 3:
                tela_compra(lista_car, lista_cli, lista_prod);
                break;

            case 4:
                printf("Deseja salvar os dados \033[36m[Y]/[N]\033[0m?\n");
                scanf("%c", &escolha_salvar);
                getchar();
                if(escolha_salvar == 'Y') salvar_dados_txt(lista_cli, lista_prod);
                printf("\033[32m[OK]\033[0m Encerrando o sistema...\n");
                Sleep(800);
                break;

            default:
                printf("\033[31m[ERRO]\033[0m Opcao invalida! Tente novamente.\n");
                Sleep(900);
                break;
        }

    } while (opcao != 4);
}
