#ifndef faturacao_h
#define faturacao_h
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "vendas.h"



typedef struct fatura Fatura;


void insereFatura (Fatura* f, Venda *v);
Fatura* initFatura ();
Fatura* cloneFaturas(Fatura* f);
char* getProdutoFatura(Fatura* f);
void freeNodoAVLFatura(Fatura* f);
int getNumeroTotalVendas (Fatura* f, int filial, int mes, int prom);
int getQuantidadePFilial(Fatura* f, int filial);
double getFaturacao (Fatura* f, int filial, int mes, int prom);

#endif
