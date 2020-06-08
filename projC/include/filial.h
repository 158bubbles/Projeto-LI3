#ifndef filial_h
#define filial_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"
#include "tree.h"
#include "clientes.h"


typedef struct filial Filial;

typedef struct codigoProdutosP ProdP;

typedef struct produtosPorCliente PpC;

typedef struct codigoClientes ClieP;

ProdP* initCodigoProduto ();
void insereClienteP (Venda* v,ProdP* p);
PpC* initProdutoCliente ();
void insereProdutoCliente(Venda* v, PpC* p);
char* getNomePpC (PpC* p);
int getQuantidadePpC (PpC* p,int mes);
int getFaturacaoPpC (PpC* p,int mes);
ClieP* initCodigoClientes ();
void updateCodigoCliente(Venda* v, PpC* p);
void insereCodigoCliente(Venda* v, ClieP* c);
int getOcupadosClieP(ClieP* c);
int getQuantidadeClieP (ClieP* c, int mes);
PpC* getPpCClieP(ClieP* c,int i);
Filial* initFilial();
Filial* insereFilial(Filial* f,Venda* v);
int getQuantProdMesCliente (AVL *f,char* cliente,int mes);
Dados* getCodigosClientsN(AVL *f,char* productID);
Dados* getCodigosClientsP(AVL *f,char* productID);
AVL* getAVLProdutos (Filial* f);
AVL* getAVLClientes (Filial* f);
int getCliePCliente(AVL* f, char* clienteID, int month);

void freeProP (ProdP* p);
void freeAVLP (AVL* f);
void freePpC(ClieP* c);
void freeAVLC (AVL* f);
void freeFilial(Filial* f);
#endif
