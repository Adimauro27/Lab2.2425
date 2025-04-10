#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>

int main(int argc, char *argv[]){
    for(int i = 1; i < argc; i++){
        for(int j = strlen(argv[i]); j>=0 ; j--){
            printf("%c",argv[i][j]);
        }
        puts(" ");
    }
    return 0; 
}