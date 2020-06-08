#ifndef interface_h
#define interface_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vendas.h"
#include "clientes.h"
#include "produtos.h"
#include "tree.h"
#include "faturacao.h"
#include "faturacoes.h"
#include "filial.h"

typedef struct sgv SGV;

SGV* initSGV();
SGV* loadSGVFromFiles(SGV* sgv, char* clientesFilePath,char* productsFilePath, char* salesFilePath);
void destroySGV (SGV* sgv);
AVL* getAVLProdutosSGV(SGV* sgv,int filial);
AVL* getAVLClientesSGV(SGV* sgv,int filial);
AVL* getAVLFaturasSGV(SGV* sgv);
Dados* getDadosPSGV(SGV* sgv);
Dados* getDadosCSGV(SGV* sgv);
VT* getVendasSGV (SGV* sgv);
int getSGVnumeroTVendas(SGV* sgv,char* prod,int filial, int mes, int prom);
int getSGVquantidadePFilial(SGV* sgv, char* prod,int filial);
int getSGVfaturacaoAVL(SGV* sgv, char* prod,int filial, int mes, int prom);
char* getPathP(SGV*sgv);
char* getPathC(SGV*sgv);
char* getPathV(SGV*sgv);




#endif
