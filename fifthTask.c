#include <stdio.h>
#include <memory.h>

int main() {

    FILE *file1 = fopen("test.txt", "r");
    FILE *file2 = fopen("test.txt", "r");
    char str1[255], str2[255];

    while (fgets(str1, 255, file1)){
        int flag = 0;
        while (fgets(str2, 255, file2)){
            printf("%s %s %d\n", str1, str2, strcmp(str1, str2));

            if (!strcmp(str1, str2)){
                flag++;
            }
        }

        if (flag == 1){
            printf(" %s", str1);
            break;
        } else {
            fclose(file2);
            file2 = fopen("test.txt", "r");
        }
    }

    fclose(file1);
    fclose(file2);
    return 0;
}