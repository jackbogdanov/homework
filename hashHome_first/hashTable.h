#ifndef HASH_1
#pragma once

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "liblist.h"

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

int max(int a, int b);
int min(int a, int b);

int multiplier(int i);

int hashFunction(char * string, int size);

HashTable * createHashTable(int size, hashFunc func);

void clearTable(HashTable * hashTable);

void insert(HashTable * hashTable, char * key, int value);

Node * get(HashTable * hashTable, char * key);

void iterate(HashTable * hashTable, iterator fun);

void printNode(char * key, int value);

void printStats(HashTable * hashTable);
#endif
