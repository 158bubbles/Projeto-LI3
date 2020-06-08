/**
* @file                 faturacoes.c
* @brief                Modulo que inicializa e insere as estruturas faturas numa estrutura AVL
*/
#include "faturacoes.h"


/**
* @brief                Desaloca a memória ocupada por faturas em AVL
* @param [f]            Estrutura AVL que vai ser desalocada
*/
void freeAVLFatura (AVL* f){
  if(f){
    free(getKey(f));
    freeNodoAVLFatura((Fatura*)(getEquals(f)));
    freeAVLFatura(getRight(f));
    freeAVLFatura(getLeft(f));
    free(f);
    f = NULL;
  }
}

/**
* @brief                Insere a estrutura fatura numa AVL
* @param [v]            Estrutura VT que irá fornecer as vendas para inicializar a estrutura faturas
* @param [t]            Estrutura AVL onde vão ser inseridas as faturas
* @return               Retorna a estrutura AVL com as faturas
*/
AVL* insereFaturaAVL (VT* v, AVL* t){
  int i;
  for(i = 0; i < getOcupadosV(v); i++){
    Venda* vendas = getVenda(v,i);
    char* prod = getProduto(vendas);
    AVL* tmp = searchAVLTMP(t,prod);
    if(tmp != NULL){
      Fatura* e = (Fatura*)getEquals(tmp);
      insereFatura(e,vendas);
    }
    else {
      Fatura* f = initFatura();
      insereFatura(f,vendas);
      t = insert(t,strdup(prod),f);
    }
    free(prod);
  }
  return t;
}

/**
* @brief                Obtem o numero total de vendas dado o mês, a filial e o tipo de promoção recorrendo a AVL
* @param [a]            Estrutura AVL utilizada para obter o numero total de vendas
* @param [prod]         Produto na qual desejamos saber o numero de vendas
* @param [filial]       Filial desejada
* @param [mes]          Mes desejado
* @param [prom]         Promocao desejada
* @return               Retorna o numero total de vendas
*/
int getNumeroTVendAVL (AVL* a,char* prod,int filial, int mes,int prom){
  if(searchAVL(a,prod)){
    AVL* tmp = a;
    while(strcmp(getKey(tmp),prod)!=0){
      if((strcmp(getKey(tmp),prod)) < 0){
        tmp = getRight(tmp);
      }
      else{
        tmp = getLeft(tmp);
      }
    }
    return getNumeroTotalVendas(getEquals(tmp),filial,mes,prom);
  }
  return 0;
}

/**
* @brief                Obtem a quantidade total de produtos vendidos dado o mês, a filial e o tipo de promoção recorrendo a AVL
* @param [a]            Estrutura AVL utilizada para obter a quantidade total de produtos vendidos
* @param [prod]         Produto na qual desejamos saber o numero de vendas
* @param [filial]       Filial desejada
* @return               Retorna a quantidade total de produtos vendidos
*/
int getQuantidadePFilialAVL (AVL* a,char* prod ,int filial){
  if(searchAVL(a,prod)){
    AVL* tmp = a;
    while(strcmp(getKey(tmp),prod)!=0){
      if((strcmp(getKey(tmp),prod)) < 0){
        tmp = getRight(tmp);
      }
      else{
        tmp = getLeft(tmp);
      }
    }
    return getQuantidadePFilial(getEquals(tmp),filial);
  }
  return 0;
}

/**
* @brief                Obtem a faturacao total de vendas dado o mês, a filial e o tipo de promoção recorrendo a AVL
* @param [a]            Estrutura AVL utilizada para obter a faturacao total
* @param [prod]         Produto na qual desejamos saber o numero de vendas
* @param [filial]       Filial desejada
* @param [mes]          Mes desejado
* @param [prom]         Promocao desejada
* @return               Retorna a faturacao total
*/
int getFaturacaoAVL(AVL* a, char* prod, int filial, int mes, int prom){
  if(searchAVL(a,prod)){
    AVL* tmp = a;
    while(strcmp(getKey(tmp),prod)!=0){
      if((strcmp(getKey(tmp),prod)) < 0){
        tmp = getRight(tmp);
      }
      else{
        tmp = getLeft(tmp);
      }
    }
    return getFaturacao(getEquals(tmp),filial,mes,prom);
  }
  return 0;
}

/**
* @brief                Indica-nos a faturação dado um intervalo fechado de meses
* @param [fatura]       Estrutura AVL
* @param [minMonth]     Limite inferior
* @param [maxMonth]     Limite superior
* @return               Retorna a faturacao total no intervalo fechado de meses
*/
double faturacaoTAVL (AVL* fatura,int minMonth, int maxMonth){
  double valor = 0;
  int j,k;
  if (fatura != NULL){
    for(j = minMonth; j <= maxMonth; j++){
      for(k = 0; k < 2; k++)
        valor += getFaturacao(getEquals(fatura),0,j,k);
    }
    return valor + faturacaoTAVL(getLeft(fatura),minMonth,maxMonth) + faturacaoTAVL(getRight(fatura),minMonth,maxMonth);
  }
  else return 0;
}

/**
* @brief                Indica-nos a quantidade dado um intervalo fechado de meses
* @param [fatura]       Estrutura AVL
* @param [minMonth]     Limite inferior
* @param [maxMonth]     Limite superior
* @return               Retorna a quantidade total no intervalo fechado de meses.
*/
int quantidadeTAVL (AVL* fatura,int minMonth, int maxMonth){
  int valor = 0;
  int i,j,k;
  if (fatura != NULL){
    for(i = 1; i <= 3; i++){
      for(j = minMonth; j <= maxMonth; j++){
        for(k = 0; k < 2; k++)
          valor += getNumeroTotalVendas(getEquals(fatura),i,j,k);
      }
    }
    return valor + quantidadeTAVL(getLeft(fatura),minMonth,maxMonth) + quantidadeTAVL(getRight(fatura),minMonth,maxMonth);
  }
  else return 0;
}
