#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "menu.h"
#include "interface.h"

int main(){
  SGV* sgv= initSGV();
  clock_t start_time,end_time;
  start_time = clock();
  menu(sgv);
  end_time = clock();
  double time_used = ((double)end_time-start_time)/CLOCKS_PER_SEC;
  destroySGV(sgv);
  printf("Tempo de Execucao: %fs\n",time_used);
  return 0;
}
