#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    srand(time(NULL));

    FILE * f = fopen("/home/jack/testHome/sort.txt", "w");
    int i = 100000000;
    //scanf("%d", &i);

    while (i){
        fprintf(f, "%d ", 0 + rand() % 50);
        --i;
    }

    fclose(f);
    return 0;
}
