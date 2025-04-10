#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>


// stampa un messaggio d'errore e termina il programma
void termina(char *messaggio)
{
  perror(messaggio);
  exit(1);
}

char *converte16(int n){
    char *res;

    asprintf(&res, "%x", n );
    if(res == NULL) termina("conversione fallita");

    return res;
}


int main(int argc, char *argv[]){

    //controllo sull'input
    if(argc < 2 ) termina("argomenti passati non validi");

    //chiamo la funzione converte16 su tutti i paramentri
    for(int i = 1; i < argc ; i++){
        fprintf(stdout, "%s \n", converte16( atoi(argv[i]) ));
    }

    return 0;
}