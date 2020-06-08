IDIR = ../include
CC = gcc
CFLAGS= -ansi -D_GNU_SOURCE -Wall -g -I$(IDIR)

ODIR=obj

_DEPS = menu.h interface.h print.h queries.h vendas.h filial.h clientes.h produtos.h tree.h faturacoes.h faturacao.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =  main.o menu.o interface.o print.o queries.o vendas.o filial.o clientes.o  produtos.o tree.o faturacoes.o faturacao.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	[ -d $(ODIR)] || mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	doxygen Doxyfile

memcheck:
	valgrind --leak-check=full ./program


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -rf ../docs/html
	rm -rf ../docs/latex
