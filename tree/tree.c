#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>


typedef struct node{

    int value;
    int frequency;

    int p;
    int q;

    struct node * right;
    struct node * left;
} Node;



Node * createNode(int value, int frequency) {
    Node * node = calloc(sizeof(Node), 1);

    if (node != NULL) {
        node->value = value;
        node->frequency = frequency;

        node->right = NULL;
        node->left = NULL;

        node->p = 0;
        node->q = 0;
    } else {
        printf("Не удалось создать узел!");
    }

    return node;
}

void parseFile(Node *nodes[], char * nameOfFile) {
    FILE * file = fopen(nameOfFile, "r");

    int value = 0;
    int frequency = 0;
    Node * node = NULL;

    int i = 0;

    if (file != NULL) {

        while (!feof(file)) {
            fscanf(file, "число %d - количество запросов %d\n", &value, &frequency);

            node = createNode(value, frequency);
            nodes[i] = node;
            i++;
        }


    } else {
        printf("Не удалось открыть файл!");
    }

    fclose(file);
}

void swap(Node ** a, Node ** b) {
    Node * p = *a;
    *a = *b;
    *b = p;
}


void qSortByValue(Node * nodes[], int begin, int end) {
    int left = begin;
    int right = end;
    Node * midElement = nodes[(begin + end)/2];

    while (left <=right) {

        while (nodes[left]->value < midElement->value) {
            left++;
        }

        while (nodes[right]->value > midElement->value) {
            right--;
        }

        if (left <= right) {
            swap(&nodes[left++], &nodes[right--]);
        }
    }

    if (begin < right) {
        qSortByValue(nodes,begin, right);
    }

    if (end > left) {
        qSortByValue(nodes,left, end);
    }
}

void printNodes(Node * nodes[], int len) {

    printf("--------------Вывод--------------\n");

    for (int i = 0; i < len; ++i) {
        printf("Узел - %d, значение - % d, частота - %d\n", i, nodes[i]->value, nodes[i]->frequency);
    }

    printf("---------------------------------\n");
    printf("\n");
}

void countIntegralFr(Node * nodes[], int len) {
    int p = 0;

    for (int i = 0; i < len; ++i) {
        nodes[i]->p = p;
        p += nodes[i]->frequency;
    }

}

void countQFunk(Node * nodes[], int len) {

    if (len >= 3) {
        nodes[0]->q = 0 + nodes[2]->p;

        for (int i = 1; i < len - 1; ++i) {
            nodes[i]->q = nodes[i]->p + nodes[i + 1]->p;
        }

        nodes[len - 1]->q = 2*nodes[len - 1]->p + nodes[len - 1]->frequency;
    }

}

Node * buildTree(Node * nodes[], int begin, int end) {
    Node * minNode = NULL;

    if (!(begin >= end || end < 0)) {

        int fun = 0, i = 0, m = 0;
        int minFun = INT_MAX;

        while (i <= end) {
            fun = abs(nodes[i]->q - (nodes[begin]->p + nodes[end]->p));
            if (minFun > fun) {
                minFun = fun;
                minNode = nodes[i];
                m = i;
            }
            ++i;
        }


        if (begin == end) {
            minNode->left = NULL;
            minNode->right = NULL;
        }
        else if (m == end) {
            minNode->left = buildTree(nodes, 0, m - 1);
            minNode->right = NULL;
        }
        else if (m == begin) {
            minNode->right = buildTree(nodes, m + 1, end);
            minNode->left = NULL;
        }
        else {
            minNode->left = buildTree(nodes, 0, m - 1);
            minNode->right = buildTree(nodes, m + 1, end);
        }


//            minNode->left = buildTree(nodes, 0, m - 1);
//        minNode->right = buildTree(nodes, m + 1, end);
    } else {
        minNode = nodes[begin];
    }


    return minNode;
}

void printTreeInFile(Node * node, FILE * file) {

    if (node->left != NULL) {
        fprintf(file, "\"%d\\n%d\" -> \"%d\\n%d\";\n", node->value, node->frequency,
                node->left->value, node->left->frequency);
        printTreeInFile(node->left, file);
    }

    if (node->right != NULL) {
        fprintf(file, "\"%d\\n%d\" -> \"%d\\n%d\";\n", node->value, node->frequency,
                node->right->value, node->right->frequency);
        printTreeInFile(node->right, file);
    }



}

void printTree(Node * node, int level) {

    if (node != NULL) {
        printf("level - %d, значение - %d\n", level, node->value);
        printTree(node->left, level + 1);
        printTree(node->right, level + 1);
    }
}

int main() {
    int numOfNodes = 5;

    Node * nodes[numOfNodes];

    int len = sizeof(nodes)/ sizeof(nodes[0]);

    parseFile(nodes, "/home/jack/инфа/optimalTree/inform.txt");

    printNodes(nodes, len);
    qSortByValue(nodes, 0, len - 1);
    printNodes(nodes, len);

    countIntegralFr(nodes, len);
    countQFunk(nodes, len);

    FILE * file = fopen("/home/jack/инфа/optimalTree/out.dot", "w");

    if (file != NULL) {
        fprintf(file, "digraph {\n");
        printTreeInFile(buildTree(nodes, 0, len - 1), file);
        fprintf(file, "}\n");
    } else {
        printf("Ошибка во время открытия файла!");
    }


    fclose(file);

    return 0;
}
