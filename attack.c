#include <stdio.h>


void secretFun(){
    printf("Surprise!!!\n");
}

void fun(){
    char buffer[20];
    printf("Enter your message:\n");

    scanf("%s", buffer);

    printf("Your entered %s\n", buffer);
}



int main() {
    printf("%p\n", secretFun);
    fun();
    return 0;
}
