# definizione del compilatore e dei flag di compilazione
# che vengono usate dalle regole implicite
CC=gcc
CFLAGS=-std=c11 -Wall -g -O -pthread
LDLIBS=-lm -pthread -lrt

# mi creo l'elenco degli eseguibili da creare
EXECS = pro_gen.out

# primo target: gl ieseguibili sono precodndizioni 
# quindi verranno tutti creati

all: $(EXECS)

# regola per la crezione la creazione degli eseguibili utlizzando xerrori.o
%.out: %.o xerrori.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# pattern rule che esprime che tutti i .o dipendono da xerrori.h
%.o %.c xerrori.h


clean: 
	rm *.o $(EXECS)


# crea file zip della lezione


