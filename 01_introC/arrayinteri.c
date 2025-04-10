#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe


//traccia:
/*
    scrivere un programma c che legge un intero n e costruisce
    i seguenti due array di interi:

    array a[] che numeri tra 1 e N mulipli di 3 ma non di 5

    array b[] che numeri tra 1 e N mulipli di 5 ma non di 3

*/

int main(){

    // prendo il numero N da tastiera
    int n = 0;
    puts("inserire un numero intero positivo : ");
    scanf("%d", &n);

    //creo i due array A e B di lunghezza N
    int *a;
    int *b;

    a = malloc(n*sizeof(int));
    if(a == NULL){
        puts("malloc fallita");
        exit(1);
    }

    b = malloc(n*sizeof(int));
    if(a == NULL){
        puts("malloc fallita");
        exit(1);
    }

    //creo una variabile contatore per gli indici degli array
    int indexA = 0;
    int indexB = 0;

    //variabili per la somma degli elementi dell'array
    int sumA = 0;
    int sumB = 0;

    
    //riempio l'array
    for(int i = 1; i<=n ; i++){
        if((i%3 == 0) && (i%5 != 0)){
            a[indexA] = i;
            indexA++;
            sumA+=i;
        }
        if((i%5 == 0) && (i%3 != 0)){
            b[indexB] = i;
            indexB++;
            sumB+=i;
        }
    }

    //realloco gli array con lo spazio utilizzato
    
    //array A
    a = realloc(a,indexA*sizeof(int));
    if(a == NULL){
        puts("realloc fallita");
        exit(2);
    }
    //array B
    b = realloc(b,indexB*sizeof(int));
    if(b == NULL){
        puts("realloc fallita");
        exit(2);
    }


    //stampo i riusltati
    printf("lunghezza a[] = %d , somma a[]= %d \n ", indexA , sumA);
    printf("lunghezza b[] = %d , somma b[]= %d \n ", indexB , sumB);


    //libero la memoria
    free(a); free(b);


    return 0;
}