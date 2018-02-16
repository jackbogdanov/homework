#include <stdio.h>
#include <memory.h>

int main() {
    FILE *file = fopen("/home/evgenij/test.txt", "r");
    char str[255];

    if (file != NULL) {
        while (fgets(str, 255, file)) {

            int i = 0;
            int len = (int) strlen(str);

            while (i < len- 1) {
                if (str[i] == '/' && str[i + 1] == '/') {
                    while (str[i] != '\n') {
                        printf("%c", str[i]);
                        i ++;
                    }
                    printf("\n");
                }
                i++;
            }
        }

        fclose(file);

    } else {
        printf("Не удалось открыть файл:(");
    }
    
    return 0;
}
