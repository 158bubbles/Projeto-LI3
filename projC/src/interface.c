#include "interface.h"
#include <time.h>

struct sgv{
  char* path[3];
  Dados* clientes;
  Dados* produtos;
  VT* vendas;
  AVL* faturas;
  Filial* filial[3];
};


/**
* @brief                Inicializa o SGV
* @return               Retorna um SGV inicializa
*/

SGV* initSGV(){
  SGV* sgv = malloc(sizeof(struct sgv));
  int i;
  sgv->produtos = initDados();
  sgv->clientes = initDados();
  sgv->vendas = initVendas();
  sgv->faturas =  NULL;
  for(i = 0; i < 3; i++){
    sgv->filial[i] = initFilial();
  }
  return sgv;
}

/**
* @brief                          Carrega os ficheiros relativos aos produtos, clientes e vendas
* @param [sgv]                    Sgv inicializado
* @param [clientesFilePath]       Caminho para o documento dos clientes
* @param [productsFilePath]       Caminho para o documento dos produtos
* @param [salesFilePath]          Caminho para o documento das vendas
* @return                         Sgv carregado
*/
SGV* loadSGVFromFiles(SGV* sgv, char* clientesFilePath,char* productsFilePath, char* salesFilePath){
  read_Produtos(sgv->produtos,productsFilePath);
  read_Clientes(sgv->clientes,clientesFilePath);
  read_Vendas(sgv->vendas,sgv->produtos,sgv->clientes,salesFilePath);
  int i;
  sgv->path[0] = clientesFilePath;
  sgv->path[1] = productsFilePath;
  sgv->path[2] = salesFilePath;
  sgv->faturas = insereFaturaAVL(sgv->vendas,sgv->faturas);
  for (i = 0; i < getOcupadosV(sgv->vendas); i++){
    int j = getFilial(getVenda(sgv->vendas,i)) -1;
    sgv->filial[j] = insereFilial(sgv->filial[j],getVenda(sgv->vendas,i));
  }
  return sgv;
}


/**
* @brief                          Obtem
* @param [sgv]                    Sgv inicializado
* @param [filial]                 Inteiro que representa a filial
* @return                         Devolve a AVL referente aos produtos da filial selecionada
*/
AVL* getAVLProdutosSGV(SGV* sgv,int filial){
  return getAVLProdutos(sgv->filial[filial]);
}

/**
* @brief                          Obtem
* @param [sgv]                    Sgv inicializado
* @param [filial]                 Inteiro que representa a filial
* @return                         Devolve a AVL referente aos clientes da filial selecionada
*/
AVL* getAVLClientesSGV(SGV* sgv,int filial){
  return getAVLClientes(sgv->filial[filial]);
}

/**
* @brief                          Obtem
* @param [sgv]                    Sgv inicializado
* @return                         Devolve a AVL referente às faturas
*/
AVL* getAVLFaturasSGV(SGV* sgv){
  return sgv->faturas;
}

/**
* @brief                          Obtem
* @param [sgv]                    Sgv inicializado
* @return                         Devolve a estrutura Dados dos produtos
*/
Dados* getDadosPSGV(SGV* sgv){
  return sgv->produtos;
}

/**
* @brief                          Obtem
* @param [sgv]                    Sgv inicializado
* @return                         Devolve a estrutura Dados dos clientes
*/
Dados* getDadosCSGV(SGV* sgv){
  return sgv->clientes;
}

/**
* @brief                          Obtem
* @param [sgv]                    Sgv inicializado
* @return                         Devolve a estrutura VT que contem as vendas
*/
VT* getVendasSGV (SGV* sgv){
  return sgv->vendas;
}

/**
* @brief                          Obtem o numero total de vendas dado o mês, a filial e o tipo de promoção recorrendo a SGV
* @param [sgv]                    Sgv inicializado
* @param [filial]                 Inteiro que representa a filial
* @param [mes]                    Inteiro que representa a mes
* @param [prom]                   Inteiro que representa a promoçao (0 -> Sem promoção (N) // 1-> Com promoção (P))
* @return                         Devolve um inteiro com o numero total de vendas
*/
int getSGVnumeroTVendas(SGV* sgv,char* prod,int filial, int mes, int prom){
  return getNumeroTVendAVL(sgv->faturas,prod,filial,mes,prom);
}

/**
* @brief                          Obtem a quantidade total dada a filial e o produto recorrendo a SGV
* @param [sgv]                    Sgv inicializado
* @param [prod]                   Apontador para a string que representa o produto
* @param [filial]                 Inteiro que representa a filial
* @return                         Devolve um inteiro com a quantidade total de um produto numa filial
*/
int getSGVquantidadePFilial(SGV* sgv, char* prod,int filial){
  return getQuantidadePFilialAVL(sgv->faturas,prod,filial);
}

/**
* @brief                          Obtem a faturação dado o mês, a filial, o produto e o tipo de promoção recorrendo a SGV
* @param [sgv]                    Sgv inicializado
* @param [prod]                   Apontador para a string que representa o produto
* @param [filial]                 Inteiro que representa a filial
* @param [mes]                    Inteiro que representa a mes
* @param [prom]                   Inteiro que representa a promoçao (0 -> Sem promoção (N) // 1-> Com promoção (P))
* @return                         Devolve um inteiro com a faturaçao total de um produto numa filial,num mês específico e com um tipo de promoção específico
*/
int getSGVfaturacaoAVL(SGV* sgv, char* prod,int filial, int mes, int prom){
  return getFaturacaoAVL(sgv->faturas,prod,filial,mes,prom);
}


/**
* @brief                          Obtem o caminho para o documento dos clientes
* @param [sgv]                    Sgv inicializado
* @return                         Um apontador para um string que contem o caminho para o documento dos clientes
*/
char* getPathC (SGV* sgv){
  return sgv->path[0];
}

/**
* @brief                          Obtem o caminho para o documento dos clientes
* @param [sgv]                    Sgv inicializado
* @return                         Um apontador para um string que contem o caminho para o documento dos produtos
*/
char* getPathP (SGV* sgv){
  return sgv->path[1];
}

/**
* @brief                          Obtem o caminho para o documento dos clientes
* @param [sgv]                    Sgv inicializado
* @return                         Um apontador para um string que contem o caminho para o documento das vendas
*/
char* getPathV (SGV* sgv){
  return sgv->path[2];
}

/**
* @brief                          Dá free do sgv
* @param [sgv]                    Sgv inicializado
*/
void destroySGV (SGV* sgv){
  freeAVLFatura(sgv->faturas);
  int i;
  for(i = 0; i < 3; i++){
    freeFilial(sgv->filial[i]);
  }
  freeDados(sgv->produtos);
  freeDados(sgv->clientes);
  freeVendas(sgv->vendas);
  free(sgv);
  sgv = NULL;
}
