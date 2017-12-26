#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define NUM_OF_COMMANDS 3

struct descriptionStruct {
    char *str;
    void (*function)(float x);
} description[NUM_OF_COMMANDS];



void initDesc(char *str, void (*function)(float x), int num) { 
    description[num].str = str;
    description[num].function = function;
}

void printDescription(struct descriptionStruct str[], int sizeStruckt)
{
    for (int i = 0; i < sizeStruckt; i++) {
        printf("Способ №%d: %s\n", i + 1, str[i].str);
    }

}

void mantissaPrint(int mantissa) {
    char str[24] = "";
    union {
        int mantissa:23;
        short bit:1;
    } bitField;
    bitField.mantissa = mantissa;

    int n = 23, i = 0;
    while (bitField.mantissa << i + 9 && i < 23) {
        bitField.mantissa = bitField.mantissa >> n - (i + 1);
        str[i] = (char) (abs(bitField.bit) + '0') ;
        bitField.mantissa = mantissa;
        i++;
    }
    str[i] = 0;

    if (strlen(str))printf(".%s\n", str);
}

void printResult(int sign, int order, int mantissa) {
    printf("    %d   %d\n", sign, order - 127);
    printf("(-1) * 2 * 1");
    mantissaPrint(mantissa);
}


void funkOne(float x) {
    union {
        float num;
        int intNum;
        int sign:1;
        int order:8;
        int mantissa:23;
    } field;

    field.num = x;

    int mantissa = field.mantissa;
    field.intNum = field.intNum >> 23;
    int order = field.order;
    field.intNum = field.intNum >> 8;
    int sign = abs(field.sign);

    printResult(sign, order, mantissa);
}


void funkTwo(float x) {
    union {
        float num;
        int intNum;
    } field;

    field.num = x;

    int mantissa = field.intNum & 0x007fffff;
    int order = (field.intNum & 0x7f000000) >> 23;
    int sign = abs((field.intNum & 0x80000000) >> 31);

    printResult(sign, order, mantissa);
}

void funkThree(float x) {
    int *px = (int*) &x;
    int intX = *px;


    int mantissa = intX & 0x007fffff;
    int order = (intX & 0x7f000000) >> 23;
    int sign = abs((intX & 0x80000000) >> 31);
    printResult(sign, order, mantissa);
}

int main() {
    if (sizeof(float) == 4) {
        int sizeStruckt = sizeof(description)/ sizeof(description[0]);
        initDesc("Вывести float при помощи Union с int", funkOne, 0);
        initDesc("Вывести float при помощи  union со структурой с bit fields", funkTwo, 1);
        initDesc("Вывести float при помощи взятие адреса и разыменование указателя", funkThree, 2);
        printDescription(description, sizeStruckt);
        printf("Выберите способ обработки и введите два числа типа float:\n");

        int num;
        float x, y = 1;
        scanf("%d %f %f",&num, &x, &y);
        if (y) {
            printf("%f\n", x / y);
            description[num - 1].function(x / y);
        } else {
            if (x) {
                if (x > 0){
                    printf("+Inf");
                } else {
                    printf("-Inf");
                }
            } else {
                printf("NaN");
            }

        }
    } else {
        printf("ERROR: floatSize != 4");
    }

    return 0;
}
