#ifndef LIST
#define LIST
#pragma once

#include <printf.h>
#include <malloc.h>

typedef struct node {
    struct node * next;
    char * key;
    int value;
} Node;

typedef struct linkedList {
    size_t length;
    struct node * head;
    struct node * end;
} LinkedList;

LinkedList * createList();

Node * createNode(char * key, int value);

int insertIntoBeginning(LinkedList * list, char * key, int value);

int insertIntoEnd(LinkedList * list, char * key, int value);

int insertAfter(LinkedList * list, int value, char * key);

int deleteByValue(LinkedList * list, int value);

void clearList(LinkedList * list);

void printList(LinkedList * list);
#endif


