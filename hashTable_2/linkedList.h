#ifndef LIST
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

LinkedList * createList() {
    struct linkedList * list = calloc(sizeof(LinkedList), 1);
    if (list) {
        list->length = 0;
        list->head = NULL;
        list->end = NULL;
        return list;
    } else {
        printf("Error while creating List");
        return NULL;
    }

};

Node * createNode(char * key, int value) {
    Node * node = calloc(sizeof(Node), 1);


    if (node) {
        node->value = value;
        node->next = NULL;
        node->key = key;
        return node;
    } else {
        printf("Error while creating Node");
        return NULL;
    }
}

int insertIntoBeginning(LinkedList * list, char * key, int value) {
    Node * node = createNode(key, value);

    if (node) {
        node->next = list->head;
        list->head = node;
        if (!list->end) {
            list->end = node;
        }
        list->length += 1;
        return 1;
    } else {
        return 0;
    }

}

int insertIntoEnd(LinkedList * list, char * key, int value) {

    if (list->length){
        Node * node = createNode(key, value);
        if (node) {
            list->end->next = node;
            list->end = node;
            list->length += 1;
            return 1;
        } else {
            return 0;
        }

    } else {
        return insertIntoBeginning(list, key, value);
    }




}

int insertAfter(LinkedList * list, int value, char * key) {
    Node * node = createNode(key, value);
    Node * pointer = list->head;

    while (pointer) {
        if (pointer->key == key) {
            node->next = pointer->next;
            pointer->next = node;
            return 1;
        } else {
            pointer = pointer->next;
        }
    }

    printf("Элемент не найден:(\n");
    return 0;
}

int deleteByValue(LinkedList * list, int value) {
    Node * pointer = list->head;
    int returnCode = 0;

    while (pointer) {

        while (pointer->next && pointer->next->value == value) {
            Node * newNext = pointer->next->next;
            free(pointer->next);
            pointer->next = newNext;
            list->length -= 1;
            returnCode += 1;
        }

        pointer = pointer->next;
    }

    pointer = list->head;
    if (pointer->value == value) {
        list->head = pointer->next;
        free(pointer);
        list->length -= 1;
        returnCode += 1;
    }



    if (!returnCode) {
        printf("Элемент не найден!");
    }

    return returnCode;
}

void clearList(LinkedList * list) {
    Node * pointer = list->head;
    Node * container;

    while (pointer) {
        container = pointer->next;
        free(pointer);
        pointer = container;
    }

    free(list);
}

void printList(LinkedList * list) {
    Node * pointer = list->head;
    int i = 1;

    while (pointer) {
        printf("№ %d; value - %d;\n",i ,pointer->value);
        ++i;
        pointer = pointer->next;
    }
}
#endif


