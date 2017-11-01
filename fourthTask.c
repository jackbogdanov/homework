#include <stdio.h>
#include <memory.h>

int main() {

    int squareSum = 0, sum = 0;
    for (int i = 1; i < 101; ++i) {
        squareSum += i*i;
        sum += i;
    }

    printf("%d \n", sum*sum - squareSum);
    return 0;
}