#ifndef queries_h
#define queries_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vendas.h"
#include "clientes.h"
#include "produtos.h"
#include "tree.h"
#include "faturacao.h"
#include "faturacoes.h"
#include "filial.h"
#include "interface.h"

typedef struct querie {
  int size;
  int ocup;
  char** str;
}Q;

typedef struct querie3{
  int numTVenN[4];
  int numTVenP[4];
  double fatToN[4];
  double fatToP[4];
}Q3;

typedef struct querie6{
  int naoCompraram;
  int naoComprados;
}Q6;


typedef struct querie7{
  int mes[3][12];
}Q7;

typedef struct querie8{
  int minMes;
  int maxMes;
  int Nvendas;
  double Tfaturado;
}Q8;



typedef struct querie9{
  int sizeN;
  int ocupN;
  char** strN;
  int sizeP;
  int ocupP;
  char** strP;
}Q9;

typedef struct produto10{
  char* prod;
  int quant;
}P10;

typedef struct querie10{
  int ocup;
  P10** str;
}Q10;


typedef struct p11{
  int porFilialC[3];
  int porFilialNumeroU[3];
}P11;

typedef struct querie11{
  P11** p;
  Fatura** str;
}Q11;

typedef struct p12{
  char* produto;
  double faturacao;
}P12;

typedef struct querie12{
  int ocup;
  P12** str;
}Q12;

typedef struct querie13{
  int validas[3];
  int lidas[3];
  char* path[3];
}Q13;


/*Querie 2*/
Q* getProductsStartedByLetter (SGV* sgv, char letter);
int getOcupadosQ (Q* q);
char* getSTRQ (Q* q,int i);
char** getSTRTQ(Q* q);
/*Querie 3*/
Q3* getProductSalesAndProfit(SGV* sgv, char* productID, int month, int filial);
int getNumTVenN (Q3* q,int i);
int getNumTVenP (Q3* q,int i);
double getFatToN (Q3* q,int i);
double getFatToP (Q3* q,int i);
/*Querie 4*/
Q* getProductsNeverBought (SGV* sgv, int branchID);
/*Querie 5*/
Q* getClientsOfAllBranches (SGV* sgv);
/*Querie 6*/
Q6* getClientsAndProductsNeverBought(SGV* sgv);
int getNaoCompraramQ6(Q6* q);
int getNaoCompradosQ6(Q6* q);
/*Querie 7*/
Q7* getProductsBoughtByClient (SGV* sgv, char* clientID);
int getQuantMesQ7(Q7* q,int filial, int mes);
/*Querie 8*/
Q8* getSalesAndProfit(SGV* sgv, int minMonth, int maxMonth);
int getTotalQ8(Q8* q);
double getFatQ8 (Q8* q);
/*Querie 9*/
Q9* getProductBuyers(SGV* sgv, char* productID, int branch);
int getOcupadosNQ9 (Q9* q);
int getOcupadosPQ9 (Q9* q);
char* getSTRnQ9 (Q9* q,int i);
char* getSTRpQ9 (Q9* q,int i);
/*Querie 10*/
int searchSTR(Q10* q,char* prod);
void updateSTR(Q10* q,PpC* p,int month);
void insereSTR(Q10* q, PpC* p,int month);
int compareQuantidade (const void* a,const void* b);
Q10* getClientsFavoriteProduct(SGV* sgv, char* clientID, int month);
char* getProdutoSTRP10 (P10* p);
int getQuantSTRP10(P10* p);
int getOcupadosQ10(Q10* q);
P10* getSTRQ10(Q10* q,int i);
/*Querie 11*/
void percorreAVL(AVL* a, Fatura** str,int* i);
int comparaFaturas (const void* a,const void* b);
Q11* getTopSelledProducts(SGV* sgv, int limit);
int getPorFilialC(P11* p, int i);
int getPorFilialNumeroU(P11* p, int i);
P11* getP11(Q11* q,int i);
Fatura* getFaturaQ11(Q11* q,int i);
/*Querie 12*/
int comparaFaturacao (const void* a,const void* b);
int searchFat(Q12* q,char* prod);
void updateFat(Q12* q,PpC* p);
void insereFat(Q12* q, PpC* p);
Q12* getClientTopProfitProducts(SGV* sgv,char* clientID, int limit);
char* getProdutoQ12(P12* p);
double getFaturacaoQ12(P12* p);
P12* getP12(Q12* q,int i);
int getOcupadosQ12(Q12* q);
/*Querie 13*/
Q13* getCurrentFilesInfo(SGV* sgv);
char* getPathQ13(Q13* q,int i);
int getValidasQ13(Q13* q,int i);
int getLidasQ13(Q13* q,int i);



#endif
