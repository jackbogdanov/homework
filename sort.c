#include <stdio.h>
#include <time.h>

typedef void (*function)(int , int *);
#define MAS_SIZE 100000000
#define MAX_NUMBER_OF_COMMAND 5
#define SORTS_COUNT 4
#define MAX_VALUE 51

void print(int length, int * mas);

void swap(int * a, int * b) {
    int k = *a;
    *a = *b;
    *b = k;
}


void qsort(int begin, int end, int * mas) {
    int left = begin;
    int right = end;
    int midElement = mas[(left + right)/2];

    while (left <= right) {

        while (mas[left] < midElement) {
            left++;
        }
        while (mas[right] > midElement) {
            right--;
        }

        if (left <= right) {
            swap(&mas[left++], &mas[right--]);
        }
    }



    if (begin < right) {
        qsort(begin, right, mas);
    }

    if (end > left) {
        qsort(left, end, mas);
    }
}

void qsortWrapper(int length, int * mas) {

    int left = 0, right = length - 1;
    qsort(left, right, mas);

}


void slowSort(int length, int * mas) {
    int flag = 0;

    for (int i = 0; i < length; ++i) {
        flag = 1;
        for (int j = i; j < length; ++j) {

            if (mas[i] > mas[j]) {
                swap(&mas[i], &mas[j]);
                flag = 0;
            }

        }

        if (flag){
            break;
        }
    }


}

//считаю, что числа варьируются от 0 до 50
void countSort(int length, int * mas) {
    int countMas[MAX_VALUE] = {0};
    int i = 0;

    while(length - i) {
        countMas[mas[i]]++;
        i++;
    }

    int mainIndex = 0;

    for (int j = 0; j < MAX_VALUE - 11
            ; ++j) {
        while (countMas[j]--) {
            mas[mainIndex] = j;
            mainIndex++;
        }
    }
}

void parse(int length, int * mas) {

    FILE *f = fopen("/home/jack/testHome/sort.txt", "r");

    if (f != NULL) {
        int i = 0, num = 0;

        while (fscanf(f, "%d", &num) > 0 && i < length) {
            mas[i] = num;
            ++i;
        }

        while (i < length) {
            mas[i] = 0;
            ++i;
        }

    } else {
        printf("FILE ERROR!");
    }

    fclose(f);
}

void print(int length, int * mas) {

    int i = 0;
    while (length - i) {
        printf("%d ", mas[i]);
        if (!((i + 1) % 100)) {
            printf("\n");
        }
        ++i;
    }

    printf("\n");
}

int mas[MILLION];

void printMenu() {
    printf("0 - exit\n");
    printf("1 - countSort\n");
    printf("2 - slowSort\n");
    printf("3 - qsort\n");
    printf("4 - print\n");
    printf("5 - read file again\n");
}

int main() {

    clock_t start, end;

    int length = 0, k = -1;

    function methods[] = {
            countSort,
            slowSort,
            qsortWrapper,
            print,
            parse
    };

    //printf("Введите длинну массива: \n");
    //scanf("%d", &length);
    length = MILLION;
    parse(length, mas);

    while (1) {
        printMenu();
        scanf("%d", &k);

        if (k < 0 || k > MAX_NUMBER_OF_COMMAND) {
            printf("WRONG INSTRUCTION NUMBER!!");
        } else {
            if (!k) {
                break;
            } else {
                start = clock();
                methods[k - 1](length, mas);
                end = clock();
                if (k > 0 && k < SORTS_COUNT) {
                    printf("Время выполнения сортировки: %f\n", (float) (end - start)/CLOCKS_PER_SEC);
                }
            }
        }
    }

    return 0;
}
