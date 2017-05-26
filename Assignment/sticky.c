#include <stdio.h>
#include <stdlib.h>

int main(){
	int i = 0;
	int *x;
	while(1){
		i ++;
		x = malloc(i*sizeof(int));
	}
	return 0;
}
