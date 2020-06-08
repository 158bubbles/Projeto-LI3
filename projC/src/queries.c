#include "queries.h"



/**
* @brief                          Querie 2 -> Determina a lista e o nr total de produtos começados por letter
* @param [sgv]                    Sgv carregado
* @param [letter]                 Letra que queremos procurar na estrutura
* @return                         Devolve a estrutura Q com a informaçao pedida
*/
Q* getProductsStartedByLetter (SGV* sgv, char letter){
  int i;
  Q* q = malloc(sizeof(Q));
  q->size = 1;
  q->ocup = 0;
  q->str = malloc(sizeof(char**));
  for(i = 0; i < getOcupadosP(getDadosPSGV(sgv));i++){
    char* prod = getProdutoP(i, getDadosPSGV(sgv));

    if(prod[0]== letter){

      if(q->size == q->ocup){

        q->size *= 2;
        char** aux = malloc(sizeof(char*)*q->size);
        int j;
        for(j = 0; j < q->size/2; j++){
          aux[j] = q->str[j];
        }
        free(q->str);
        q->str = NULL;
        q->str = aux;
      }
      q->str[q->ocup] = getProdutoP(i,getDadosPSGV(sgv));
      q->ocup++;
    }
    free(prod);
  }
  return q;
}

/**
* @brief                          Obtem numero de posiçoes ocupadas na string str
* @param [q]                      Estrutura Q
* @return                         Devolve um inteiro que nos diz o numero de posiçoes ocupadas na string str da estrutura
*/
int getOcupadosQ (Q* q){
  return q->ocup;
}

/**
* @brief                          Obtem o conteúdo de uma certa posiçao do array str
* @param [q]                      Estrutura Q
* @param [i]                      Inteiro que indica o indice
* @return                         Devolve o conteúdo de uma certa posiçao do array str
*/
char* getSTRQ (Q* q,int i){
  return q->str[i];
}

/**
* @brief                          Obtem o conteúdo do array str
* @param [q]                      Estrutura Q
* @return                         Devolve o conteúdo do array str
*/
char** getSTRTQ(Q* q){
  return q->str;
}

/**
* @brief                          Querie 3
* @param [sgv]                    Sgv carregado
* @param [productID]              Apontador que indica o produto pretendido
* @param [month]                  Inteiro que indica o mês pretendido
* @param [flag]                   Inteiro que indica se queremos o resultado global ou filial a filial
* @return                         Devolve a estrutura Q3 com a informação pedida
*/
Q3* getProductSalesAndProfit(SGV* sgv, char* productID, int month, int flag){
  Q3* q = malloc(sizeof(Q3));
  int i;
  for(i = 0; i < 4; i++){
    q->numTVenN[i] = 0;
    q->numTVenP[i] = 0;
    q->fatToN[i] = 0;
    q->fatToP[i] = 0;
  }
  if(flag == 0){
    q->numTVenN[flag] = getSGVnumeroTVendas(sgv,productID,flag,month,0);
    q->numTVenP[flag] = getSGVnumeroTVendas(sgv,productID,flag,month,1);
    q->fatToN[flag] = getSGVfaturacaoAVL(sgv,productID,flag,month,0);
    q->fatToP[flag] = getSGVfaturacaoAVL(sgv,productID,flag,month,1);
  }
  else{
    for(i = 1; i <= 3; i++){
      q->numTVenN[i] = getSGVnumeroTVendas(sgv,productID,i,month,0);
      q->numTVenP[i] = getSGVnumeroTVendas(sgv,productID,i,month,1);
      q->fatToN[i] = getSGVfaturacaoAVL(sgv,productID,i,month,0);
      q->fatToP[i] = getSGVfaturacaoAVL(sgv,productID,i,month,1);
    }
  }
  return q;
}

/**
* @brief                          Obtem o conteúdo de uma certa posiçao do array
* @param [q]                      Estrutura Q3
* @param [i]                      Inteiro que indica o indice
* @return                         Devolve o número total de vendas com prom = N
*/
int getNumTVenN (Q3* q,int i){
  return q->numTVenN[i];
}

/**
* @brief                          Obtem o conteúdo de uma certa posiçao do array
* @param [q]                      Estrutura Q3
* @param [i]                      Inteiro que indica o indice
* @return                         Devolve o número total de vendas com prom = P
*/
int getNumTVenP (Q3* q,int i){
  return q->numTVenP[i];
}

