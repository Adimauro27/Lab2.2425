#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>


bool in(int numero, int *a, int size){
    bool res = false;
    for(int i = 0; i < size; i++){
        if(a[i] == numero){
            res = true;
        }
    }
    return res;
}

int *somme_distinte(int a[], int n, int *size){

    int tmp = 0;
    int messi = 0;

    int *res = malloc(*size * sizeof(int));
    if(res == NULL){
        puts("malloc fallita");
        exit(1);
    }

    bool in0 = false;

    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            tmp = a[i] + a[j];
            if(tmp == 0 && in0 == false){
                in0=true;
                messi++;
                break;
                }
            printf(" %d + %d = %d \n",a[i], a[j], tmp);
            if( !(in(tmp, res, *size))){
                puts("non ce");
                if(messi >= *size){
                    *size = *size * 2;
                    res = realloc(res, *size*sizeof(int));
                    if(res == NULL){
                        puts("realloc fallita");
                        exit(1);
                    }
                }
                res[messi] = tmp;
                messi++;
            }else{}
    }
    }
    puts("zio ho finito");
    printf("MESSI : %d \n", messi);
    *size= messi;
    res = realloc(res,*size*sizeof(int));
    if(res == NULL){
        puts("realloc fallita;");
    }

    return res;
}





int main(int argc, char *argv[]){

    int n;
    int *a;
    int *b;

    int size = argc-1;
    int sizea = size;

    //i valori sono in argv[]
    //creo array
    a = malloc(sizea*sizeof(int));
    if(a == NULL){
        puts("malloc fallita");
        exit(1);
    }
    //inserisco valori
    for(int i = 1; i <= sizea; i++){
        int tmp = atoi(argv[i]);
        a[i-1] = tmp;

    }

    //chiamo funzione
    b = somme_distinte(a, sizea, &size);

    for(int i = 0; i < size; i++){
        printf(" %d ", b[i]);
    }

    puts("\n finito ");

    free(a);
    free(b);


    return 0;
}