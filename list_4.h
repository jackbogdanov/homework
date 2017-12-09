#ifndef LIST_4
#pragma once

#define COMMANDS_NUMBER 4
#define INSERT_BY_VALUE 5
#define PRINT 6
#define REVERT 7
#define IS_LOOPED 8


typedef struct node {
    struct node * next;
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

typedef int (*func)(LinkedList *, int);

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

int menuConsol() {
    int k = 0;
    printf("0 - выход\n");
    printf("1 - вставка в начало\n");
    printf("2 - вставка в конец\n");
    printf("3 - удаление по значению\n");
    printf("4 - создать петлю\n");
    printf("5 - вставка позначению\n");
    printf("6 - печать\n");
    printf("7 - развернуть список\n");
    printf("8 - проверить на цикл\n");

    printf("Выберите действие: \n");

    scanf("%d", &k);

    return k;
}


void revert(LinkedList * list) {
    Node * container;
    Node * previousNode = list->head;
    Node * pointer = previousNode->next;

    previousNode->next = NULL;

    list->end = previousNode;


    while (pointer){
        container = pointer->next;
        pointer->next = previousNode;
        previousNode = pointer;
        pointer = container;
    }

    list->head = previousNode;
}

int createLoop(LinkedList * list, int position) {

    if (list->length > position) {
        int i = 1;
        Node * node = list->head;

        while (i-position){
            node = node->next;
            ++i;
        }

        list->end->next = node;

        return 1;
    } else {
        return 0;
    }

}

int isLooped(LinkedList * list) {
    Node * p1 = list->head;
    Node * p2 = list->head->next;

    while (p1 != p2 && (p1 == NULL || p2->next == NULL) ) {
        
        p1 = p1->next;
        p2 = p2->next->next;
    }

    if (p1 == p2) {
        printf("Есть цикл!\n");
        return 1;
    } else {
        printf("OK\n");
        return 0;
    }
}

void menu() {
    LinkedList * list = createList();
    func methods[COMMANDS_NUMBER] = {
            insertIntoBeginning,
            insertIntoEnd,
            deleteByValue,
            createLoop
    };

    int k = 0, value = 0, after = 0;

    while (k = menuConsol()) {

        if (k == IS_LOOPED) {
            isLooped(list);
        } else {
            if (k == PRINT || k == REVERT){

                if (k == REVERT){
                    revert(list);
                    printf("Развернутый список: \n");
                }
                printList(list);

            } else {
                printf("Введите занчения узла\n");
                scanf("%d", &value);

                if (k <= COMMANDS_NUMBER){
                    methods[k - 1](list, value);
                } else {
                    if (k == INSERT_BY_VALUE) {
                        printf("Введите значение после которого необходимо вставить узел\n");
                        scanf("%d", &after);
                        insertAfter(list, value, after);
                    }
                }
            }
        }

        printf("\n");
    }

    clearList(list);
}

#endif
