#include <stdio.h>

union Data{
	int i;
	char c[sizeof(int)];
}data;

int main(){
	data.i = 1;
	printf( "Memory : %d %d %d %d \n ", data.c[0], data.c[1], data.c[2], data.c[3]);
	return 0;
}