/**
* @brief                          Obtem o conteúdo de uma certa posiçao do array
* @param [q]                      Estrutura Q3
* @param [i]                      Inteiro que indica o indice
* @return                         Devolve o número total de faturação com prom = N
*/
double getFatToN (Q3* q,int i){
  return q->fatToN[i];
}

/**
* @brief                          Obtem o conteúdo de uma certa posiçao do array
* @param [q]                      Estrutura Q3
* @param [i]                      Inteiro que indica o indice
* @return                         Devolve o número total de faturação com prom = P
*/
double getFatToP (Q3* q,int i){
  return q->fatToP[i];
}


/**
* @brief                          Querie 4-> Determina a lista e o nr de produtos nunca comprados
* @param [sgv]                    Sgv carregado
* @param [branchID]               Inteiro que indica se o utilizador pretende resultados globais ou filial a filial
* @return                         Devolve a estrutura Q com a informação pedida
*/
Q* getProductsNeverBought (SGV* sgv, int branchID){
  Q* q = malloc(sizeof(Q));
  int i,j;
  q->size = 1;
  q->ocup = 0;
  q->str = malloc(sizeof(char**));
  if(branchID == 0){
    int flag[3];
    int r,k;
    for(j = 0; j < getOcupadosP(getDadosPSGV(sgv)); j++){
      r = 0;
      for(k = 0; k < 3; k++){
        flag[k] = 0;
      }
      char* prod = getProdutoP(j,getDadosPSGV(sgv));
      for(i = 0; i < 3; i++){
        if (!(searchAVL(getAVLProdutosSGV(sgv,i), prod))){
          flag[i] = 1;
        }
      }
      for(k = 0; k < 3 && r == 0; k++){
        if(flag[k] != 1) r = 1;
      }
      if (r == 0){
        if(q->size == q->ocup){
          int m;
          q->size *= 2;
          char** aux = malloc(sizeof(char*)*q->size);
          for(m = 0; m < q->size/2; m++)
            aux[m] = q->str[m];
          free(q->str);
          q->str = NULL;
          q->str = aux;
        }
        q->str[q->ocup] = getProdutoP(j,getDadosPSGV(sgv));
        q->ocup++;
      }
      free(prod);
    }
  }
  else {
    for(j = 0; j < getOcupadosP(getDadosPSGV(sgv)); j++){
      char* prod = getProdutoP(j,getDadosPSGV(sgv));
      if(!(searchAVL(getAVLProdutosSGV(sgv,branchID-1),prod))){
        if(q->size == q->ocup){
          int m;
          q->size *= 2;
          char** aux = malloc(sizeof(char*)*q->size);
          for(m = 0; m < q->size/2; m++){
            aux[m] = q->str[m];
          }
          free(q->str);
          q->str = NULL;
          q->str = aux;
        }
        q->str[q->ocup] = getProdutoP(j,getDadosPSGV(sgv));
        q->ocup++;
      }
      free(prod);
    }
  }
  return q;
}



/**
* @brief                          Querie 5 -> Determina a lista dos clientes que fizeram comprar em todas as filiais
* @param [sgv]                    Sgv carregado
* @return                         Devolve a estrutura Q com a informação pedida
*/
Q* getClientsOfAllBranches (SGV* sgv){
  Q* q = malloc(sizeof(Q));
  q->size = 1;
  q->ocup = 0;
  q->str = malloc(sizeof(char**));
  int flag[3];
  int i,j,r = 0;

  for(j = 0; j < getOcupadosC(getDadosCSGV(sgv)); j++){
    char* cli = getClienteC(j,getDadosCSGV(sgv));
    for(i = 0; i < 3; i++){
      flag[i] = 0;
    }
    for(i = 0; i < 3; i++){
      if (searchAVL(getAVLClientesSGV(sgv,i), cli)){
        flag[i] = 1;
      }
    }
    for(i = 0; i < 3 && r == 0; i++){
      if(flag[i] != 1) r = 1;
    }
    if(r == 0){
      if(q->size == q->ocup){
        q->size *= 2;
        char** aux = malloc(sizeof(char*)*q->size);
        for(j = 0; j < q->size/2; j++){
          aux[j] = q->str[j];
        }
        free(q->str);
        q->str = NULL;
        q->str = aux;
      }
      q->str[q->ocup] = getClienteC(j,getDadosCSGV(sgv));
      q->ocup++;
    }
    free(cli);
  }
  return q;
}

