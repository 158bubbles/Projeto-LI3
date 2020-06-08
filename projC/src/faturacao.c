/**
* @file                 faturacao.c
* @brief                Modulo que inicializa e controi a estrutura faturacao
*/

#include "faturacao.h"


struct fatura {
      char* produto;
      int numeroTotalVendas [3][12][2];
      int quantPorFilial [3];
      double faturaTotal [3][12][2];
};


void freeNodoAVLFatura(Fatura* f){
  free(f->produto);
  free(f);
}

/**
* @brief                Insere uma venda numa fatura
* @param [f]            Estrutura fatura
* @param [v]            Estrutura venda que vai ser inserida.
*/

void insereFatura (Fatura* f, Venda *v){
  int data,filial,prom;
  data = getData(v);
  filial = getFilial(v);
  prom = getPromocao(v);
  f->produto = getProduto(v);
  f->numeroTotalVendas[filial-1][data-1][prom]++;
  f->quantPorFilial[filial-1] += getQuantidade(v);
  f->faturaTotal[filial-1][data-1][prom] += getPreco(v)*getQuantidade(v);
}

/**
* @brief                Inicialização das faturas
* @return               Nova fatura
*/
Fatura* initFatura (){
  int i,j,k;
  Fatura* f = malloc(sizeof(Fatura));
  for(i = 0; i < 3; i++){
    f->quantPorFilial[i] = 0;
    for(j = 0; j < 12; j++){
      for(k = 0; k < 2; k++){
        f->numeroTotalVendas[i][j][k] = 0;
        f->faturaTotal[i][j][k] = 0;
      }
    }
  }
  return f;
}

/**
* @brief                Cria um clone de uma fatura
* @param [f]            Fatura que vai ser clonizada
* @return               Fatura clone
*/
Fatura* cloneFaturas(Fatura* f){
  Fatura* a = malloc(sizeof(Fatura));
  int i, j, k;
  a->produto = strdup(f->produto);
  for(i = 0; i < 3; i++){
    a->quantPorFilial[i] = f->quantPorFilial[i];
    for(j = 0; j < 12; j++){
      for(k = 0; k < 2; k++){
        a->numeroTotalVendas[i][j][k] = f->numeroTotalVendas[i][j][k];
        a->faturaTotal[i][j][k] = f->faturaTotal[i][j][k];
      }
    }
  }
  return a;
}

/**
* @brief                Retorna o produto de uma fatura
* @param [f]            Estrutura fatura
* @return               Produto de uma fatura
*/
char* getProdutoFatura(Fatura* f){
  return f->produto;
}

/**
* @brief                Obtem o numero total de vendas dado o mês, a filial e o tipo de promoção
* @param [f]            Estrutura fatura
* @param [filial]       Inteiro que determina a filial (filial = 0 -> todas as filials)
* @param [mes]          Inteiro que determina o mes
* @param [prom]         Inteiro que determina a tipo de promocao (prom = 0 -> N e prom = 1 -> P)
* @return               Retorna o numero total de vendas
*/
int getNumeroTotalVendas (Fatura* f, int filial, int mes, int prom){
  if(filial == 0)
    return f->numeroTotalVendas[0][mes-1][prom]+f->numeroTotalVendas[1][mes-1][prom]+ f->numeroTotalVendas[2][mes-1][prom];
  return f->numeroTotalVendas[filial-1][mes-1][prom];
}


/**
* @brief                Obtem a quantidade total dada a filial
* @param [f]            Estrutura fatura
* @param [filial]       Inteiro que determina a filial (filial = 0 -> todas as filials)
* @return               Retorna a faturacao total
*/
int getQuantidadePFilial(Fatura* f, int filial){
  if (filial == 0)
    return f->quantPorFilial[0]+f->quantPorFilial[1]+f->quantPorFilial[2];
  return f->quantPorFilial[filial-1];
}

/**
* @brief                Obtem a faturacao total dado o mês, a filial e o tipo de promoção
* @param [f]            Estrutura fatura
* @param [filial]       Inteiro que determina a filial (filial = 0 -> todas as filials)
* @param [mes]          Inteiro que determina o mes
* @param [prom]         Inteiro que determina a tipo de promocao (prom = 0 -> N e prom = 1 -> P)
* @return               Retorna a faturacao total
*/
double getFaturacao (Fatura* f, int filial, int mes, int prom){
  if(filial == 0)
    return f->faturaTotal[0][mes-1][prom] + f->faturaTotal[1][mes-1][prom] + f->faturaTotal[2][mes-1][prom];

  return f->faturaTotal[filial-1][mes-1][prom];
}
