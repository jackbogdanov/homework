#include <stdio.h>
#include <memory.h>

#define MAX_STRING 255

int main() {

    char str[MAX_STRING];

    char ch;
    scanf("%s \n", str);
    scanf("%c", &ch);

    char clearStr[MAX_STRING] = {0};

    int i = 0, j = 0;
    int len = (int) strlen(str);

    while (i < len){
        if (str[i] != ch){
            clearStr[j] = str[i];
            j++;
        }
        i++;
    }

    printf("%s \n", clearStr);
    return 0;
}
