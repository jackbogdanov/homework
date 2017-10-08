#include <stdio.h>

union Data{
	int i;
	char c[sizeof(int)];
}data;

int main(){
	data.i = 1;
	if (data.c[0]){
		printf("Little-endian\n");
	} else {
		printf("Big-endian\n");	
	}
	return 0;
}
