#include "menu.h"


char* getPath (){
  char* aux = NULL;
  char* path = malloc(sizeof(char)*64);
  while(1){
    aux = fgets(path,64,stdin);
    aux = strtok(aux,"\n");
    if(fopen(aux,"r")) break;
    else printf("Ficheiro inexistente\n");
  }
  return aux;

}

void menu (SGV* sgv){
  int flag = 0;
  char* aux = NULL;
  char* querie = malloc(sizeof(char)*64);
  int querieI;
  if(system("clear"));
  do {
    printf("--------------- M E N U ---------------\n");
    printf("1 - loadSGVFromFiles\n");
    printf("2 - getProductsStartedByLetter\n");
    printf("3 - getProductSalesAndProfit\n");
    printf("4 - getProductsNeverBought\n");
    printf("5 - getClientsOfAllBranches\n");
    printf("6 - getClientsAndProductsNeverBought\n");
    printf("7 - getProductsBoughtByClient\n");
    printf("8 - getSalesAndProfit\n");
    printf("9 - getProductBuyers\n");
    printf("10 - getClientsFavoriteProduct\n");
    printf("11 - getTopSelledProducts\n");
    printf("12 - getClientTopProfitProducts\n");
    printf("13 - getCurrentFilesInfo\n");
    printf("14 - Exit\n");
    printf("\n");
    printf("Insira o comando:\n");

    aux = fgets(querie,64,stdin);
    aux = strtok(aux,"\n");
    querieI = atoi(aux);
    switch (querieI) {
      case 1:{
        clock_t start,end;
        double time_used;
        printf("Default?[Y/N]\n");
        char* aux1 = NULL;
        char* var = malloc(sizeof(char*)*10);
        aux1 = fgets(var,10,stdin);
        aux1 = strtok(aux1,"\n");
        aux1[0] = toupper(aux1[0]);
        if(aux1[0] == 'Y' && strlen(aux1) == 1){
          char productsPath[] = "../DadosIniciais/Produtos.txt";
          char clientsPath[] = "../DadosIniciais/Clientes.txt";
          char salesPath[] = "../DadosIniciais/Vendas_1M.txt";
          start = clock();
          sgv = loadSGVFromFiles(sgv,clientsPath,productsPath,salesPath);
          end = clock();
          time_used = ((double)(end-start))/CLOCKS_PER_SEC;
          printf("\n");
          printf("Tempo de execucao: %fs\n",time_used);
          printf("\n");
        }
        else if(aux1[0] == 'N' && strlen(aux1) == 1){
          clock_t start,end;
          double time_used;
          printf("Insira a diretoria dos produtos:\n");
          char* productsPath = getPath();
          printf("Insira a diretoria dos clientes:\n");
          char* clientsPath = getPath();
          printf("Insira a diretoria dos vendas:\n");
          char* salesPath = getPath();
          start = clock();
          loadSGVFromFiles(sgv,clientsPath,productsPath,salesPath);
          end = clock();
          time_used = ((double)(end-start))/CLOCKS_PER_SEC;
          printf("\n");
          printf("Tempo de execucao: %fs\n",time_used);
          printf("\n");
          free(productsPath);
          free(clientsPath);
          free(salesPath);
        }
        else {
          printf("Resposta Invalida\n");
        }
        free(var);
        flag = 1;
        break;
      }
      case 2:{
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          printf("Insira a letra:\n");
          char* aux2 = NULL;
          char* var = malloc(sizeof(char*)*10);
          aux2 = fgets(var,10,stdin);
          aux2 = strtok(aux2,"\n");
          if(isupper(aux2[0]) && strlen(aux2) == 1){
            struct querie* q2 = getProductsStartedByLetter (sgv,aux2[0]);
            print2(q2,aux2[0]);
            int f;
            for(f = 0; f < getOcupadosQ(q2); f++){
              free(getSTRQ(q2,f));
            }
            free(getSTRTQ(q2));
            free(q2);
          }
          else{
            printf("Letra invalida\n");
          }
          free(var);
        }
        break;
      }
      case 3:{
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          printf("Insira um produto:\n");
          char* aux3 = NULL;
          char* produto = malloc(sizeof(char*)*24);
          aux3 = fgets(produto,24,stdin);
          strtok(aux3,"\n");
          printf("Insira o mês:\n");
          char* auxM = NULL;
          char* mes = malloc(sizeof(char*)*10);
          auxM = fgets(mes,10,stdin);
          strtok(auxM,"\n");
          int mesI = atoi(auxM);
          printf("Deseja todas filiais?[Y/N]\n");
          char* auxF = NULL;
          char* filial = malloc(sizeof(char*)*10);
          auxF = fgets(filial,10,stdin);
          strtok(auxF,"\n");
          auxF[0] = toupper(auxF[0]);
          if(valid_Produtos(aux3) == 0 || month(mesI) == 0){
            printf("Dados invalidos\n");
          }
          else {
            if( auxF[0] == 'Y' && strlen(auxF) == 1){
              struct querie3* q3 = getProductSalesAndProfit(sgv,aux3,mesI,0);
              print3(q3,mesI,0,aux3);
              free(q3);
            }
            else{
              Q3* q3 = getProductSalesAndProfit(sgv,aux3,mesI,1);
              print3(q3,mesI,1,aux3);
              free(q3);
            }
          }
          free(produto);
          free(mes);
          free(filial);
        }
        break;
      }
      case 4:{
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else{
          printf("Deseja todas filiais?[Y/N]\n");
          char* aux4 = NULL;
          char* ques = malloc(sizeof(char*)*10);
          aux4 = fgets(ques,10,stdin);
          strtok(aux4,"\n");
          aux4[0] = toupper(aux4[0]);
          if(aux4[0] == 'Y'){
            struct querie* q4 = getProductsNeverBought(sgv,0);
            print4(q4,0);
            int f;
            for(f = 0; f < q4->ocup; f++){
              free(q4->str[f]);
            }
            free(q4->str);
            free(q4);
          }
          else {
            printf("Qual a filial?\n");
            char* aux4F = NULL;
            char* filial = malloc(sizeof(char*)*10);
            aux4F = fgets(filial,10,stdin);
            strtok(aux4F,"\n");
            int filialI = atoi(aux4F);
            if(filialI == 1 || filialI == 2 || filialI == 3){
              Q* q4 = getProductsNeverBought(sgv,filialI);
              print4(q4,filialI);
              int f;
              for(f = 0; f < q4->ocup; f++){
                free(q4->str[f]);
              }
              free(q4->str);
              free(q4);
              free(filial);
            }
            else {
              printf("Filial inexistente\n");
            }
          }
          free(ques);
        }
        break;
      }
      case 5:{
        if(flag != 1){
            printf("Estrutura não inicializada\n");
        }
        else {
          struct querie* q5 = getClientsOfAllBranches(sgv);
          print5(q5);
          int f;
          for(f = 0; f < q5->ocup; f++){
            free(q5->str[f]);
          }
          free(q5->str);
          free(q5);
        }
        break;
      }
      case 6:{
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          start = clock();
          struct querie6* q6 = getClientsAndProductsNeverBought(sgv);
          end = clock();
          time_used = ((double)(end-start))/CLOCKS_PER_SEC;
          print6(q6);
          printf("\n");
          printf("Tempo de execucao: %fs\n",time_used);
          printf("\n");
          free(q6);
        }
        break;
      }
      case 7: {
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          printf("Insira um cliente:\n");
          char* aux7 = NULL;
          char* cliente = malloc(sizeof(char*)*24);
          aux7 = fgets(cliente,24,stdin);
          strtok(aux7,"\n");
          if(valid_Clientes(aux7) == 0 ){
            printf("Cliente invalido\n");
          }
          else {
            start = clock();
            struct querie7* q7 = getProductsBoughtByClient(sgv,aux7);
            end = clock();
            time_used = ((double)(end-start))/CLOCKS_PER_SEC;
            print7(q7);
            printf("\n");
            printf("Tempo de execucao: %fs\n",time_used);
            printf("\n");
            free(q7);
          }
          free(cliente);
        }
        break;
      }
      case 8:{
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          printf("Insira o limite inferior do intervalo de tempo:\n");
          char* auxI = NULL;
          char* inf = malloc(sizeof(char*)*10);
          auxI = fgets(inf,10,stdin);
          strtok(auxI,"\n");
          int infI = atoi(auxI);
          printf("Insira o limite superior do intervalo de tempo:\n");
          char* auxS = NULL;
          char* sup = malloc(sizeof(char*)*10);
          auxS = fgets(sup,10,stdin);
          strtok(auxS,"\n");
          int supI = atoi(auxS);
          if(month(infI) != 0 && month(supI) != 0 && infI < supI){
            start = clock();
            struct querie8* q8 = getSalesAndProfit(sgv,infI,supI);
            end = clock();
            time_used = ((double)(end-start))/CLOCKS_PER_SEC;
            print8(q8,infI,supI);
            printf("\n");
            printf("Tempo de execucao: %fs\n",time_used);
            printf("\n");
            free(q8);
          }
          else {
            printf("Dados invalidos\n");
          }

          free(inf);
          free(sup);
        }
        break;
      }
      case 9:{
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          printf("Insira um produto:\n");
          char* aux9 = NULL;
          char* produto = malloc(sizeof(char*)*24);
          aux9 = fgets(produto,24,stdin);
          strtok(aux9,"\n");
          printf("Insira a filial desejada:\n");
          char* aux9F = NULL;
          char* filial = malloc(sizeof(char*)*10);
          aux9F = fgets(filial,10,stdin);
          strtok(aux9F,"\n");
          int filialI = atoi(aux9F);
          if(valid_Produtos(aux9) && market(filialI)){
            start = clock();
            struct querie9* q9 = getProductBuyers(sgv,aux9,filialI);
            end = clock();
            time_used = ((double)(end-start))/CLOCKS_PER_SEC;
            print9(q9);
            printf("\n");
            printf("Tempo de execucao: %fs\n",time_used);
            printf("\n");
            int fN,fP;
            for(fN = 0; fN < q9->ocupN; fN++){
              free(q9->strN[fN]);
            }
            for(fP = 0; fP < q9->ocupP; fP++){
              free(q9->strP[fP]);
            }
            free(q9->strN);
            free(q9->strP);
            free(q9);
          }
          else{
            printf("Dados invalidos \n");
          }
          free(produto);
          free(filial);
        }

        break;
      }
      case 10: {
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          printf("Insira um cliente:\n");
          char* aux10 = NULL;
          char* cliente = malloc(sizeof(char*)*24);
          aux10 = fgets(cliente,24,stdin);
          strtok(aux10,"\n");
          printf("Insira o mês:\n");
          char* aux10M = NULL;
          char* mes = malloc(sizeof(char*)*10);
          aux10M = fgets(mes,10,stdin);
          strtok(aux10M,"\n");
          int mesI = atoi(aux10M);
          if(valid_Clientes(aux10) && month(mesI)){
            start = clock();
            struct querie10* q10 = getClientsFavoriteProduct(sgv,aux10,mesI);
            end = clock();
            time_used = ((double)(end-start))/CLOCKS_PER_SEC;
            print10(q10);
            printf("\n");
            printf("Tempo de execucao: %fs\n",time_used);
            printf("\n");
            int f;
            for(f = 0; f < q10->ocup; f++){
              free(q10->str[f]->prod);
              free(q10->str[f]);
            }
            free(q10->str);
            free(q10);
          }
          else{
            printf("Dados invalidos \n");
          }
          free(cliente);
          free(mes);
        }

        break;
      }
      case 11: {
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          printf("Insira o limite:\n");
          char* aux11 = NULL;
          char* limit = malloc(sizeof(char*)*10);
          aux11 = fgets(limit,10,stdin);
          strtok(aux11,"\n");
          int limitI = atoi(aux11);
          start = clock();
          struct querie11* q11 = getTopSelledProducts(sgv,limitI);
          end = clock();
          time_used = ((double)(end-start))/CLOCKS_PER_SEC;
          print11(q11,limitI);
          printf("\n");
          printf("Tempo de execucao: %fs\n",time_used);
          printf("\n");
          int f;
          for(f = 0; f < limitI; f++){
            free(q11->p[f]);
            freeNodoAVLFatura(q11->str[f]);
          }
          free(q11->p);
          free(q11->str);
          free(q11);
          free(limit);

        }
        break;
      }
      case 12: {
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          printf("Insira um cliente:\n");
          char* aux12 = NULL;
          char* cliente = malloc(sizeof(char*)*24);
          aux12 = fgets(cliente,24,stdin);
          strtok(aux12,"\n");
          printf("Insira o limite:\n");
          char* aux12L = NULL;
          char* limit = malloc(sizeof(char*)*10);
          aux12L = fgets(limit,10,stdin);
          strtok(aux12L,"\n");
          int limitI = atoi(aux12L);
          if(valid_Clientes(aux12)){
            start = clock();
            struct querie12* q12 = getClientTopProfitProducts(sgv,aux12,limitI);
            end = clock();
            time_used = ((double)(end-start))/CLOCKS_PER_SEC;
            print12(q12,limitI);
            printf("\n");
            printf("Tempo de execucao: %fs\n",time_used);
            printf("\n");
            int f;
            for(f = 0; f < q12->ocup; f++){
              free(q12->str[f]->produto);
              free(q12->str[f]);
            }
            free(q12->str);
            free(q12);
          }
          else{
            printf("Dados invalidos\n");
          }
          free(cliente);
          free(limit);
        }

        break;
      }
      case 13: {
        if(flag != 1){
          printf("Estrutura não inicializada\n");
        }
        else {
          clock_t start,end;
          double time_used;
          start = clock();
          struct querie13* q13 = getCurrentFilesInfo(sgv);
          end = clock();
          time_used = ((double)(end-start))/CLOCKS_PER_SEC;
          print13(q13);
          printf("\n");
          printf("Tempo de execucao: %fs\n",time_used);
          printf("\n");
          free(q13);
        }
        break;
      }
      default:{
        break;
      }
    }
  } while(querieI!= 14);
  free(querie);
}
