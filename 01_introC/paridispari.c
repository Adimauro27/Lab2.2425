#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>
int main(int argc, char *argv[]){

    //qualche controllo sul giusto inserimento dei parametri
    // .... 
    // ....

    //apro il file
    FILE *f = fopen(argv[1],"r" );
    FILE *pari = fopen(argv[2],"w+" );
    FILE *dispari = fopen(argv[3],"w+" );
    if(f == NULL || pari == NULL || dispari == NULL){
        puts("errore apertura del file");
        exit(1);
    }

    //leggo i numeri dal file e devo decidere se metterlo nel file pari
    //o nel file dipari
    int n = 0;
    while(true){
        int e = fscanf(f, "%d", &n);
        if(e==EOF){break;}
        if(n%2 == 0){
            fprintf(pari, "%d\n", n);
        }else{
            fprintf(dispari, "%d\n", n);
        }
    }

    fclose(f);
    fclose(pari);
    fclose(dispari);


    return 0;
}