/**
* @brief                          Querie 6 -> determina o nr de clientes que nao comprarm nada e o nr de produtos que não foram comprados
* @param [sgv]                    Sgv carregado
* @return                         Devolve a estrutura Q6 com a informação pedida
*/
Q6* getClientsAndProductsNeverBought(SGV* sgv){
  Q6* q = malloc(sizeof(Q6));
  q->naoComprados = 0;
  q->naoCompraram = 0;
  int i,j=0;
  int n= 0;
  int np=0;

  for(j = 0; j < getOcupadosC(getDadosCSGV(sgv)); j++){
    char* cli = getClienteC(j,getDadosCSGV(sgv));
    for(i = 0; i < 3; i++){
      if (!(searchAVL(getAVLClientesSGV(sgv,i), cli))){
        n+=1;
      }
    }
    free(cli);
  }

  q->naoCompraram = n;

  int r,k,flag[3];
  for(j = 0; j < getOcupadosP(getDadosPSGV(sgv)); j++){
    char* prod = getProdutoP(j,getDadosPSGV(sgv));
    r = 0;
    for(k = 0; k < 3; k++){
      flag[k] = 0;
    }
    for(i = 0; i < 3; i++){
      if (!(searchAVL(getAVLProdutosSGV(sgv,i), prod))){
        flag[i] = 1;
      }
    }
    for(k = 0; k < 3 && r == 0; k++){
      if(flag[k] != 1) r = 1;
    }
    if (r == 0) np++;
    free(prod);
  }
  q->naoComprados=np;
  return q;
}

/**
* @brief                          Obtem o resultado armazenado na estrutura
* @param [q]                      Estrutura Q6
* @return                         Devolve o número total de clientes que não compraram nada
*/
int getNaoCompraramQ6(Q6* q){
  return q->naoCompraram;
}

/**
* @brief                          Obtem o resultado armazenado na estrutura
* @param [q]                      Estrutura Q3
* @param [i]                      Inteiro que indica o indice
* @return                         Devolve o número total de produtos que não foram comprados
*/
int getNaoCompradosQ6(Q6* q){
  return q->naoComprados;
}

/**
* @brief                          Querie 7 -> cria uma tabela com o nr total de produtos comprados de mes a mes, filial a filial
* @param [sgv]                    Sgv carregado
* @param [clientID]               Inteiro que indica o cliente pretendido
* @return                         Devolve a estrutura Q7 com a informação pedida
*/
Q7* getProductsBoughtByClient (SGV* sgv, char* clientID){
  Q7* q = malloc(sizeof(Q7));
  int i,j;
  for(j = 0; j < 3; j++){
    for(i = 0; i < 12; i++){

      if(searchAVL(getAVLClientesSGV(sgv,j),clientID)){
        q->mes[j][i] = getQuantProdMesCliente(getAVLClientesSGV(sgv,j),clientID,i);
      }
      else q->mes[j][i] = 0;
    }
  }
  return q;
}

/**
* @brief                          Obtem o conteúdo de uma certa posiçao do array str
* @param [q]                      Estrutura Q7
* @param [i]                      Inteiro que indica o indice
* @param [mes]                    Inteiro que indica o mes pretendido
* @return                         Vendas totais da filial naquele mês
*/
int getQuantMesQ7(Q7* q,int filial, int mes){
  return q->mes[filial][mes];
}

/**
* @brief                          Querie 8 -> devolver o nr de vendas e o total faturado num intervalo
* @param [sgv]                    Sgv carregado
* @param [minMonth]               Inteiro que indica o limite inferior do intervalo dos meses
* @param [maxMonth]               Inteiro que indica o limite superior do intervalo dos meses
* @return                         Devolve a estrutura Q8 com a informação pedida
*/
Q8* getSalesAndProfit(SGV* sgv, int minMonth, int maxMonth){
  Q8* q = malloc(sizeof(Q8));
  q->Nvendas=0;
  q->Tfaturado=0;
  int total;
  double faturacao;
  total = quantidadeTAVL(getAVLFaturasSGV(sgv),minMonth,maxMonth);
  faturacao = faturacaoTAVL(getAVLFaturasSGV(sgv),minMonth,maxMonth);
  q->Nvendas = total;
  q->Tfaturado = faturacao;
  return q;
}

