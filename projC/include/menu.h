#ifndef menu_h
#define menu_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "vendas.h"
#include "clientes.h"
#include "produtos.h"
#include "tree.h"
#include "faturacao.h"
#include "faturacoes.h"
#include "filial.h"
#include "interface.h"
#include "queries.h"
#include "print.h"


char* getPath ();
void menu (SGV* sgv);

#endif
