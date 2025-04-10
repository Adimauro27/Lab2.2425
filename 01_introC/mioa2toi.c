#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>


int mioa2toi(const char *s, int *n){
    //stringa vuota
    if((int)strlen(s) == 0 || s==NULL){
        return 1;
    }

    //ingnoro gli spazi iniziali
    int i = 0;
    while(s[i] == ' '){
        i++;
    }

    int controllo_cifra = 0;
    int count_cifre = 0;

    //controlli vari
    int controllo = 0;
    for(int j = i ; j < (int)strlen(s); j++){

      //controllo se e' formata da caratteri non permessi
      if( (s[j] > 47 && s[j] < 58) || s[j] == 43 || s[j] == 45 ){
        //controllo se il segno inserito una sola volta
        if( (controllo_cifra == 0) && (s[j] == 43 || s[j] == 45) ){
          controllo_cifra = 1;
        }else if(controllo_cifra == 1){
          return 3; }else{
        if(s[j] == 32){
          break;
        }else{ return 2; }
      }
      }
    }

    if(count_cifre == 0){
      return 4;
    }
}

int main(int argc, char *argv[])
{
  for(int i=1;i<argc;i++) {
    int n, e;
    e = mioatoi(argv[i],&n);
    if(e!=0) printf("Errore conversione: %d\n",e);
    else printf("Mia funzione: %d, libreria: %d\n",n,atoi(argv[i]));
  }
  return 0;
} 