/**
* @brief                          Obtem o conteúdo armazenado na estrutura
* @param [q]                      Estrutura Q8
* @return                         Número de vendas do intervalo
*/
int getTotalQ8(Q8* q){
  return q->Nvendas;
}

/**
* @brief                          Obtem o conteúdo armazenado na estrutura
* @param [q]                      Estrutura Q8
* @return                         Faturação total do intervalo
*/
double getFatQ8 (Q8* q){
  return q->Tfaturado;
}


/**
* @brief                          Querie 9 -> Determina os clientes que compraram o productID na filial pretendida(distingue N e P)
* @param [sgv]                    Sgv carregado
* @param [productID]              Apontador para a string que contem código do produto pretendido
* @param [branch ]                Inteiro que indica a filial pretendida
* @return                         Devolve a estrutura Q9 com a informação pedida
*/
Q9* getProductBuyers(SGV* sgv, char* productID, int branch){
  Q9* q = malloc(sizeof(Q9));

  q->sizeN = 1;
  q->ocupN = 0;

  q->sizeP = 1;
  q->ocupP = 0;


  if(searchAVL(getAVLProdutosSGV(sgv,branch-1), productID)){
    Dados* auxN = getCodigosClientsN(getAVLProdutosSGV(sgv,branch-1),productID);
    q->ocupN = auxN->ocupados;
    q->strN = malloc(sizeof(char*)* q->ocupN);
    q->sizeN = auxN->size;
    int i;
    for(i = 0; i < auxN->ocupados; i++){
      q->strN[i] = strdup(auxN->str[i]);
    }
    Dados* auxP = getCodigosClientsP(getAVLProdutosSGV(sgv,branch-1),productID);
    q->ocupP = auxP->ocupados;
    q->strP = malloc(sizeof(char*)* q->ocupP);
    q->sizeP = auxP->size;
    for(i = 0; i < auxP->ocupados; i++){
      q->strP[i] = strdup(auxP->str[i]);
    }

    /*for(i=0; i < auxN->ocupados; i++){
      free(auxN->str[i]);
    }

    free(auxN->str);

    for(i=0; i < auxP->ocupados; i++){
      free(auxP->str[i]);
    }
    free(auxP->str);
    free(auxN);
    free(auxP);*/
  }
  return q;
}

/**
* @brief                          Obtem o conteúdo armazenado na estrutura
* @param [q]                      Estrutura Q9
* @return                         Número de posiçoes ocupadas em strN
*/
int getOcupadosNQ9 (Q9* q){
  return q->ocupN;
}

/**
* @brief                          Obtem o conteúdo armazenado na estrutura
* @param [q]                      Estrutura Q9
* @return                         Número de posiçoes ocupadas em strP
*/
int getOcupadosPQ9 (Q9* q){
  return q->ocupP;
}

/**
* @brief                          Obtem o conteúdo de strN na posiçao i
* @param [q]                      Estrutura Q9
* @param [i]                      Indica o indice
* @return                         Devolve o código do cliente que comprou o produto com prom = N
*/
char* getSTRnQ9 (Q9* q,int i){
  return q->strN[i];
}


/**
* @brief                          Obtem o conteúdo de strN na posiçao i
* @param [q]                      Estrutura Q9
* @param [i]                      Indica o indice
* @return                         Devolve o código do cliente que comprou o produto com prom = P
*/char* getSTRpQ9 (Q9* q,int i){
  return q->strP[i];
}

/**
* @brief                          Determina se o produto já foi adicionado à estrutura Q10 ou não
* @param [q]                      Estrutura Q10
* @param [prod]                   Indica o produto procurado
*/
int searchSTR(Q10* q,char* prod){
  int i,flag = 0;
  for(i = 0; i < q->ocup && flag == 0; i++){
    if(strcmp(q->str[i]->prod,prod) == 0)
      flag = 1;
  }
  return flag;
}

/**
* @brief                          Atualiza a sua quantidade de um produto na estrutura Q10
* @param [q]                      Estrutura Q10
* @param [i]                      Indica o indice
*/
void updateSTR(Q10* q,PpC* p, int month){
  int i,flag = 0;
  char* nome = getNomePpC(p);
  for(i = 0; i < q->ocup && flag == 0; i++){
    if(strcmp(q->str[i]->prod, nome) == 0){
        q->str[i]->quant += getQuantidadePpC(p,month-1);
        flag = 1;
    }
  }
  free(nome);
}

