#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // confronto/copia/etc di stringhe
#include <errno.h>
#include <time.h>


/*Scrivere un programma che legge dalla riga di comando un elenco di nomi di file e stampa l'elenco di questi file ordinati per dimensione decrescente, i file con la stessa dimensione devono essere ordinati lessicograficamente.
*/


void termina(const char *messaggio)
{
  // se errno!=0 oltre al mio messaggio stampa il messaggio
  // associato alla variabile globale errno 
  // utilizzando la funzione di libreria perror()
  if(errno!=0) perror(messaggio);
  // altrimenti stampa solo il mio messaggio
  else fprintf(stderr,"%s\n", messaggio);
  exit(1);
}


// definizione struct che rappresenta
// una file con nome e lunghezza
typedef struct {
  char *nome;
  long lung; 
} miofile;

miofile *miofile_crea(char *s){
    //apro il file in lettura
    FILE *f = fopen(s,"r");
    if(f == NULL){
        fprintf(stderr,"non e' stato possibile aprire il file %s \n", s);
        return NULL;
    }

    if(fseek(f,0,SEEK_END) != 0 ){
        fprintf(stderr, "non e' stato possibile fare seek su file %s \n", s);
        fclose(f);
        return NULL;
    }

    //ora il puntatore e' alla fine del file
    long pos = ftell(f); //prendo il numero di byte dall'inizio del file e quindi la sua "dimensione"
    if(pos<0){
        fprintf(stderr, "non e' stato possibile fare ftell su file %s\n", s);
        fclose(f);
        return NULL;
    }
    fclose(f);
    //se siamo arrivati qui pos contiene la lunghezza del file in byte
    miofile *a = malloc(sizeof(*a));
    if(a==NULL) termina("memoria insufficiente");
    a->nome = strdup(s);
    a->lung = pos;

    return a;
}

// distrugge (dealloca) un oggetto capitale 
void miofile_distruggi(miofile *a)
{
  free(a->nome);
  free(a);
}

// stampa sul file *f i campi del file *a
void miofile_stampa(const miofile *a, FILE *f) {
  fprintf(f,"%20ld %s\n",a->lung,a->nome);
}

void merge(miofile **a , int na , miofile **c , int nc , miofile **b);
void mergesort(miofile **a , int n ){

    //controlli su arr
    assert(a!=NULL);
    assert(n>0);

    //caso base
    if(n==1) return;
    
    int n1 = n/2;
    int n2 = n - n1;
    assert(n1 + n2 == n);

    //ordino la prima meta'
    mergesort(a, n1);
    //ordino la seconda meta'
    mergesort(&a[n1], n2);

    // ora ho due meta' ordinate devo fare il merge
    miofile **b = malloc(n*sizeof(*b));
    if(b == NULL) termina("malloc fallita nel merge");
    merge(a,n1,a+n1,n2,b);
    //copio il risultato da b[] ad a[]
    for(int i = 0; i<n ; i++){
        a[i] = b[i];
    }
    free(b); //dealloco array temporaneo b[]
}





int main(int argc, char *argv[]){

    if(argc < 2){
        printf("uso: %s nome1 [nome2 nome3 ...] \n ",argv[0]);
        exit(1);
    }
    miofile **arr;
    arr = malloc((argc-1)*sizeof(*arr));
    int n=0; //numero di elementi in arr[]
    for(int i =1 ; i < argc ; i++){
        //provo ad inserire argv[i]
        miofile *tmp = miofile_crea(argv[i]);
        if(tmp!=NULL){
            arr[n++] = tmp;
        }
    }
    //stampa array
    for(int i =0; i<n ; i++){
        miofile_stampa(arr[i], stdout);
    }

    puts("pippo ---------------");

    puts("\n \n ordiamo l'array \n \n");
    //ordino l'array
    mergesort(arr,n);
    //stampa array
    for(int i =0; i<n ; i++){
        miofile_stampa(arr[i], stdout);
    }

    
    puts("pippo ---------------");
    
    
    //dealloa i singoli file e l'array
    for(int i = 0; i < n ; i++){
        miofile_distruggi(arr[i]);
    }
    free(arr);
    
    return 0;
}

void merge(miofile **a , int na , miofile **c , int nc , miofile **b){
    assert(a!=NULL);
    assert(c!=NULL);
    assert(b!=NULL);
    assert(na>0);
    assert(nc>0);

    int i = 0; //indice per a[]
    int j = 0; //indice per c[]
    int k = 0; //indice per b[]

    //scorro a[] e c[] e copio il minore in b[]
    while(i<na && j<nc){
        if(!(a[i]->lung < c[j]->lung)){
            b[k] = a[i];
            i++;
        }else{
            b[k] = c[j];
            j++;
        }
        k++;
    }
    // copio il resto di a[] in b[]
    while(i<na) {
      b[k] = a[i];
      i++;
      k++;
    }
    // copio il resto di c[] in b[]
    while(j<nc) {
        b[k] = c[j];
        j++;
        k++;
    }
      assert(i==na);
      assert(j==nc);
      assert(k==na+nc); 
}