/**
* @file                 filial.c
* @brief                Modulo filial Que inicializa e controi a estrutura
*/

#include "filial.h"

struct filial{
  AVL* produtos;
  AVL* clientes;
};

struct codigoProdutosP{
  Dados* clienteN;
  Dados* clienteP;
};

struct produtosPorCliente{
  char* nome;
  int quant[12];
  int fat[12];
};

struct codigoClientes{
  int ocupados;
  int quant[12];
  PpC** produtosPorCliente;
};


/**
* @brief              Inicialização da estrutura ProdP e da estrutura dados
* @return             Retorna a nova estrutura ProdP
*/
ProdP* initCodigoProduto (){
  ProdP* p = malloc(sizeof(ProdP));
  p->clienteN = initDados();
  p->clienteP = initDados();
  return p;
}

/**
* @brief            Insere os dados referentes à struct ProdP
* @param [v]        Venda utilizada para inserir o cliente
* @param [p]        Estrutura ProdP onde vai ser inserida o cliente
*/
void insereClienteP (Venda* v,ProdP* p){
  if(getPromocao(v) == 'N'){
    if(p->clienteN->size == p->clienteN->ocupados){
      reallocDados(p->clienteN);
    }
    p->clienteN->str[p->clienteN->ocupados++] = getCliente(v);
  }
  else {
    if(p->clienteP->size == p->clienteP->ocupados){
      reallocDados(p->clienteP);
    }
    p->clienteP->str[p->clienteP->ocupados++] = getCliente(v);
  }
}

/**
* @brief                Inicializa a estrutura PpC
* @return               Estrutura PpC inicializada
*/
PpC* initProdutoCliente (){
  int i;
  PpC* p = malloc(sizeof(PpC));
  p->nome = NULL;
  for(i = 0; i < 12; i++){
    p->quant[i] = 0;
  }
  for(i = 0; i < 12; i++){
    p->fat[i] = 0;
  }
  return p;
}

/**
* @brief                  Insere uma venda na estrutura PpC
* @param [v]              Venda utilizada para inserir os dados na estrutura
* @param [p]              Estrutura onde vao ser inseridos os dados
*/
void insereProdutoCliente(Venda* v, PpC* p){
  p->nome = getProduto(v);
  p->quant[getData(v)-1] += getQuantidade(v);
  p->fat[getData(v)-1] += getPreco(v)*getQuantidade(v);
}

/**
* @brief                  Funcao que retorna o nome de um dado PpC
* @param [p]              Estrutura PpC
* @return                 Retorna o nome do produto da estrutura PpC
*/
char* getNomePpC (PpC* p){
  return strdup(p->nome);
}

/**
* @brief                  Funcao que retorna a quantidade total de um dado mes
* @param [p]              Estrutura PpC
* @param [mes]            Mes que queremos saber a quantidade
* @return                 Retorna a quantidade de um dado mes da estrutura PpC
*/
int getQuantidadePpC (PpC* p,int mes){
  return p->quant[mes];
}

/**
* @brief                  Funcao que retorna a faturacao total de um dado mes
* @param [p]              Estrutura PpC
* @param [mes]            Mes que queremos saber a faturacao
* @return                 Retorna a faturacao de um dado mes da estrutura PpC
*/
int getFaturacaoPpC (PpC* p,int mes){
  return p->fat[mes];
}


/**
* @brief                  Inicialização da estrutura ClieP
* @return                 Estrutura inicializada ClieP
*/
ClieP* initCodigoClientes (){
  ClieP* c = malloc(sizeof(ClieP));
  c->ocupados = 0;
  int i;
  for(i = 0; i < 12; i++){
    c->quant[i] = 0;
  }
  c->produtosPorCliente = NULL;
  return c;
}


/**
* @brief                Atualizacao dos dados da estrutura PpC utilizando uma venda
* @param [v]            Venda utilizada para atualizar os valores da estrutura PpC
* @param [p]            Estrutura PpC que vai ser atualizada
*/
void updateCodigoCliente(Venda* v, PpC* p){
  p->quant[getData(v)-1] += getQuantidade(v);
  p->fat[getData(v)-1] += getPreco(v);
}

