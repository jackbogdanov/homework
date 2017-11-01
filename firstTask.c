#include <stdio.h>
#include <memory.h>

int main() {
    char str[255];
    char ch;
    scanf("%s \n", str);
    scanf("%c", &ch);

    char clearStr[255] = "1";

    int i = 0, j = 0;


    while (i < strlen(str)){
        if (str[i] != ch){
            clearStr[j] = str[i];
            j++;
        }
        i++;
    }

    printf("%s \n", clearStr);
    return 0;
}