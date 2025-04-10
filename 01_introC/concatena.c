#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>

void termina(char *messaggio);

int main(int argc, char *argv[]){

    //prendo le cose da argv e le concateno in una sola stringa

    int lun = 0;
    int size = argc*10;

    char *finale = malloc(size*sizeof(char));
    if (finale == NULL) termina("malloc fallita");


    //array di stringhe, iesimo elemento jesima lettera
    for(int i = 1; i < argc; i++){
        for(int j = 0; j < (int)strlen(argv[i]); j++){
            if(lun == size){
                size = size*2;
                finale = realloc(finale, size * sizeof(char));
                if (finale == NULL) termina("realloc fallita");
                }
            finale[lun] = argv[i][j];
            lun++;
        }

    }

    //aggiungo terminatore
    if(lun == size){
        size = size*2;
        finale = realloc(finale, size * sizeof(char));
        if (finale == NULL) termina("realloc fallita");
    }
    finale[lun] = '\0';
    lun++;

    //realloco alla dimensione giusta
    finale = realloc( finale, lun*sizeof(char));


    puts(finale);

    free(finale);



    return 0;
}


void termina(char *messaggio)
{
  perror(messaggio);
  exit(1);
}