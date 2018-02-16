#include <stdio.h>
#include <memory.h>

int main() {

    FILE *file1 = fopen("test.txt", "r");
    FILE *file2 = fopen("test.txt", "r");

    if (file1 != NULL && file2 != NULL) {

        char str1[255], str2[255];

        while (fgets(str1, 255, file1)) {
            int flag = 0;
            
            while (fgets(str2, 255, file2)) {
                int res = strcmp(str1, str2);
                
                printf("%s %s %d\n", str1, str2, res);

                if (!res) {
                    flag++;
                }
            }

            if (flag == 1) {
                printf(" %s", str1);
                break;
            } else {
                fclose(file2);
                file2 = fopen("test.txt", "r");
            }
        }

        fclose(file1);
        fclose(file2);
    } else {
        printf("Не удалось открыть файл:(");
    }


    return 0;
}