/**
* @brief                Funcao que insere os dados uma venda numa estrutura ClieP
* @param [v]            Venda utilizada para obter os dados
* @param [c]            Estrutura onde vão ser inseridos os dados
*/
void insereCodigoCliente(Venda* v, ClieP* c){

  PpC** aux = c->produtosPorCliente;
  int i = 0;
  char* prod = getProduto(v);
  while(i < c->ocupados && (strcmp(aux[i]->nome,prod) != 0)) i++;
  if(i == c->ocupados){
    int size = (i*2)+1;
    c->produtosPorCliente = realloc(c->produtosPorCliente,size*sizeof(PpC*));
    c->produtosPorCliente[c->ocupados] = initProdutoCliente();
    insereProdutoCliente(v,c->produtosPorCliente[c->ocupados++]);
    c->quant[getData(v)-1] += getQuantidade(v);
  }
  else{
    updateCodigoCliente(v,aux[i]);
  }
  free(prod);
}

/**
* @brief                Funcao que obtem o numero de ocupados da estrutura PpC** na estrutura ClieP
* @param [c]            Estrutura ClieP
* @return               Retorna o numero de ocupados da estrutura PpC**
*/
int getOcupadosClieP(ClieP* c){
  return c->ocupados;
}

/**
* @brief                Funcao que obtem a quantidade total de produtos comprados num dado mes de um dado cliente
* @param [c]            Estrutura ClieP
* @param [mes]          Mes em que quer a quantidade
* @return               Quantidade total de produtos comprados num dados mes
*/
int getQuantidadeClieP (ClieP* c, int mes){
  return c->quant[mes-1];
}

/**
* @brief                Funcao que obtem uma estrutura PpC a partir de uma estrutura ClieP
* @param [c]            Estrutura ClieP
* @param [i]            Indice i onde encontramos a estrutura PpC
* @return               Estrutura PpC
*/
PpC* getPpCClieP(ClieP* c,int i){
  return c->produtosPorCliente[i];
}

/**
* @brief                Funcao que inicializa uma estrutura Filial
* @return               Retorna a estrutura Filial inicializada
*/
Filial* initFilial(){
  Filial* f = malloc(sizeof(Filial));
  f->produtos = NULL;
  f->clientes = NULL;
  return f;
}

/**
* @brief                Funcao que insere todos os valores da estrutura filial dada uma venda
* @param [f]            Filial onde vao ser inseridos os valores de todas as suas estruturas
* @param [v]            Venda utilizada para obter os dados
* @return               Retorna a filial com os dados todos inseridos
*/

/*AVL* ap = f->produtos;
while(strcmp(getKey(ap),getProduto(v)) != 0){
  if(strcmp(getKey(ap),getProduto(v)) > 0){
    ap = getLeft(ap);
  }
  else {
    ap = getRight(ap);
  }
}*/

Filial* insereFilial(Filial* f,Venda* v){
  char* prod = getProduto(v);
  char* cli = getCliente(v);
  AVL* ap = searchAVLTMP(f->produtos,prod);
  if(ap != NULL){
    insereClienteP(v,(ProdP*) getEquals(ap));
  }
  else
  {
    ProdP* p = initCodigoProduto();
    insereClienteP(v,p);
    f->produtos = insert(f->produtos,strdup(prod),p);
  }
  AVL* ac = (searchAVLTMP(f->clientes,cli));
  if(ac != NULL){
    insereCodigoCliente(v,getEquals(ac));
  }
  else {
    ClieP* c = initCodigoClientes();
    insereCodigoCliente(v,c);
    f->clientes = insert(f->clientes,strdup(cli),c);
  }
  free(prod);
  free(cli);
  return f;
}


/**
* @brief                Obtem a quantidade de produtos comprados dado o cliente e o mês
* @param [f]            Estrutura avl onde vai ser procurado o cliente
* @param [cliente]      Cliente que queremos encontrar
* @param [mes]          Mes que o utilizador deseja informacoes
* @return               Retorna a quantidade de produtos comprados
*/
int getQuantProdMesCliente (AVL* f,char* cliente,int mes){
  if(searchAVL(f,cliente)){
    AVL* aux = f;
    while(strcmp(getKey(aux),cliente)!= 0){
      if(strcmp(getKey(aux),cliente) > 0)
        aux = getLeft(aux);
      else
        aux = getRight(aux);
    }
    return ((ClieP*)getEquals(aux))->quant[mes];
  }
  return 0;
}

