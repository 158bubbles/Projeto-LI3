/**
* @brief    Ficheiro que contem funções utilizadas para os produtos
* @file     produtos.c
*/
#include "produtos.h"



/**
* @brief                Valida os produtos
* @param [str]          Código de um produto
* @return               Um r que nos diz se um produto é valido (r=1) ou invalido (r=0)
*/
int valid_Produtos (char* str){
  int i,r = 1;
  int l = strlen(str);
  if (l == 6 && (isupper(str[0])) > 0 && (isupper(str[1])) > 0) {
    for (i = 2; i < l-2; i++){
      if (!(isdigit(str[i]))){
          return 0;
      }
    }
  }
  else r = 0;
  return r;
}


/**
* @brief                  Função que lê um ficheiro .txt com a informacao relativa aos produtos
* @param [produtos]       Dados dos produtos
* @param [filePath]       Caminho do ficheiro
*/
void read_Produtos (Dados* produtos, char* filePath){
  FILE* f = fopen(filePath, "r");
  if (f == NULL){
    printf("Ficheiro produtos inexistente\n");
  }
  char str[1024];
  while(fgets(str,1024,f)){
    produtos->lidas++;
    if(valid_Produtos(strtok(str,"\r\n"))){
      if(produtos->size == produtos->ocupados){
        reallocDados(produtos);
      }
      produtos->str[produtos->ocupados] = strdup(str);
      produtos->ocupados++;

    }
  }
  qsort(produtos->str,produtos->ocupados,sizeof(char*),myCompare);
  fclose(f);
}


/**
* @brief                   Função que devolve o espaço ocupado pelos produtos na string
* @param [produtos]        Dados dos produtos
* @return                  Espaço ocupado pelos produtos na string
*/
int getOcupadosP (Dados* produtos){
  return produtos->ocupados;
}


/**
* @brief                   Função que devolve os produtos lidos
* @param [produtos]        Dados dos produtos
* @return                  Produtos lidos
*/
int getLidasP (Dados* produtos){
  return produtos->lidas;
}


/**
* @brief                   Função que devolve um array com os produtos
* @param [i]               Indíce do array str
* @param [produtos]        Dados dos produtos
* @return                  Array com os produtos
*/
char* getProdutoP (int i,Dados* produtos){
  return strdup(produtos->str[i]);
}