/**
* @brief                          Insere os dados da AVL numa estrutura. Se o produto já se encontrar presente na nossa estrutura não o vai adicionar, apenas atualizar
* @param [q]                      Estrutura Q10
* @param [i]                      Indica o indice
*/
void insereSTR(Q10* q, PpC* p,int month){
  char* nome = getNomePpC(p);
  if(!(searchSTR(q, nome)) && getQuantidadePpC(p,month-1) != 0){
    P10* aux = malloc(sizeof(P10));
    aux->quant = getQuantidadePpC(p,month-1);
    aux->prod = getNomePpC(p);
    q->str[q->ocup] = aux;
    q->ocup++;
  }
  else {
    updateSTR(q,p,month);
  }
  free(nome);
}


/**
* @brief                          Determina a ordem pela qual os produtos vão ser ordenados
* @param [a]                      Constantes que vão ser comparadas
* @param [b]                      Constantes que vão ser comparadas
* @return                         Devolve um inteiro que irá ser negativo ou positivo
*/
int compareQuantidade (const void* a,const void* b){
  P10* aa = *(P10**)a;
  P10* bb = *(P10**)b;
  return (bb->quant - aa->quant);
}

/**
* @brief                          Querie 10 -> Determina os produtos mais comprados pelo um cliente num dado mês
* @param [sgv]                    Sgv carregado
* @param [clientID]               Inteiro que indica o cliente pretendido
* @param [month]                  Inteiro que o mes pretendido
* @return                         Devolve a estrutura Q10 com a informação pedida
*/
Q10* getClientsFavoriteProduct(SGV* sgv, char* clientID, int month){
  Q10* q = malloc(sizeof(Q10));
  q->ocup = 0;
  AVL* a1 = getAVLClientesSGV(sgv,0);
  AVL* a2 = getAVLClientesSGV(sgv,1);
  AVL* a3 = getAVLClientesSGV(sgv,2);
  while(a1 != NULL && (strcmp(getKey(a1),clientID)) != 0){
    if((strcmp(getKey(a1),clientID)) > 0)
      a1 = getLeft(a1);
    else
      a1 = getRight(a1);
  }
  while( a2 != NULL && (strcmp(getKey(a2),clientID)) != 0 ){
    if((strcmp(getKey(a2),clientID)) > 0)
      a2 = getLeft(a2);
    else
      a2 = getRight(a2);
  }
  while(a3 != NULL && (strcmp(getKey(a3),clientID)) != 0){
    if((strcmp(getKey(a1),clientID)) > 0)
      a3 = getLeft(a3);
    else
      a3 = getRight(a3);
  }
  int ocup1,ocup2,ocup3;
  if(a1 != NULL)
    ocup1 = getOcupadosClieP((ClieP*)getEquals(a1));
  else
    ocup1 = 0;
  if(a2 != NULL)
    ocup2 = getOcupadosClieP((ClieP*)getEquals(a2));
  else
    ocup2 = 0;
  if(a3 !=NULL)
    ocup3 = getOcupadosClieP((ClieP*)getEquals(a3));
  else
    ocup3 = 0;
  q->str = malloc(sizeof(P10*)*(ocup1+ocup2+ocup3));
  int i,j,m;
  for(i = 0; i < ocup1; i++){
    insereSTR(q,getPpCClieP((ClieP*)getEquals(a1),i),month);
  }
  for(j = 0; j < ocup2; j++){
    insereSTR(q,getPpCClieP((ClieP*)getEquals(a2),j),month);
  }
  for(m = 0; m < ocup3; m++){
    insereSTR(q,getPpCClieP((ClieP*)getEquals(a3),m),month);
  }
  qsort(q->str,q->ocup,sizeof(P10*),compareQuantidade);
  return q;
}

/**
* @brief                          Devolve o código de um produto
* @param [q]                      Estrutura P10
* @return                         Devolve o código de um produto
*/
char* getProdutoSTRP10 (P10* p){
  return p->prod;
}

/**
* @brief                          Determina a ordem pela qual os produtos vão ser ordenados
* @param [q]                      Estrutura P10
* @param [i]                      Indica o indice
* @return                         Devolve a quantidade de um produto
*/
int getQuantSTRP10(P10* p){
  return p->quant;
}

