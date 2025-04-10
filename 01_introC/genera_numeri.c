#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//uso : genera_numeri 10



int main(int argc, char* argv[]) {
    srand(time(NULL)); 

    if(argc < 2) exit(1);
    int cifra = atoi(argv[1]);

    FILE *file = fopen("numeri1.txt", "w");
    if (file == NULL) {
        perror("Errore nell'aprire il file");
        return 1;
    }

    for (int i = 0; i <= cifra; i++) {
        if (i != 13 && i != 17 && i != 49) {
            fprintf(file, "%d\n", rand()%10);
        }
    }

    fclose(file);
    return 0;
}