/**
* @brief                Obtem os clientes que compraram o produto correspondente ao codigo dado em promoção tipo N
* @param [f]            Estrutura AVL onde vai ser procurado o produtos
* @param [productID]    Produto que queremos encontrar
* @return               Retorna a estrutura dados clienteN
*/
Dados* getCodigosClientsN(AVL* f,char* productID){
  if(searchAVL(f,productID)){
    AVL* tmp = f;
    while(strcmp(getKey(tmp),productID)!= 0){
      if(strcmp(getKey(tmp),productID) > 0){
        tmp = getLeft(tmp);
      }
      else{
        tmp = getRight(tmp);
      }
    }

    return ((ProdP*)getEquals(tmp))->clienteN;
  }
  return NULL;
}

/**
* @brief                Obtem os clientes que compraram o produto correspondente ao codigo dado em promoção tipo P
* @param [f]            Estrutura AVL onde vai ser procurado o produtos
* @param [productID]    Produto que queremos encontrar
* @return               Retorna a estrutura dados clienteP
*/
Dados* getCodigosClientsP(AVL* f,char* productID){
  if(searchAVL(f,productID)){
    AVL* tmp = f;
    while(strcmp(getKey(tmp),productID)!= 0){
      if(strcmp(getKey(tmp),productID) > 0){
        tmp = getLeft(tmp);
      }
      else{
        tmp = getRight(tmp);
      }
    }
    return ((ProdP*)getEquals(tmp))->clienteP;
  }
  return NULL;
}

/**
* @brief                Funcao que obtem a AVL de produtos
* @param [f]            Filial onde vamos buscar a AVL produtos
* @return               Retorna a AVL produtos;
*/
AVL* getAVLProdutos (Filial* f){
  return f->produtos;
}

/**
* @brief                Funcao que obtem a AVL de cliente
* @param [f]            Filial onde vamos buscar a AVL cliente
* @return               Retorna a AVL cliente;
*/
AVL* getAVLClientes (Filial* f){
  return f->clientes;
}

/**
* @brief                Desaloca a memoria ocupada pela estrutura ProdP
* @param [p]            Estrutura ProdP
*/
void freeProdP (ProdP* p){
  freeDados((Dados*) p->clienteN);
  freeDados((Dados*) p->clienteP);
  free(p);
}

/**
* @brief                Desaloca a memoria ocupada pela estrutura AVL
* @param [f]            Estrutura AVL
*/
void freeAVLP (AVL* f){
  if(f){
    free(getKey(f));
    freeAVLP(getLeft(f));
    freeAVLP(getRight(f));
    freeProdP((ProdP*)(getEquals(f)));
    free(f);
    f = NULL;
  }
}



/**
* @brief                  Desaloca a memoria ocupada pela estrutura PpC
* @param [p]              Estrutura PpC
*/

void freePpC(ClieP* c){
  int i;
  for(i=0; i < c->ocupados; i++){
    free(c->produtosPorCliente[i]->nome);
    free(c->produtosPorCliente[i]);
  }
  free(c->produtosPorCliente);
  free(c);
}


/**
* @brief                 Desaloca a memoria ocupada pela estrutura AVL
* @param [f]             Estrutura AVL
*/
void freeAVLC (AVL* f){
  if(f){
    free(getKey(f));
    freeAVLC(getLeft(f));
    freeAVLC(getRight(f));
    freePpC((ClieP*)(getEquals(f)));
    free(f);
    f = NULL;
  }
}



/**
* @brief                Desaloca a memória ocupada pelos estrutura Filial
* @param [f]            Estrutura Filial
*/
void freeFilial(Filial* f){
  freeAVLP(f->produtos);
  freeAVLC(f->clientes);
  free(f);
  f = NULL;
}
