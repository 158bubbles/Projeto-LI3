#ifndef print_h
#define print_h
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
#include "interface.h"
#include "queries.h"

void print2 (Q* q,char letter);
void print3(Q3* q, int mes, int filial, char* prod);
void print4(Q* q,int filial);
void print5 (Q* q);
void print6 (Q6* q);
void print7 (Q7* q);
void print8 (Q8* q,int minMes,int maxMes);
void print9 (Q9* q);
void print10 (Q10* q);
void print11 (Q11* q,int limit);
void print12(Q12* q, int limit);
void print13 (Q13* q);


#endif