/**
* @brief                          Devolve um inteiro que indica o numero de posiçoes ocupadas em str
* @param [q]                      Estrutura Q10
* @return                         Devolve um inteiro que indica o numero de posiçoes ocupadas em str
*/
int getOcupadosQ10(Q10* q){
  return q->ocup;
}

/**
* @brief                          Obtem o conteúdo de uma certa posiçao do array str
* @param [q]                      Estrutura Q10
* @param [i]                      Indica o indice
* @return                         Devolve uma posição que contem a informaçao introduzida em P10
*/
P10* getSTRQ10(Q10* q,int i){
  return q->str[i];
}



/**
* @brief                          Percorre a AVL
* @param [a]                      AVL recebida
* @param [str]                    Estrutura fatura
* @param [i]                      Indica o indice
*/
void percorreAVL(AVL* a, Fatura** str,int* i){
  if(a != NULL){
    AVL* aux = a;
    str[*i] = cloneFaturas(getEquals(a));
    *i = *i+1;
    percorreAVL(getLeft(aux),str,i);
    percorreAVL(getRight(aux),str,i);
  }
}


/**
* @brief                          Determina a ordem pela qual os produtos vão ser ordenados
* @param [a]                      Constantes que vão ser comparadas
* @param [b]                      Constantes que vão ser comparadas
* @return                         Devolve um inteiro que irá ser negativo ou positivo
*/
int comparaFaturas (const void* a,const void* b){
  Fatura* aa = *(Fatura**)a;
  Fatura* bb = *(Fatura**)b;
  return (getQuantidadePFilial(bb,0)- getQuantidadePFilial(aa,0));
}

/**
* @brief                          Querie 11 -> cria uma lista com limit posições, indicando nr de vendas e nr de clientes, filial a filial, ordenado spor ordem decrescente
* @param [sgv]                    Sgv carregado
* @param [limit]                  Inteiro que indica o numero de posiçoes que a lista irá ter
* @return                         Devolve a estrutura Q11 com a informação pedida
*/
Q11* getTopSelledProducts(SGV* sgv, int limit){
  Q11* q = malloc(sizeof(Q11));
  q->p = malloc(sizeof(P11*)*limit);
  int j,n;
  for(j = 0; j < limit; j++){
    P11* aux = malloc(sizeof(P11));
    for(n = 0; n < 3; n++){
      aux->porFilialC[n] = 0;
      aux->porFilialNumeroU[n] = 0;
    }
    q->p[j] = aux;
  }

  int nN = numNode(getAVLFaturasSGV(sgv));
  Fatura** str = malloc(sizeof(Fatura*)*nN);
  int i = 0;
  percorreAVL(getAVLFaturasSGV(sgv),str,&i);
  qsort(str,nN,sizeof(Fatura*),comparaFaturas);
  for(i = limit; i < nN; i++){
    char* prod = getProdutoFatura(str[i]);
    free(prod);
    free(str[i]);
  }
  q->str = str;
  int m;
  for(j = 0; j < limit; j++){
    for(i = 0; i < 3; i++){
      for(m = 0; m < 12; m++){
        q->p[j]->porFilialC[i] += getNumeroTotalVendas(q->str[j],i+1,m+1,0) + getNumeroTotalVendas(q->str[j],i+1,m+1,1);
      }
      q->p[j]->porFilialNumeroU[i] += getQuantidadePFilial(q->str[j],i+1);
    }
  }
  return q;
 }


 /**
 * @brief                          Devolve o número de clientes da filial
 * @param [q]                      Estrutura P11
 * @param [i]                      Indica a filial
 * @return                         Devolve o número de clientes da filial
 */
int getPorFilialC(P11* p, int i){
  return p->porFilialC[i];
}


/**
* @brief                          Devolve o número de vendas da filial
* @param [q]                      Estrutura P11
* @param [i]                      Indica a filial
* @return                         Devolve o número de vendas da filial
*/
int getPorFilialNumeroU(P11* p, int i){
  return p->porFilialNumeroU[i];
}

/**
* @brief                          Devolve a estrutura P11
* @param [q]                      Estrutura P11
* @param [i]                      Indica a filial
* @return                         Devolve a estrutura P11
*/
P11* getP11(Q11* q,int i){
  return q->p[i];
}


