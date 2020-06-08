#ifndef faturacoes_h
#define faturacoes_h
#include "tree.h"
#include "faturacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void freeAVLFatura (AVL* f);
AVL* insereFaturaAVL (VT* v, AVL* t);
int getNumeroTVendAVL (AVL* a,char* prod,int filial, int mes,int prom);
int getQuantidadePFilialAVL (AVL* a,char* prod ,int filial);
int getFaturacaoAVL(AVL* a, char* prod, int filial, int mes, int prom);
int getFaturacaoAVLTotal(AVL* a, int filial, int mes, int prom,int total);
double faturacaoTAVL (AVL* fatura,int minMonth, int maxMonth);
int quantidadeTAVL (AVL* fatura,int minMonth, int maxMonth);

#endif
