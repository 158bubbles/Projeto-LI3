/**
* @brief    Ficheiro utilizado para imprimir os outputs das funçóes
* @file     clientes.c
*/
#include "print.h"



/**
* @brief                         Função que imprime o output da querie 2
* @param [q]                     Estrutura da querie 2
* @param [letter]                Letra inserida pelo utilizador
*/
void print2 (Q* q,char letter){
  if(system("clear"));
  int i,j,m,k,l;
  k = l = 0;
  if(getOcupadosQ(q)%10 != 0){
    int a = 0;
    for (j = 0; j < (getOcupadosQ(q)/10)+1 && a < getOcupadosQ(q); j++){
      printf("\n");
      for(i = 0; i < 10 && a < getOcupadosQ(q);i++){
        l++;
        printf("%d: %s  ",l,getSTRQ(q,a));
        a++;
      }
    }
  }
  else {
    int b = 0;
    for (m = 0; m < (getOcupadosQ(q)/10) && b < getOcupadosQ(q); m++){
      printf("\n");
      for(i = 0; i < 10 && b < getOcupadosQ(q); i++){
        k++;
        printf("%d: %s  ",k,getSTRQ(q,b));
        b++;
      }
    }
  }
  printf("\n");
  printf("Numero de produtos iniciados pela letra %c: %d\n",letter,getOcupadosQ(q));
}



/**
* @brief                         Função que imprime o output da querie 3
* @param [q]                     Estrutura da querie 3
* @param [mes]                   Mês inserido pelo utilizador
* @param [filial]                Filial inserida pelo utilizador
* @param [prod]                  Produto inserido pelo utilizador
*/
void print3(Q3* q, int mes, int filial, char* prod){
  if(system("clear"));
  int i;
  if(filial == 0){
    printf("O Numero total de Vendas em Promoção de Todos os filiais no mes %d: %d\n",mes,getNumTVenP(q,0));
    printf("O Numero total de Vendas sem Promoção de Todos os filiais %d: %d\n",mes,getNumTVenN(q,0));
    printf("A Faturacao total de Vendas em Promoção de Todos os filiais %d: %f\n",mes,getFatToP(q,0));
    printf("A Faturacao total de Vendas sem Promoção de Todos os filiais %d: %f\n",mes,getFatToN(q,0));
  }
  else {
    for(i = 1; i <= 3; i++){
      printf("O Numero total de Vendas em Promoção na filiail %d e no mes %d: %d\n",i,mes,getNumTVenP(q,i));
      printf("O Numero total de Vendas sem Promoção na filiail %d e no mes %d: %d\n",i,mes,getNumTVenN(q,i));
      printf("A Faturacao total de Vendas em Promoção na filiail %d e no mes %d: %f\n",i,mes,getFatToP(q,i));
      printf("A Faturacao total de Vendas sem Promoção na filiail %d e no mes %d: %f\n",i,mes,getFatToN(q,i));
    }
  }
}



/**
* @brief                         Função que imprime o output da querie 4
* @param [q]                     Estrutura da querie 4
* @param [letter]                Filial inserida pelo utilizador
*/
void print4(Q* q,int filial){
  if(system("clear"));
  int i,j,m,k,l;
  k = l = 0;
  if(getOcupadosQ(q)%6 != 0){
    int a = 0;
    for (j = 0; j < (getOcupadosQ(q)/6)+1 && a < getOcupadosQ(q); j++){
      printf("\n");
      for(i = 0; i < 6 && a < getOcupadosQ(q);i++){
        l++;
        printf("%d: %s  ",l,getSTRQ(q,a));
        a++;
      }
    }
  }
  else {
    int b = 0;
    for (m = 0; m < (getOcupadosQ(q)/6) && b < getOcupadosQ(q); m++){
      printf("\n");
      for(i = 0; i < 6 && b < getOcupadosQ(q); i++){
        k++;
        printf("%d: %s  ",k,getSTRQ(q,b));
        b++;
      }
    }
  }
  printf("\n");
  if(filial == 0)
    printf("Numero total de produtos nao comprados em todas as filiais: %d\n",getOcupadosQ(q));
  else
    printf("Numero total de produtos nao comprados na filial %d: %d\n",filial,getOcupadosQ(q));
}



/**
* @brief                         Função que imprime o output da querie 5
* @param [q]                     Estrutura da querie 5
*/
void print5 (Q* q){
  if(system("clear"));
  int i,j,m,k,l;
  k = l = 0;
  if(getOcupadosQ(q)%10 != 0){
    int a = 0;
    for (j = 0; j < (getOcupadosQ(q)/10)+1 && a < getOcupadosQ(q); j++){
      printf("\n");
      for(i = 0; i < 10 && a < getOcupadosQ(q);i++){
        l++;
        printf("%d: %s  ",l,getSTRQ(q,a));
        a++;
      }
    }
  }
  else {
    int b = 0;
    for (m = 0; m < (getOcupadosQ(q)/10) && b < getOcupadosQ(q); m++){
      printf("\n");
      for(i = 0; i < 10 && b < getOcupadosQ(q); i++){
        k++;
        printf("%d: %s  ",k,getSTRQ(q,b));
        b++;
      }
    }
  }
  printf("\n");
  printf("Numero total de produtos que compraram em todas as filiais: %d\n",getOcupadosQ(q));
}



/**
* @brief                         Função que imprime o output da querie 6
* @param [q]                     Estrutura da querie 6
*/
void print6 (Q6* q){
  if(system("clear"));
  printf("Número total de clientes que não comparam nada: %d\n",getNaoCompraramQ6(q));
  printf("Número total de produtos que não foram comprados: %d\n",getNaoCompradosQ6(q));
}



