# Variabili
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = concatena.c genera_numeri.c arrayinteri.c converte16.c \
smista.c paridispari.c reverse.c smista.c somma_mancanti.c \
somme_distinte.c
EXEC = $(SRC:.c=)

EXECS = frequenze

# Regola di default
all: $(EXEC)

# Regola per costruire gli eseguibili
%: %.c
	$(CC) $(CFLAGS) $< -o $@

freq: $(EXECS)

frequenze: frequenze.o strint.o
	$(CC) $^ $(LDLIBS) -o $@

frequenze.o: frequenze.c strint.h
	$(CC) $< $(CFLAGS) -c -o $@


# Regola per la pulizia dei file eseguibili
.PHONY: clean

clean:
	rm -f $(EXEC)