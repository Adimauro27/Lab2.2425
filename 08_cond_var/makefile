# definizione del compilatore e dei flag di compilazione
# che vengono usate dalle regole implicite
CC=gcc
CFLAGS=-std=c11 -Wall -g -O -pthread
LDLIBS=-lm -lrt -pthread


# su https://www.gnu.org/software/make/manual/make.html#Implicit-Rules
# sono elencate le regole implicite e le variabili 
# usate dalle regole implicite 

# Variabili automatiche: https://www.gnu.org/software/make/manual/make.html#Automatic-Variables
# nei comandi associati ad ogni regola:
#  $@ viene sostituito con il nome del target
#  $< viene sostituito con il primo prerequisito
#  $^ viene sostituito con tutti i prerequisiti

# elenco degli eseguibili da creare
EXECS= manza

# primo target: gli eseguibili sono precondizioni del target
# quindi verranno tutti creati
all: $(EXECS) 

# target finale dell'eseguibile
manza: fair_mia.o xerrori.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# compilazione del file oggetto da fair_mia.c
fair_mia.o: fair_mia.c xerrori.h
	$(CC) $(CFLAGS) -c fair_mia.c -o fair_mia.o

# build per la versione statica (con -DMANZA)
fair_mia_statica: fair_mia.c xerrori.h
	$(CC) $(CFLAGS) -O3 -DMANZA -c $< -o $@

# build della versione dinamica
fair_mia_dinamica: fair_mia.c xerrori.h
	$(CC) $(CFLAGS) -O3 -c $< -o $@

# Copie per creare i .out
fair_mia_statica.out: fair_mia_statica
	cp $< $@

fair_mia_dinamica.out: fair_mia_dinamica
	cp $< $@

clean: 
	rm -f *.o $(EXECS) *.out fair_mia_statica fair_mia_dinamica

