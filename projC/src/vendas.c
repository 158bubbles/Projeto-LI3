/**
* @brief    Ficheiro que contem funções utilizadas para as vendas
* @file     vendas.c
*/
#include "vendas.h"

struct venda{
  char* produto;
  double preco;
  int quantidade;
  char promocao;
  char* cliente;
  int data;
  int filial;
};


struct vt {
  int size;
  int ocupados;
  int lidas;
  Venda* str;
};


/**
* @brief                Inicialização dos dados das vendas
* @return               Nova venda
*/
VT* initVendas (){
  VT* v = malloc(sizeof(VT));
  v->size = 0;
  v->ocupados = 0;
  v->lidas = 0;
  v->str = NULL;
  return v;
}


/**
* @brief                Função que desaloca a memória ocupada pelas Vendas
* @param [d]            uma venda
*/
void freeVendas(VT* v){
  int i = 0;
  for(i = 0; i < v->ocupados; i++){
    free(v->str[i].produto);
    v->str[i].produto = NULL;
    free(v->str[i].cliente);
    v->str[i].cliente = NULL;
  }
  free(v->str);
  v->str = NULL;
  free(v);
  v = NULL;
}


/**
* @brief                Função que realoca a memoria ocupada pelas Vendas
* @param [d]            Uma venda
*/
void reallocVendas (VT *v){
  v->size  = 2 * v->size +1;
  v->str =realloc(v->str,sizeof(Venda)*v->size);
  /*Venda* aux = malloc(sizeof(Venda)*v->size);
  int t;
  for(t = 0; t < (v->size-1)/2; t++){
    aux[t].produto = strdup(v->str[t].produto);
    free(v->str[t].produto);
    aux[t].preco = v->str[t].preco;
    aux[t].quantidade = v->str[t].quantidade;
    aux[t].promocao = v->str[t].promocao;
    aux[t].cliente = strdup(v->str[t].cliente);
    free(v->str[t].cliente);
    aux[t].data = v->str[t].data;
    aux[t].filial= v->str[t].filial;
    free(v->str[t]);
  }
  free(v->str);
  v->str = aux;*/

}


/**
* @brief                  Função que efetua a procura binária
* @param [total]          char** onde queremos fazer a procura
* @param [i]              Indice i
* @param [t]              Indice t
* @param [str]            char* que queremos encontrar
* @return                 Retorna -1 caso a procura falhe
*/
int binarySearch(char** total, int i, int t, char* str)
{
    while (i <= t) {
        int m = i + (t - i) / 2;

        if (strcmp(total[m],str) == 0)
            return m;
        if (strcmp(total[m],str) < 0)
            i = m + 1;
        else
            t = m - 1;
    }
    return -1;
}


/**
* @brief                   Valida a componente produto
* @param [prod]            Um produto
* @param [produto]         Dados dos produtos
* @return                  Um r que nos diz se um produto é validado (r=1) ou não (r=0)
*/
int product (char* prod, Dados* produtos){
  int r = 0;
  if ((binarySearch(produtos->str,0,(produtos->ocupados)-1,prod)) != -1){
      r = 1;
  }
  return r;
}


/**
* @brief                   Valida a componente preço
* @param [prod]            Preço
* @return                  Um r que nos diz se um preço é validado (r=1) ou não (r=0)
*/
int price (double preco){
  int r = 0;
  if (preco >= 0) r = 1;
  return r;
}

/**
* @brief                   Valida a componente quantidade
* @param [prod]            Quantidade
* @return                  Um r que nos diz se uma quantidade é validada (r=1) ou não (r=0)
*/
int quantity (int quant){
  int r = 1;
  if (quant >= 0) r = 1;
  return r;
}


/**
* @brief                   Valida a componente promoção
* @param [prod]            Promoção
* @return                  Um r que nos diz se uma promoção é validada (r=1) ou não (r=0)
*/
int promotion (char prom){
  int r = 0;
  if(prom == 'N' || prom == 'P') r = 1;
  return r;
}


/**
* @brief                   Valida a componente cliente
* @param [prod]            Cliente
* @return                  Um r que nos diz se um cliente é validado (r=1) ou não (r=0)
*/
int client (char* cli, Dados* clientes){
  int r = 0;
  if ((binarySearch(clientes->str,0,(clientes->ocupados)-1,cli)) != -1){
    r = 1;
  }
  return r;
}


/**
* @brief                   Valida a componente mês
* @param [prod]            Mês
* @return                  Um r que nos diz se um mês é validado (r=1) ou não (r=0)
*/
int month (int mes){
  int r = 0;
  if (mes == 1 ||
      mes == 2 ||
      mes == 3 ||
      mes == 4 ||
      mes == 5 ||
      mes == 6 ||
      mes == 7 ||
      mes == 8 ||
      mes == 9 ||
      mes == 10 ||
      mes == 11 ||
      mes == 12) r = 1;
  return r;
}


