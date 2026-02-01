#ifndef FUNCOES_TRABALHO_H
#define FUNCOES_TRABALHO_H
#include "structs_trabalho.h"

Cliente* criar_cliente();
Produto* criar_produto();
ListaCliente* create_list();
ListaProdutos* create_list_prod();
void tela_cadastrar_cliente(ListaCliente *L);
void tela_cadastrar_produto(ListaProdutos *L);
void listar_clientes(ListaCliente *L);
void listar_produtos(ListaProdutos *L);
//void tela_editar_cliente();
void tela_editar_produto();
void tela_cliente();
void tela_produtos();
void tela_compra();
void tela_inicial();


#endif