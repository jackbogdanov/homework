#include <stdio.h>
#include <memory.h>

int main() {
    int b1[] = {1, 0, 1};
    int b2[] = { 0, 1};

    int sizeB1 = sizeof(b1)/ sizeof(int);
    int sizeB2 = sizeof(b2)/ sizeof(int);

    if (sizeB1 == sizeB2){
        int i = 0;
        while (i < sizeB1 && b1[i] == b2[i]){
            i++;
        }

        if (i != sizeB1){
            if (b1[i]){
                printf("b1 > b2");
            } else{
                printf("b2 > b1");
            }
        } else{
            printf("b2 = b1");
        }


    } else{
        if (sizeB1 > sizeB2){
            printf("b1 > b2");
        } else {
            printf("b2 > b1");
        }
    }

    return 0;
}