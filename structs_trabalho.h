#ifndef STRUCTS_TRABALHO_H
#define STRUCTS_TRABALHO_H

typedef struct cliente {
    char *cpf;
    char *nome;
    char *email;
    char *nascimento;
    struct cliente *prox;
} Cliente;

typedef struct lista_clientes {
    Cliente *head;
    int size;
} ListaCliente;

typedef struct produto {
    int codigo;
    char *nome;
    float preco;
    int quantidade;
    struct produto *prox;
} Produto;

typedef struct lista_produtos {
    Produto *head;
    int size;
} ListaProdutos;

typedef struct carrinho {
    Produto *produto;
    struct carrinho *prox;
}ItemCarrinho;

typedef struct lista_carrinho {
    ItemCarrinho *head;
    Cliente *cliente;
    int size;
}ListaCarrinho;

#endif