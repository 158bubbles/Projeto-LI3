/**
* @brief    Ficheiro que contem funções utilizadas para os clientes
* @file     clientes.c
*/
#include "clientes.h"


/**
* @brief                Inicialização dos dados dos clientes
* @return               Novo dado
*/
Dados* initDados (){
  Dados* d = malloc(sizeof(Dados));
  d->size = 1;
  d->ocupados = 0;
  d->lidas = 0;
  d->str = malloc(sizeof(char*));
  return d;
}


/**
* @brief                Função que desaloca a memória ocupada pelos Dados
* @param [d]            Dados
*/
/*void freeDados(Dados* d){
  int i;
  for(i = 0; i < d->ocupados; i++){
    free(d->str[i]);
    d->str[i] = NULL;
  }
  d->str = NULL;
  free(d);
  d = NULL;
}*/

void freeDados(Dados *l){
    int i;
    for(i = 0;i<l->ocupados;i++)
        free(l->str[i]);
    free(l->str);
    free(l);
}


/**
* @brief                Função que realoca a memoria ocupada pelos Dados
* @param [d]            Dados
*/
/*void reallocDados (Dados* d){
  d->size = 2 * d->size +1;
  d->str = realloc(d->str, sizeof(char*)*d->size);
  char** aux = malloc(sizeof(char*)*d->size);
  int i;
  for(i = 0; i < (d->size-1)/2; i++){
    aux[i] = d->str[i];
  }
  free(d->str);
  d->str = NULL;
  d->str = aux;
}*/

void reallocDados(Dados* lista){
    int i;
    char **tmp = malloc(2*lista->size*sizeof(char*));
    for(i = 0;i<lista->size;i++){
        tmp[i] = lista->str[i];
    }
    free(lista->str);
    lista->str = tmp;
    lista->size *=2;
}


/**
* @brief                Função que compara duas constantes
* @param [a]            Uma constante
* @param [b]            Uma constante
* @return               Resultado desta comparação
*/
int myCompare (const void * a, const void * b ) {
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;

    return strcmp(pa,pb);
}


/**
* @brief                Valida os clientes
* @param [str]          Código de um cliente
* @return               Um r que nos diz se um cliente é valido (r=1) ou invalido (r=0)
*/
int valid_Clientes (char* str){
  int i,r = 1;
  int l = strlen(str);
  if (l == 5 && (isupper(str[0])) > 0) {
    for (i = 1; i < l-1 && r == 1; i++){
      if (!(isdigit(str[i]))) r = 0;
    }
  }
  else r = 0;
  return r;
}


/**
* @brief                  Função que lê um ficheiro .txt com a informacao relativa aos clientes
* @param [clientes]       Dados dos clientes
* @param [filePath]       Caminho do ficheiro
*/
void read_Clientes (Dados* clientes, char* filePath){
  FILE* f = fopen(filePath, "r");
  if (f == NULL){
    printf("Ficheiro clientes inexistente\n");
  }
  char str[1024];

  while(fgets(str,1024,f)){
    clientes->lidas++;
    if(valid_Clientes(strtok(str,"\r\n")) == 1){
      if(clientes->size == clientes->ocupados){
        reallocDados(clientes);
      }
      clientes->str[clientes->ocupados] = strdup(str);
      clientes->ocupados++;

    }
  }
  qsort(clientes->str,clientes->ocupados,sizeof(char*),myCompare);
  fclose(f);
}


/**
* @brief                   Função que devolve o espaço ocupado pelos clientes na string
* @param [produtos]        Dados dos clientes
* @return                  Espaço ocupado pelos produtos na string
*/
int getOcupadosC (Dados* clientes){
  return clientes->ocupados;
}

/**
* @brief                   Função que obtem o tamanho da string
* @param [clientes]        Dados dos clientes
* @return                  Tamanho da string
*/
int getSizeC (Dados* clientes){
  return clientes->ocupados;
}

/**
* @brief                   Função que devolve os clientes lidos
* @param [produtos]        Dados dos clientes
* @return                  Clientes lidos
*/
int getLidasC (Dados* clientes){
  return clientes->lidas;
}

/**
* @brief                   Função que devolve um array com os clientes
* @param [i]               Indíce do array str
* @param [clientes]        Dados dos clientes
* @return                  Array com os clientes
*/
char* getClienteC (int i,Dados* clientes){
  return strdup(clientes->str[i]);
}

char** getSTRdosClientes(Dados* clientes){
  return clientes->str;
}