/**
* @brief                          Devolve uma estrutura Fatura
* @param [q]                      Estrutura Q11
* @param [i]                      Indica o inidice onde está a estrutura
* @return                         Retorna uma fatura
*/

Fatura* getFaturaQ11(Q11* q,int i){
  return q->str[i];
}


/**
* @brief                          Determina a ordem pela qual os produtos vão ser ordenados
* @param [a]                      Constantes que vão ser comparadas
* @param [b]                      Constantes que vão ser comparadas
* @return                         Devolve um inteiro que irá ser negativo ou positivo
*/
 int comparaFaturacao (const void* a,const void* b){
   P12* aa = *(P12**)a;
   P12* bb = *(P12**)b;
   return (bb->faturacao-aa->faturacao);
 }


 /**
 * @brief                          Determina se o produto já foi adicionado à estrutura Q12 ou não
 * @param [q]                      Estrutura Q12
 * @param [prod]                   Indica o produto procurado
 */
 int searchFat(Q12* q,char* prod){
   int i,flag = 0;
   for(i = 0; i < q->ocup && flag == 0; i++){
     if(strcmp(q->str[i]->produto,prod) == 0)
       flag = 1;
   }
   return flag;
 }


 /**
 * @brief                          Atualiza a faturação na estrutura Q12
 * @param [q]                      Estrutura Q12
 * @param [p]                      Indica o indice
 */
 void updateFat(Q12* q,PpC* p){
   char* nome = getNomePpC(p);
   int i,j,flag = 0;
   for(i = 0; i < q->ocup && flag == 0; i++){
     if(strcmp(q->str[i]->produto, nome) == 0){
       int total = 0;
       for(j = 0; j < 12; j++){
         total += getFaturacaoPpC(p,j);
       }
       q->str[i]->faturacao += total;
       flag = 1;
     }
   }
   free(nome);
 }

 /**
 * @brief                          Insere os dados da estrutura PpC numa estrutura Q12. Se o produto já se encontrar presente na nossa estrutura não o vai adicionar, apenas atualizar
 * @param [q]                      Estrutura Q12
 * @param [p]                      Indica o indice
 */
 void insereFat(Q12* q, PpC* p){
   int quantidade = 0,i;
   for(i = 0; i < 12; i++){
     quantidade += getQuantidadePpC(p,i);
   }
   char* nome = getNomePpC(p);
   if(!(searchFat(q, nome)) && quantidade != 0){
     P12* aux = malloc(sizeof(P12));
     double total = 0;
     for(i = 0; i < 12; i++){
        total += getFaturacaoPpC(p,i);
     }
     aux->faturacao = total;
     aux->produto = getNomePpC(p);

     q->str[q->ocup] = aux;
     q->ocup++;
   }
   else {
     updateFat(q,p);
   }
   free(nome);
 }
 /**
 * @brief                          Querie 12 -> cria uma lista com limit posições, indicando os produtos em que o cliente mais gastou durante o ano
 * @param [sgv]                    Sgv carregado
 * @param [clientID]               Indica o cliente pretendido
 * @param [limit]                  Inteiro que indica o numero de posiçoes que a lista irá ter
 * @return                         Devolve a estrutura Q12 com a informação pedida
 */
Q12* getClientTopProfitProducts(SGV* sgv,char* clientID, int limit){
  Q12* q = malloc(sizeof(Q12));
  q->ocup = 0;
  AVL* a1 = getAVLClientesSGV(sgv,0);
  AVL* a2 = getAVLClientesSGV(sgv,1);
  AVL* a3 = getAVLClientesSGV(sgv,2);

  while(a1 != NULL && (strcmp(getKey(a1),clientID)) != 0){
    if((strcmp(getKey(a1),clientID)) > 0)
      a1 = getLeft(a1);
    else
      a1 = getRight(a1);
  }

  while( a2 != NULL && (strcmp(getKey(a2),clientID)) != 0 ){
    if((strcmp(getKey(a2),clientID)) > 0)
      a2 = getLeft(a2);
    else
      a2 = getRight(a2);
  }

  while(a3 != NULL && (strcmp(getKey(a3),clientID)) != 0){
    if((strcmp(getKey(a3),clientID)) > 0)
      a3 = getLeft(a3);
    else
      a3 = getRight(a3);
  }

  int ocup1,ocup2,ocup3;
  if(a1 != NULL)
    ocup1 =getOcupadosClieP(getEquals(a1));
  else
    ocup1 = 0;
  if(a2 != NULL)
    ocup2 =getOcupadosClieP(getEquals(a2));
  else
    ocup2 = 0;
  if(a3 !=NULL)
    ocup3 =getOcupadosClieP(getEquals(a3));
  else
    ocup3 = 0;

  q->str = malloc(sizeof(P12*)*(ocup1+ocup2+ocup3));
  int i,j,m;
  for(i = 0; i < ocup1; i++){
    insereFat(q,getPpCClieP(getEquals(a1),i));
  }
  for(j = 0; j < ocup2; j++){
    insereFat(q,getPpCClieP(getEquals(a2),j));
  }
  for(m = 0; m < ocup3; m++){
    insereFat(q,getPpCClieP(getEquals(a3),m));
  }

  qsort(q->str,q->ocup,sizeof(P10*),comparaFaturacao);
  for(i = limit; i < q->ocup; i++){
    free(q->str[i]);
    q->str[i] = NULL;
  }
  q->ocup = limit;
  return q;
}


