#include <stdio.h>
#include <memory.h>

int main() {
    FILE *file = fopen("/home/evgenij/test.txt", "r");
    char str[255];

    while (fgets(str, 255, file)){

        int i = 0;

        while (i < strlen(str)- 1){
            if (str[i] == '/' && str[i + 1] == '/'){
                while (str[i] != '\n'){
                    printf("%c", str[i]);
                    i ++;
                }
                printf("\n");
            }
            i++;
        }
    }

    fclose(file);

    return 0;
}