#include <stdio.h>
#include <time.h>
#include "hashTable.h"
#define HASH_TABLE_SIZE 10
#define BUFFER_SIZE 20

int symbolCheck(char ch) {

    char * unwantedSymbols = ".!,\"_-+?#:;()*";
    int len = (int) strlen(unwantedSymbols);

    for (int i = 0; i < len; ++i) {
        if (ch == unwantedSymbols[i]) {
            return 1;
        }
    }

    if (ch >= '1' && ch <= '9') {
        return 1;
    }

    return 0;
}

void cleanWord(char * word) {


    int i = 0;

    while (word[i]) {
        if (symbolCheck(word[i])) {
            for (int j = i; j < strlen(word); ++j) {
                word[j] = word[j+1];
            }
            --i;
        }
        ++i;
    }

}

char * rewrite(char * buff, char * word) {
    int len = (int) strlen(word);
    int i = 0;

    while (len < BUFFER_SIZE && i - BUFFER_SIZE) {
        buff[i] = word[i];
        ++i;
    }
    buff[i] = '\0';

    return buff;
}

void parseFile(HashTable * hashTable, char * nameOfFile) {

//    FILE * file = fopen("/home/jack/testHome/myW.txt", "r");
    FILE * file = fopen(nameOfFile, "r");

    char * word = calloc(BUFFER_SIZE, sizeof(char));

    while (!feof(file)) {

        char *buff = calloc(BUFFER_SIZE, sizeof(char)) ;

        fscanf(file, "%s", word);

        cleanWord(word);
        rewrite(buff, word);


        if (strlen(buff) && !feof(file)) {
            add(hashTable, buff);
        }
    }


    fclose(file);
}

int main() {

    HashTable * hashTable = createHashTable(HASH_TABLE_SIZE, hashFunction);
    clock_t start, end;


    start = clock();
    parseFile(hashTable, "/home/jack/testHome/Кровь эльфов. Анджей Сапковский.txt");
    printStats(hashTable);
    end = clock();
    printf("Время выполнения пограммы: %f\n", (float) (end - start)/CLOCKS_PER_SEC);

    clearTable(hashTable);
    return 0;
}