/**
* @brief                         Função que imprime o output da querie 7
* @param [q]                     Estrutura da querie 7
*/
void print7 (Q7* q){
  if(system("clear"));
  int i;
  for(i = 0; i < 3; i++){
    printf("+---------+---------+---------+---------+---------+---------+\n");
    printf("|                .:: Tabela da filial %d ::.                 |\n",i);
    printf("+---------+---------+---------+---------+---------+---------+\n");
    printf("| Janeiro |Fevereiro|  Marco  |  Abril  |   Maio  |  Junho  |\n");
    printf("+---------+---------+---------+---------+---------+---------+\n");
    printf("|  %3d    |   %3d   |   %3d   |   %3d   |   %3d   |   %3d   |\n",getQuantMesQ7(q,i,0),getQuantMesQ7(q,i,1),getQuantMesQ7(q,i,2),getQuantMesQ7(q,i,3),getQuantMesQ7(q,i,4),getQuantMesQ7(q,i,5));
    printf("+---------+---------+---------+---------+---------+---------+\n");
    printf("|  Julho  | Agosto  | Setembro| Outubro | Novembro| Dezembro|\n");
    printf("+---------+---------+---------+---------+---------+---------+\n");
    printf("|  %3d    |   %3d   |   %3d   |   %3d   |   %3d   |   %3d   |\n",getQuantMesQ7(q,i,6),getQuantMesQ7(q,i,7),getQuantMesQ7(q,i,8),getQuantMesQ7(q,i,9),getQuantMesQ7(q,i,10),getQuantMesQ7(q,i,11));
    printf("+---------+---------+---------+---------+---------+---------+\n");
    printf("\n");
  }
  int total = 0,j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 12; j++){
      total += getQuantMesQ7(q,i,j);
    }
  }
  printf("Numero de unidades compradas pelo cliente: %d\n",total);
}




/**
* @brief                         Função que imprime o output da querie 8
* @param [q]                     Estrutura da querie 8
* @param [minMes]                Limite inferior do intervalo de meses inserido pelo utilizador
* @param [maxMes]                Limite superior do intervalo de meses inserido pelo utilizador
*/
void print8 (Q8* q,int minMes,int maxMes){
  if(system("clear"));
  printf("Número total de vendas entre os meses %d e %d é: %d\n",minMes,maxMes,getTotalQ8(q));
  printf("O total faturado foi: %f\n",getFatQ8(q));
}



/**
* @brief                         Função que imprime o output da querie 9
* @param [q]                     Estrutura da querie 9
*/
void print9 (Q9* q){
  if(system("clear"));
  printf("------------------ C L I E N T E S      N ----------------\n");
  int i;
  for(i = 0; i < getOcupadosNQ9(q);i++ ){
    printf("(N) %d: %s\n",i+1,getSTRnQ9(q,i));
  }
  printf("O número total de clientes que compraram o produto (N) é: %d\n",getOcupadosNQ9(q));

  printf("------------------ C L I E N T E S      P ----------------\n");
  int j;
  for(j = 0; j < getOcupadosPQ9(q);j++ ){
    printf("(P) %d: %s\n",j+1,getSTRpQ9(q,j));
  }
  printf("O número total de clientes que compraram o produto (P) é: %d\n",getOcupadosPQ9(q));
}



/**
* @brief                         Função que imprime o output da querie 10
* @param [q]                     Estrutura da querie 10
*/
void print10 (Q10* q){
  if(system("clear"));
  printf("Os produtos comprados pelo cliente são:\n");
  int i;
  for(i = 0; i < getOcupadosQ10(q);i++){
    printf("%s: %d\n",getProdutoSTRP10(getSTRQ10(q,i)),getQuantSTRP10(getSTRQ10(q,i)));
  }
}



/**
* @brief                         Função que imprime o output da querie 11
* @param [q]                     Estrutura da querie 11
* @param [limit]                 Limite N
*/
void print11 (Q11* q,int limit){
  if(system("clear"));
  int i;
  printf("     Prod   Filial         Unidades \n");
  printf("Fil:        1    2    3    1   2   3\n");
  for(i = 0; i<limit;i++){
      printf("     %s %-4d %-4d %-4d %d %d %d\n",getProdutoFatura(getFaturaQ11(q,i)),
                                                getPorFilialC(getP11(q,i),0),getPorFilialC(getP11(q,i),1),getPorFilialC(getP11(q,i),2),
                                                getPorFilialNumeroU(getP11(q,i),0),getPorFilialNumeroU(getP11(q,i),1),getPorFilialNumeroU(getP11(q,i),2));
  }
}



/**
* @brief                         Função que imprime o output da querie 12
* @param [q]                     Estrutura da querie 12
* @param [limit]                 Limite N
*/
void print12 (Q12* q, int limit){
  if(system("clear"));
  int i;
  for(i = 0; i < limit; i++){
    printf("%d: %s\n",i+1,getProdutoQ12(getP12(q,i)));
  }
}




/**
* @brief                         Função que imprime o output da querie 13
* @param [q]                     Estrutura da querie 13
*/
void print13 (Q13* q){
  if(system("clear"));
  int i;
  for(i = 0; i < 3; i++){
    printf("%s : Lidas -> %d; Validas -> %d.\n",getPathQ13(q,i),getLidasQ13(q,i),getValidasQ13(q,i));
  }
}
