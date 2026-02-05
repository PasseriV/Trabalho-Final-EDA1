#ifndef FUNCOES_TRABALHO_H
#define FUNCOES_TRABALHO_H
#include "structs_trabalho.h"

void carregar_dados_txt(ListaCliente*lista_cli, ListaProdutos *lista_prod);
void salvar_dados_txt(ListaCliente*lista_cli, ListaProdutos *lista_prod);
void listar_produtos_car(ListaCarrinho* lista_car);
void adicionar_produtos_car(int codigo, ListaCarrinho* lista_car, ListaProdutos* lista_prod);
void tela_adicionar_produtos(ListaCarrinho* lista_car, ListaCliente* lista_cli, ListaProdutos* lista_prod);
ListaCarrinho* create_carrinho();
ItemCarrinho* cria_item();
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
Cliente* buscar_por_cpf(char cpf[], ListaCliente *lista);
void busca_cliente(ListaCliente *lista);
Cliente* criar_cliente();
Produto* criar_produto();
ListaCliente* create_list();
ListaProdutos* create_list_prod();
void tela_cadastrar_cliente(ListaCliente *L);
void tela_cadastrar_produto(ListaProdutos *L);
void listar_clientes(ListaCliente *L);
void listar_produtos(ListaProdutos *L);
void tela_cliente(ListaCliente* lista);
void tela_produtos(ListaProdutos* lista);
void tela_compra(ListaCarrinho* lista_car, ListaCliente* lista_cli, ListaProdutos* lista_prod);
void tela_inicial();
void retirar_produto_carrinho(ListaCarrinho* lista_car, ListaProdutos* lista_prod);
void ajusta_cpf(char *cpf_digitado);
#endif