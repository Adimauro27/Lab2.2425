#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>

/*Scrivere un programma C, che legge dalla linea di comando il nome di un file di testo contenente interi e stampa su stdout la somma degli interi compresi tra 1 e 1000 che non compaiono nell'array. Ad esempio, se il file di input contiene tutti gli interi tra 1 e 1000 tranne il 13, il 17, e il 49 il valore che deve essere stampato è 79 (la somma 13+17+49). Si noti che tutti i valori nel file non compresi tra 1 e 1000 non influenzano il risultato, e che il fatto che un valore compaia più volte non influenza il risultato: a noi interessa la somma dei valori tra 1 e 1000 che non sono nel file di input. (Suggerimento: per svolgere l'esercizio non è necessario salvare gli interi del file in un array, è invece necessario utilizzare un array di 1000 elementi per tenere conto di quali valori tra 1 e 1000 sono presenti nel file).*/


// let somma_m nomefile = 
    // prendo array da file
    //stampa stdout = 
        //somma di numero di array [1 - 1000] non presenti nell'array
void termina(char *messaggio);


int main(int argc, char *argv[]){
    int *array = malloc(1001*sizeof(int));

    //apro il file
    FILE *f = fopen(argv[1], "r");
    if(f == NULL) termina("apertura file fallita");

    int n = 0;
    while(true){
        int e = fscanf(f, "%d", &n);
        if(e==EOF){break;}else{
            if(n <= 1000 || n >= 1){
                array[n] = 1;
            }
        }
    }

    //variabile sommatoria
    int sum = 0;
    for(int i = 0 ; i < 1001; i++){
        if(array[i] == 0){
            sum += i;
        }
    }

    fprintf(stdout , " %d ", sum);
    
    free(array);
    fclose(f);
    return 0;
}



// stampa un messaggio d'errore e termina il programma
void termina(char *messaggio)
{
  perror(messaggio);
  exit(1);
}

 