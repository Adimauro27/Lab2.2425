/* 
mia implementazione del paradigma lettori scrittori utlizzo 

    il buffer condiviso deve essere di dimensione variabile
    se il programa compialto con compilazione condizionale
        quando chiamo make lettori -MANZA mi fa la versione con BUFFER che fissato a 1000
        se chiamo senza -MANZA il buffer è dinamico ed è grosso argv[1]

    devo usare due lock una per (dati) e una per (ordering)
    
    
*/

// devo includere le librerie che si trovano in "xerrori.h"
#include "xerrori.h"
#define QUI __LINE__,__FILE__

// definisco la dimensione del buffer
// che deve essere statico se manza
#ifdef MANZA
//lo faccio statico
#define Buf_size 100
#else
// lo faccio dinamico

static int Buf_size;

#endif


// FUNZIONI CHE USERO DOPO
void *pbody(void *args);
void *cbody(void *args);
bool primo(int n);


//qui devo differenziare le strutture dati

// per i consumatori
//     cons leggono dal buffer e verificano primo
typedef struct{
    // cosa mi serve?
    int *buffer; // da dove devo leggere l'intero
    int quanti; // output

    int *pcindex;
    int *pdati;
    
    pthread_mutex_t *mutex;
    pthread_mutex_t *ordering;
    pthread_cond_t *empty;
    pthread_cond_t *full;
}consumatori;

// per i produttori
typedef struct{
    // cosa mi serve?
    int *buffer;
    int n; // intero generato casualmente
    int numeri; // quanti numeri deve generare

    int *ppindex;
    int *pdati;

    pthread_mutex_t *mutex;
    pthread_mutex_t *ordering;
    pthread_cond_t *empty;
    pthread_cond_t *full;
}produttori;



int main(int argc , char *argv[]){

    // uso : fair_mia 
    // leggi input

    #ifdef MANZA

    // qui statico
    if(argc<3){
        printf("Uso\n\t%s lettori scrittori\n", argv[0]);
        exit(1);
    }
    int tc = atoi(argv[1]);
    int tp = atoi(argv[2]);
    #else
    // uso : fair_mia size
    // leggi input

    if(argc<4){
        printf("Uso\n\t%s lettori scrittori buffer_size\n", argv[0]);
        exit(1);
    }
    Buf_size = atoi(argv[3]);
    int tc = atoi(argv[1]);
    int tp = atoi(argv[2]);
    #endif

    int primi = 0;

    //buffer produttori consumatori
    int buffer[Buf_size];
    int pindex=0, cindex=0, dati=0;
    pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
    pthread_cond_t full = PTHREAD_COND_INITIALIZER;
  
    // dati per i thread
    produttori ap[tp];
    consumatori ac[tc];
    pthread_t prod[tp];       // id thread produttori
    pthread_t cons[tc];       // id thread consumatori 
    
    // creo tutti i consumatori
    for(int i = 0; i<tc;i++){
        ac[i].pcindex = &cindex;
        ac[i].pdati = &dati;
        ac[i].buffer = buffer;
        ac[i].mutex = &mu;
        ac[i].empty = &empty;
        ac[i].full = &full;
        xpthread_create(&cons[i], NULL, &cbody, &ac[i],QUI);
    }
    fprintf(stderr,"Thread consumatori creati");
  // creo tutti i produttori
  for(int i=0;i<tp;i++) {
    ap[i].ppindex = &pindex;
    ap[i].pdati = &dati;
    ap[i].buffer = buffer;
    ap[i].mutex = &mu;
    ap[i].empty = &empty;
    ap[i].full = &full;
    xpthread_create(&prod[i], NULL, &pbody, &ap[i],QUI);     
  }

  // attendo i produttori
  for(int i=0;i<tp;i++) 
    pthread_join(prod[i],NULL);

  // comunico ai consumatori che possono terminare
  for(int i=0;i<tc;i++) {
    xpthread_mutex_lock(&mu,QUI);
    while(dati==Buf_size) {
      xpthread_cond_wait(&full,&mu,QUI);
    }
    buffer[pindex % Buf_size] = -1;
    pindex += 1;
    dati += 1;
    xpthread_cond_signal(&empty,QUI);
    xpthread_mutex_unlock(&mu,QUI);
  }
  // attendo i consumatori 
  for(int i=0;i<tc;i++) {
    pthread_join(cons[i],NULL);
    primi += ac[i].quanti;
  }
  // deallocazione, saluti, etc....
  xpthread_mutex_destroy(&mu,QUI);
  xpthread_cond_destroy(&empty,QUI);
  xpthread_cond_destroy(&full,QUI);
  fprintf(stderr,"Trovati %d primi con somma\n",primi);
  return 0;
}

//funzione eseguita dai thread producer
void *pbody(void *args){
    // devo prendere i paramentri
    produttori *dati = (produttori*)(args);

    fprintf(stderr,"[C] produttore partito\n");
    int loop = dati->numeri;
    do {
        //prendo il lock
        xpthread_mutex_lock(dati->ordering,QUI);
        xpthread_mutex_lock(dati->mutex,QUI);
        
        int n = rand() % 10000; // genero il numero randomico
        while(*(dati->pdati)==Buf_size) {
            // attende fino a quando il buffer rimane pieno 
            xpthread_cond_wait(dati->full,dati->mutex,QUI);
        }

        // infilo il numero nel buffer
        dati->buffer[*(dati->ppindex) % Buf_size] = n;
        *(dati->ppindex) += 1;
        *(dati->pdati) += 1;

        // segnala che il buffer non e' piu' pieno
        xpthread_cond_signal(dati->empty,QUI);
        xpthread_mutex_unlock(dati->mutex,QUI);
        xpthread_mutex_unlock(dati->ordering,QUI);

        loop--;
    }while(loop);
    fprintf(stderr,"[C] produttore terminato\n");
    pthread_exit(NULL);
}

// funzione eseguita dai thread consumer
void *cbody(void *args){
    consumatori *dati = (consumatori*)(args);
    dati->quanti = 0;

    int n;
    do
    {
        // prendo il lock
        xpthread_mutex_lock(dati->ordering,QUI);
        xpthread_mutex_lock(dati->mutex,QUI);
        while(*(dati->pdati)==0) {
            // attende fino a quando il buffer è vuoto
            xpthread_cond_wait(dati->empty,dati->mutex,QUI);
        }
        
        //prendo i dati dal buffer
        n = dati->buffer[*(dati->pcindex) % Buf_size];
        *(dati->pcindex) += 1;
        *(dati->pdati) -=1;

        // verifico se il numero e' primo

        if(primo(n)) dati->quanti++;

    } while (n!=-1);

    pthread_exit(NULL);

}



// funzione per stabilire se n e' primo  
bool primo(int n)
{
  if(n<2) return false;
  if(n%2==0) return (n==2);
  for (int i=3; i*i<=n; i += 2)
  if(n%i==0) return false;
  return true;
}