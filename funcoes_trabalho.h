#ifndef FUNCOES_TRABALHO_H
#define FUNCOES_TRABALHO_H
#include "structs_trabalho.h"

void remover_produto(int codigo, ListaProdutos *lista);
void tela_remover_produto(ListaProdutos *lista);
void remover_cliente(char cpf[],ListaCliente *lista);
void tela_remover_cliente(ListaCliente *lista);
void editar_produto(Produto *produto);
void tela_editar_produto(ListaProdutos *lista);
void editar_cliente(Cliente *cliente);
void tela_editar_cliente(ListaCliente *lista);
Produto* buscar_por_codigo(int codigo, ListaProdutos *lista);
void busca_produto(ListaProdutos *lista);
Cliente* buscar_por_cpf(char *cpf, ListaCliente *lista);
void busca_cliente(ListaCliente *lista);
Cliente* criar_cliente();
Produto* criar_produto();
ListaCliente* create_list();
ListaProdutos* create_list_prod();
void tela_cadastrar_cliente(ListaCliente *L);
void tela_cadastrar_produto(ListaProdutos *L);
void listar_clientes(ListaCliente *L);
void listar_produtos(ListaProdutos *L);
void tela_cliente();
void tela_produtos();
void tela_compra();
void tela_inicial();


#endif