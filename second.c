//# include <stdlib.h>
#include <string.h>
# include <stdio.h>

int myStrlen(char *str){
	int i = 0, len = 0;

	while (str[i] != '\0'){
		len++;
		i++;
	}


	return len;
}

void myStrcopy(char *dst, char *src){
	int i = 0;
	while(src[i] != 0){
		dst[i] = src[i];
		i++;

	}
	dst[i] = 0;
}



void myStrcat(char *dst, char *src){
	int dstLen = myStrlen(dst);

	int i = dstLen;

	while(src[i - dstLen] != 0){
		dst[i] = src[i - dstLen];
		i++;
	}
	dst[i] = 0;
}

int myStrcmp(char *s1, char *s2){
	int i = 0;
	while (s1[i] != 0 && s2[i] != 0){
		if (s1[i] != s2[i]){
			return (int) s1[i] - (int) s2[i];
		}
		i++;
	}

	return myStrlen(s1) - myStrlen(s2);
}



int main(){
	char s1[] = "a";
	char s2[] = "ab";

	printf("strcmp: %d\n", myStrcmp(s1,s2));

	printf("strlen: %d\n", myStrlen(s1));

	myStrcopy(s1, s2);
	printf("strcopy: %s\n", s1);

	//myStrcat(s1, s2);
	printf("strcat: %s\n", s1);

	return 0;
}
