#ifndef produtos_h
#define produtos_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clientes.h"



int valid_Produtos (char* str);
void read_Produtos (Dados* produtos,char* filePath);
int getOcupadosP (Dados* produtos);
int getLidasP (Dados* produtos);
char* getProdutoP (int i,Dados* produtos);
#endif
