#ifndef clientes_h
#define clientes_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct dados{
  int size;
  int ocupados;
  int lidas;
  char **str;
}Dados;

Dados* initDados ();
void freeDados(Dados* d);
void reallocDados (Dados* d);
int myCompare (const void * a, const void * b );
int valid_Clientes (char* str);
void read_Clientes (Dados* clientes,char* filePath);
int getOcupadosC (Dados* clientes);
int getSizeC (Dados* clientes);
int getLidasC (Dados* clientes);
char* getClienteC (int i,Dados* clientes);
char** getSTRdosClientes(Dados* clientes);

#endif
