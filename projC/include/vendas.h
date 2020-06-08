#ifndef vendas_h
#define vendas_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "produtos.h"
#include "clientes.h"


typedef struct venda Venda;


typedef struct vt VT;


VT* initVendas ();
void freeVendas(VT* v);
void reallocVendas (VT *v);
int binarySearch(char** total, int i, int t, char* str);

int product (char* prod, Dados* produtos);
int price (double preco);
int quantity (int quant);
int promotion (char prom);
int client (char* cli, Dados* clientes);
int month (int mes);
int market (int super);
int valid_Venda (char* prod, double preco,int quant, char prom,char *cli, int mes, int super, Dados* produtos, Dados* clientes);
char* getProduto(Venda*v);
double getPreco(Venda* v);
int getQuantidade(Venda* v);
int getPromocao(Venda* v);
char* getCliente(Venda* v);
int getData (Venda* v);
int getFilial (Venda* v);
void read_Vendas (VT *vendas,Dados* produtos,Dados* clientes,char* filePath);
int getOcupadosV (VT* vendas);
int getLidasV (VT* vendas);
Venda* getVenda(VT* vendas, int i);

#endif
