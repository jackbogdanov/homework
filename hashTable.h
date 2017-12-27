#ifndef HASH_1
#pragma once

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "linkedList.h"

#define HASH_TABLE_SIZE 10

typedef int (*hashFunc)(char *, int);
typedef void (*iterator)(char *, int);

typedef struct table {
    LinkedList * list;
} Table[HASH_TABLE_SIZE];

typedef struct hashTable {
    hashFunc hash;
    int size;
    Table * table;
} HashTable;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int multiplier(int i) {

    int k = 7, result = 1;

    while (i) {
        result = result*k;
        --i;
    }

    return result;
}

int hashFunction(char * string, int size) {

    int lengthString = (int) strlen(string);
    int result = 0;

    for (int i = 0; i < lengthString; ++i) {
        result += (((int) string[i])*multiplier(i)) % size;
    }

    if (result < 0) {
        result = -result;
    }
    return result % size;
}


HashTable * createHashTable(int size, hashFunc func) {
    Table * table = calloc(sizeof(Table)*size, 1);
    HashTable * hashTable = calloc(sizeof(HashTable), 1);

    LinkedList * list;

    if (table && hashTable) {
        int i = 0;

        while (size - i){
            list = createList();

            table[i]->list = list;

            ++i;
        }

        hashTable->table = table;
        hashTable->size = size;
        hashTable->hash = func;

        return hashTable;
    } else {
        return NULL;
    }

}


void clearTable(HashTable * hashTable) {
    Table * table = hashTable->table;

    LinkedList * list;

    int size = hashTable->size;

    for (int i = 0; i < size; ++i) {
        clearList(table[i]->list);
    }

    free(table);
    free(hashTable);
}

void add(HashTable * hashTable, char * str) {
    Table * table = hashTable->table;
    LinkedList * list = table[hashTable->hash(str, hashTable->size)]->list;
    Node * pointer = list->head;


    while (pointer && strcmp(pointer->key, str)) {
        pointer = pointer->next;
    }

    if (pointer != NULL) {
        pointer->value += 1;
    } else {
        insertIntoEnd(list, str, 1);
    }
}

void insert(HashTable * hashTable, char * key, int value) {
    Table * table = hashTable->table;

    LinkedList * list = table[hashTable->hash(key, hashTable->size)]->list;
    Node * pointer = list->head;


    while (pointer && strcmp(pointer->key, key)) {
        pointer = pointer->next;
    }

    if (pointer) {
        pointer->value = value;
    } else {
        insertIntoEnd(list, key, value);
    }


}

Node * get(HashTable * hashTable, char * key) {

    Table * table = hashTable->table;

    LinkedList * list = table[hashTable->hash(key, hashTable->size)]->list;
    Node * pointer = list->head;


    while (pointer && strcmp(pointer->key, key)) {
        pointer = pointer->next;
    }

    if (pointer) {
        return pointer;
    } else {
        printf("Элемент с колючём '%s' не найден!\n", key);
        return NULL;
    }

}

void iterate(HashTable * hashTable, iterator fun) {
    Table * table = hashTable->table;
    LinkedList * list;
    Node * pointer;

    for (int i = 0; i < hashTable->size; ++i) {
        list = table[i]->list;
        pointer = list->head;

        for (int j = 0; j < list->length; ++j) {
            fun(pointer->key, pointer->value);
            pointer = pointer->next;
        }
    }


}


void printNode(char * key, int value) {
    printf("ключ: %s; значение - %d\n", key, value);
}

void printStats(HashTable * hashTable) {
    Table * table = hashTable->table;
    LinkedList * list;
    Node * pointer;

    Node * mostCommonWord = createNode("rootNode", -1);

    int maxListLength = 0;
    int minListLength = hashTable->size + 1;

    int wordsCount = 0;
    int unicWordsCount = 0;


    for (int i = 0; i < hashTable->size; ++i) {
        list = table[i]->list;
        pointer = list->head;

        unicWordsCount += list->length;
        maxListLength = max (maxListLength, (int) list->length);
        minListLength = min (minListLength, (int) list->length);



        for (int j = 0; j < list->length; ++j) {
            wordsCount += pointer->value;

            if (mostCommonWord->value < pointer->value) {
                mostCommonWord = pointer;
            }
            pointer = pointer->next;
        }
    }

    printf("------stats------\n");
    printf("Самое частое слово - %s\n", mostCommonWord->key);
    printf("Mаксимальная длинна листа - %d\n", maxListLength);
    printf("Mинимальная длинна листа - %d\n", minListLength);
    printf("Всего слов - %d\n", wordsCount);
    printf("Уникальных слов - %d\n", unicWordsCount);
    printf("Срелняя часота слова - %f\n", (float ) wordsCount/unicWordsCount);
    printf("-----------------\n");

    free(mostCommonWord->key);
    free(mostCommonWord);
}

#endif

