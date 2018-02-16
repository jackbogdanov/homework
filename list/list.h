#ifndef LIST
#define LIST
#pragma once
#include <glob.h>
#include <malloc.h>


typedef struct node {
    struct node * next;
    int value;
} Node;

typedef struct linkedList {
    size_t length;
    struct node * head;
    struct node * end;
} LinkedList;

LinkedList * createList();

Node * createNode(int value);

int insertIntoBeginning(LinkedList * list, int value);

int insertIntoEnd(LinkedList * list, int value);

int insertAfter(LinkedList * list, int value, int after);

int deleteByValue(LinkedList * list, int value);

void clearList(LinkedList * list);

void printList(LinkedList * list);
#endif




