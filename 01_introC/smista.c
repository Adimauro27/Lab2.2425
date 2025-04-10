#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>


void termina(char *messaggio)
{
  perror(messaggio);
  exit(1);
}

bool primo(int k) {
  // se k è pari e diverso da 2 allora non è primo
  if(k%2==0 && k!=2) return false;
  // se k è dispari e non è primo
  // allora esiste un divisore <= sqrt(k)
  // che è dispari
  // quindi posso controllare solo i divisori dispari
  // e posso fermarmi a sqrt(k)
  for(int i=3; i*i<=k; i+=2) {
    if(k%i==0) return false;
  }
  return true;
}


void smista(char *nome, int n){

    for(int i = 1; i < n; i++){
        if(primo(i)){
            // allora controllo la cifra con cui finisce
            // lo metto nel file nome.ultimacifra.primi

            char *cifra = NULL;
            char *nomefile = NULL;

            int e;

            //controllo ultima cifra
            e = asprintf(&cifra, "%d", i);
            if ( e < 0 ) termina("controllo ultima cifra fallito");

            //prendo l'ultima cifra
            int last = strlen(cifra) - 1 ;
            char cif = cifra[ last ];

            //creo il file
            e = asprintf(&nomefile, "%s.%c.primi", nome, cif);
            if(e < 0 ) termina("palle culo");


            //apro il file
            FILE *f = fopen(nomefile, "a");

            //scrivo sul file
            fprintf( f, "%d \n", i );

            //chiudo il file
            fclose(f);
            //libero le variabili
            free(cifra);
            free(nomefile);
        }
    }

}






int main(int argc, char *argv[]){

    //controllo sull'input
    if(argc < 3) termina("argomenti sbagliati");

    smista(argv[1], atoi(argv[2])); 
    
    return 0;
}