# Trabalho Final de EDA 1 - FCTE

**CRUD de Clientes e Produtos**

## Colaboradores

**- Vinícius Passeri Moraes de Souza - 222015041**
-> [@PasseriV](https://github.com/PasseriV)

**- Paolla Leticia Cardoso Quaresma - 190047917**
-> [@plcq](https://github.com/plcq)

## Descrição

Uma empresa de pequeno porte deseja informatizar o controle básico de **clientes** e **produtos** por meio de uma aplicação simples executada no **terminal**.

O objetivo deste trabalho é desenvolver um sistema na linguagem **C** que utilize **listas simplesmente encadeadas** para armazenar e manipular os dados dinamicamente, implementando operações completas de **CRUD**.

---

## Funcionalidades

- Gerenciamento de Clientes
  - Cadastrar cliente (CPF, nome, email, telefone, data de nascimento);
  - Listar todos os clientes;
  - Buscar cliente pelo CPF;
  - Editar dados de um cliente;
  - Remover cliente;
- Gerenciamento de Produtos
  - Cadastrar produto (código único, nome ,preço, quantidade);
  - Listar todos os produtos;
  - Buscar produto pelo código;
  - Editar dados de um produto;
  - Remover produto; 
- Modo Compra
  - Um cliente incluir produtos que deseja comprar no carrinho;
  - Listar os produtos do carrinho de um cliente e informar quantidade de itens e valor total da compra;
  - Retirar os produtos do carrinho de um cliente;

---

## Requisitos Técnicos

- Implementação **exclusivamente em C**;
- Repositório git com contribuição de todos os membros do grupo e espaçados ao longo do tempo;
- Uso obrigatório de **listas simplesmente encadeadas**;
- Uso de **alocação dinâmica de memória** (`malloc`, `calloc`, `realloc` e `free`);
- **Proibido** o uso de variáveis globais;
- Manipulação das listas por **passagem de parâmetros**;
- Menu funcional via terminal;

---

## Organização do projeto:

funcoes_trabalho.c e funcoes_trabalho.h: definição e declaração das funções utilizadas no trabalho;

structs_trabalho.h: declaração das estruturas (listas) utilizadas no trabalho;

main.c: chamada da função principal `tela_inicial()` que inicia o sistema.

---
