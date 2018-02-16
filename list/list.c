#include <glob.h>
#include <malloc.h>
#include "list.h"

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

Node * createNode(int value) {
    Node * node = calloc(sizeof(Node), 1);
    if (node) {
        node->value = value;
        node->next = NULL;
        return node;
    } else {
        printf("Error while creating Node");
        return NULL;
    }
}

int insertIntoBeginning(LinkedList * list, int value) {
    Node * node = createNode(value);

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

int insertIntoEnd(LinkedList * list, int value) {
    Node * node = createNode(value);
    if (node) {

        if (list->length){
            list->end->next = node;
            list->end = node;
            list->length += 1;
            return 1;
        } else {
            return insertIntoBeginning(list, value);
        }

    } else {
        return 0;
    }
}

int insertAfter(LinkedList * list, int value, int after) {
    Node * node = createNode(value);
    Node * pointer = list->head;

    while (pointer) {
        if (pointer->value == after) {
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