/**
* @brief                   Valida a componente filial
* @param [prod]            Filial
* @return                  Um r que nos diz se uma filial é validada (r=1) ou não (r=0)
*/
int market (int super){
  int r = 0;
  if (super == 1 || super == 2 || super == 3) r = 1;
  return r;
}


/**
* @brief                   Valida a componente venda
* @param [prod]            Produto
* @param [preco]           Preço
* @param [quant]           Quantidade
* @param [prom]            Promoção
* @param [cli]             Cliente
* @param [produtos]        Dados dos produtos
* @param [clientes]        Dados dos clientes
* @return                  Um r que nos diz se uma venda é validada (r=1) ou não (r=0)
*/
int valid_Venda (char* prod, double preco,int quant, char prom,char *cli, int mes, int super, Dados* produtos, Dados* clientes){
  int r = 1;
  if (!product(prod,produtos) ||
      !price(preco) ||
      !quantity(quant) ||
      !promotion(prom) ||
      !client(cli,clientes) ||
      !month(mes) ||
      !market(super)) r = 0;
  return r;
}


/**
* @brief                   Acesso à componente produto
* @param [v]               Uma venda
* @return                  Um produto
*/
char* getProduto(Venda*v){
  return strdup(v->produto);
}


/**
* @brief                   Acesso à componente preço
* @param [v]               Uma venda
* @return                  Um preço
*/
double getPreco(Venda* v){
  return v->preco;
}


/**
* @brief                   Acesso à componente quantidade
* @param [v]               Uma venda
* @return                  Uma quantidade
*/
int getQuantidade(Venda* v){
  return v->quantidade;
}


/**
* @brief                   Acesso à componente promoção
* @param [v]               Uma venda
* @return                  Um r que nos diz se uma promoção é do tipo P (r=1) ou do tipo N (r=0)
*/
int getPromocao(Venda* v){
  int r = 0;
  if (v->promocao == 'N')
    r = 0;
  else if(v->promocao == 'P')
    r = 1;
  return r;
}


/**
* @brief                   Acesso à componente cliente
* @param [v]               Uma venda
* @return                  Um cliente
*/
char* getCliente(Venda* v){
  return strdup(v->cliente);
}


/**
* @brief                   Acesso à componente data
* @param [v]               Uma venda
* @return                  Uma data
*/
int getData (Venda* v){
  return v->data;
}


/**
* @brief                   Acesso à componente filial
* @param [v]               Uma venda
* @return                  Uma filial
*/
int getFilial (Venda* v){
  return v->filial;
}


/**
* @brief                  Função que lê um ficheiro .txt com a informacao relativa às vendas
* @param [vendas]         Vendas
* @param [produtos]       Dados dos produtos
* @param [clientes]       Dados dos clientes
* @param [filePath]       Caminho do ficheiro
*/
void read_Vendas (VT *vendas,Dados* produtos,Dados* clientes, char* filePath){
  FILE* f = fopen(filePath, "r");
  if (f == NULL){
    printf("Ficheiro vendas inexistente\n");
  }
  char str[64];

  while(fgets(str,64,f)){
    vendas->lidas++;
    char* aux = strdup(str);
    char* prod = strtok(aux," ");
    double pre = atof(strtok(NULL," "));
    int quant = atoi(strtok(NULL," "));
    char* prom = strtok(NULL," ");
    char* cli = strtok(NULL," ");
    int mes = atoi(strtok(NULL," "));
    int super = atoi(strtok(NULL,"\r\n"));
    if(valid_Venda(prod,pre,quant,prom[0],cli,mes,super,produtos,clientes)){
      if(vendas->size == vendas->ocupados){
        reallocVendas(vendas);
      }
      vendas->str[vendas->ocupados].produto = strdup(prod);
      vendas->str[vendas->ocupados].preco = pre;
      vendas->str[vendas->ocupados].quantidade = quant;
      vendas->str[vendas->ocupados].promocao = prom[0];
      vendas->str[vendas->ocupados].cliente = strdup(cli);
      vendas->str[vendas->ocupados].data = mes;
      vendas->str[vendas->ocupados].filial= super;
      vendas->ocupados++;
    }
    free(aux);
  }
  fclose(f);
}


/**
* @brief                   Função que devolve o espaço ocupado pelas vendas na string
* @param [produtos]        Vendas
* @return                  Espaço ocupado pelas vendas na string
*/
int getOcupadosV (VT* vendas){
  return vendas->ocupados;
}


/**
* @brief                   Função que devolve as vendas lidas
* @param [produtos]        Vendas
* @return                  Vendas lidas
*/
int getLidasV (VT* vendas){
  return vendas->lidas;
}


/**
* @brief                   Função que devolve um array com as vendas
* @param [produtos]        Vendas
* @param [i]               Indíce do array str
* @return                  Array com as vendas
*/
Venda* getVenda(VT* vendas, int i){
  return &vendas->str[i];
}