/**
* @brief                          Funcao que devolve um produto
* @param [p]                      Estrutura P12
* @return                         Retorna o nome do produto
*/
char* getProdutoQ12(P12* p){
  return p->produto;
}

/**
* @brief                          Funcao que devolve a faturacao
* @param [p]                      Estrutura P12
* @return                         Retorna a faturacao
*/
double getFaturacaoQ12(P12* p){
  return p->faturacao;
}

/**
* @brief                          Funcao que devolve uma estrutura P12
* @param [q]                      Estrutura Q12
* @param [i]                      Indice onde se encontra a estrutura P12
* @return                         Retorna a estrutura P12
*/
P12* getP12(Q12* q,int i){
  return q->str[i];
}

/**
* @brief                          Funcao que devolve o numero de ocupados, isto é, quantos elementos tem P12**
* @param [q]                      Estrutura Q12
* @return                         Retorna o numero de ocupados
*/
int getOcupadosQ12(Q12* q){
  return q->ocup;
}



/**
* @brief                          Querie 13 -> Apresenta os resultados da leitura dos ficheiros
* @param [sgv]                    Sgv carregado
* @return                         Devolve a estrutura Q13 com a informação pedida
*/
Q13* getCurrentFilesInfo(SGV* sgv){
  Q13* q = malloc(sizeof(Q13));
  int i;
  for(i = 0; i < 3; i++){
    q->validas[i] = 0;
    q->lidas[i] = 0;
  }
  q->path[0]  = getPathC(sgv);
  q->path[1] = getPathP(sgv);
  q->path[2] = getPathV(sgv);
  q->validas[0] = getOcupadosC(getDadosCSGV(sgv));
  q->lidas[0] = getLidasC(getDadosCSGV(sgv));
  q->validas[1] = getOcupadosP(getDadosPSGV(sgv));
  q->lidas[1] = getLidasP(getDadosPSGV(sgv));
  q->validas[2] = getOcupadosV(getVendasSGV(sgv));
  q->lidas[2] = getLidasV(getVendasSGV(sgv));

  return q;
 }


/**
* @brief                          Funcao que retorna o caminho de um dado ficheiro
* @param [q]                      Estrutura Q13
* @param [i]                      Indice do ficheiro
* @return                         Retorna o caminho de um dado ficheiro
* @details                        0 -> Clientes 1 -> Produtos 2 -> Vendas
*/
 char* getPathQ13(Q13* q,int i){
   return q->path[i];
 }

 /**
 * @brief                          Funcao que retorna o numero de linhas validas de um ficheiro
 * @param [q]                      Estrutura Q13
 * @param [i]                      Indice do ficheiro
 * @return                         Retorna o numero de linhas validas do ficheiro i
 * @details                        0 -> Clientes 1 -> Produtos 2 -> Vendas
 */
 int getValidasQ13(Q13* q,int i){
   return q->validas[i];
 }

 /**
 * @brief                          Funcao que retorna o numero de linhas lidas de um dado ficheiro
 * @param [q]                      Estrutura Q13
 * @param [i]                      Indice do ficheiro
 * @return                         Retorna o numero de linhas lidas do ficheiro i
 * @details                        0 -> Clientes 1 -> Produtos 2 -> Vendas
 */
int getLidasQ13(Q13* q,int i){
  return q->lidas[i];
}
